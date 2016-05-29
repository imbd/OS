#include "mmap.h"

#include "multiboot.h"
#include "utils.h"
#include "print.h"

extern const uint32_t mboot_info ;
extern char text_phys_begin [] ;
extern char bss_phys_end [] ;


#define MAX_MMAP_REGIONS 100

static mmap_entry_t mmap_regions[MAX_MMAP_REGIONS];
static int regions_num = 0;

static void clean_mmap_regions(){
	regions_num = 0;
}

static const char * get_readable_region_type(uint32_t type){
	switch(type){
	case REGION_AVAILABLE:
		return "AVAILABLE";
	case REGION_RESERVED:
		return "RESERVED";
	case KERNEL_REGION:
		return "KERNEL";
	default:
		return "UNRECOGNIZED REGION TYPE";
	}
}

static int check_btw(mmap_entry_t *entry, mmap_entry_t * new_entry){
	return entry->addr + entry->len >= new_entry->addr + new_entry->len &&
			entry->addr <= new_entry->addr;
}

static int insert_if_comparable(mmap_entry_t *entry, mmap_entry_t * new_entry){
	if(check_btw(entry, new_entry)) {
		map_insert(entry, new_entry);
		return 0;
	}
	return 1;
}

int mmap_is_block_in_available_mem(mmap_entry_t * new_entry){
	for(int i = 0; i < regions_num; i++){
		if(mmap_regions[i].type == REGION_AVAILABLE &&
				check_btw(&mmap_regions[i], new_entry))
		return 1;
	}
	return 0;
}

int mmap_init(){
	clean_mmap_regions();

	multiboot_info_t *mbi = (multiboot_info_t *) (uint64_t)mboot_info;
	if (!CHECK_FLAG(mbi->flags, MMAP_FLAG_MEM) || mbi->mmap_length == 0) {
		printf("cannot provide memmap\n");
		return -1;
	}



	mmap_entry_t kernel_entry = {
			.type = KERNEL_REGION,
			.addr = (uint64_t)text_phys_begin,
	};
	kernel_entry.len = (uint64_t)bss_phys_end -  (uint64_t)text_phys_begin + 1;


	for (multiboot_memory_map_t * mmap_region = (multiboot_memory_map_t *) (uint64_t)mbi->mmap_addr;
			(uint64_t)mmap_region < ((uint64_t)mbi->mmap_addr) + mbi->mmap_length;
			mmap_region = (multiboot_memory_map_t *) (((uint64_t)mmap_region) + mmap_region->size
					+ sizeof(mmap_region->size))) {
		mmap_entry_t current_entry = {
				.type = mmap_region->type,
				.addr = mmap_region->addr,
				.len = mmap_region->len
		};

		mmap_regions[regions_num++] = current_entry;

		insert_if_comparable(&mmap_regions[regions_num - 1], &kernel_entry);
	}
	return 0;
}



void mmap_print(){
	for(int i = 0; i < regions_num; i++) {
		mmap_entry_t * mmap_region = &mmap_regions[i];
		printf("memory range: 0x%llx-0x%llx, type %s\n",
						(mmap_region->addr),
						(mmap_region->addr + mmap_region->len - 1),
						get_readable_region_type(mmap_region->type));
	}
}


void map_insert(mmap_entry_t * entry, mmap_entry_t * new_entry){
	int32_t index = entry - mmap_regions;
	int is_same = new_entry->addr == entry->addr;
	for(int i = regions_num - 1; i > index; i--){
		mmap_regions[i + 2 - is_same] = mmap_regions[i];
	}


	mmap_regions[index + 2 - is_same].addr = new_entry->addr + new_entry->len;
	mmap_regions[index + 2 - is_same].len = entry->addr + entry->len - new_entry->addr -  new_entry->len;
	mmap_regions[index + 2 - is_same].type = entry->type;

	mmap_regions[index + 1 - is_same] = *new_entry;
	if(!is_same)
		mmap_regions[index].len = new_entry->addr -  entry->addr;

	regions_num += 2 - is_same;
}

int32_t mmap_reserve_new_subblock(uint64_t size){
	for(int i = 0; i < regions_num; i++){
		if(!mmap_regions[i].type == REGION_AVAILABLE)
			continue;
		mmap_entry_t new_entry = {
					.len = size,
					.type = REGION_RESERVED,
					.addr = mmap_regions[i].addr
		};
		if(!insert_if_comparable(&mmap_regions[i], &new_entry)){
			return i;
		}
	}
	return -1;
}

int32_t mmap_reserve_subblock(void * addr, size_t size) {
	for(int i = 0; i < regions_num; i++){
		if(!mmap_regions[i].type == REGION_AVAILABLE)
			continue;
		mmap_entry_t new_entry = {
					.len = size,
					.type = REGION_RESERVED,
					.addr = (uint64_t)addr
		};
		if(!insert_if_comparable(&mmap_regions[i], &new_entry)){
			return i;
		}
	}
	return -1;
}

int32_t mmap_get_size(){
	return regions_num;
}

mmap_entry_t * mmap_get_entry(int32_t index){
	return &mmap_regions[index];
}

uint64_t mmap_get_high_memory_level(){
	return mmap_regions[regions_num - 1].addr + mmap_regions[regions_num - 1].len;
}
