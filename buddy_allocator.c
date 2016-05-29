
#ifndef BUDDY_ALLOCATOR_C_
#define BUDDY_ALLOCATOR_C_

#include "memory.h"
#include "buddy_allocator.h"
#include "list.h"
#include "mmap.h"
#include "utils.h"
#include "boot_allocator.h"
#include <stddef.h>

struct buddy_page_discriptor{
	struct list_head list_desriptors;
	uint32_t available;
	uint32_t level;
	phys_t addr;
	void * slab;
};
typedef struct buddy_page_discriptor buddy_page_discriptor_t;

static struct list_head *  buddy_level_head;
static buddy_page_discriptor_t * all_discriptors;
static uint64_t discriptors_sz;
static uint64_t level_sz;

uint64_t buddy_get_component_size(){
	discriptors_sz = mmap_get_high_memory_level() / PAGE_SIZE;
	level_sz = 0;
	for(uint64_t temp = discriptors_sz; temp > 0; temp = (temp >> 1), level_sz++){	}
	return level_sz * sizeof(struct list_head)  +
			discriptors_sz * sizeof(buddy_page_discriptor_t);
}

static uint32_t get_buddy(uint32_t page_id, uint32_t level_id){
	return page_id ^ BIT(level_id);
}

static uint32_t get_page_id_addr(phys_t addr){
	return addr / PAGE_SIZE;
}

static uint32_t get_page_id(buddy_page_discriptor_t * page){
	return get_page_id_addr(page->addr);
}

static int is_page_in_bounds(uint32_t page_id){
	return page_id < discriptors_sz;
}


static void import_page(uint32_t page_id){
	buddy_page_discriptor_t * page = &all_discriptors[page_id];
	page->available = 0;
	list_del(&page->list_desriptors);
}

static void export_page(uint32_t page_id, uint32_t level_id){
	buddy_page_discriptor_t * page = &all_discriptors[page_id];
	page->available = 1;
	page->level = level_id;
	list_add(&page->list_desriptors, &buddy_level_head[level_id]);
}

#include "print.h"

void * buddy_allocate_page(uint32_t level){
	for(uint32_t current_level = level; current_level < level_sz; current_level++){
		if(!list_empty(&buddy_level_head[current_level])){
			uint32_t new_page_id = get_page_id(LIST_ENTRY(buddy_level_head[current_level].next,
											  buddy_page_discriptor_t,
											  list_desriptors ));
			for(uint32_t j = current_level; j > level; j--){
				import_page(new_page_id);
				export_page(new_page_id, j - 1);
				uint32_t buddy = get_buddy(new_page_id, j - 1);
				if(is_page_in_bounds(buddy))
					export_page(buddy, j - 1);
			}
			import_page(new_page_id);
			return va(all_discriptors[new_page_id].addr);
		}
	}
	return NULL;
}

void buddy_free_page(void * page){
	uint32_t page_id = get_page_id_addr(pa(page));
	all_discriptors[page_id].slab = NULL;
	export_page(page_id, all_discriptors[page_id].level);

	for(uint32_t j = all_discriptors[page_id].level + 1; j < level_sz; j++){
		uint32_t buddy = get_buddy(page_id, j - 1);
		if(!is_page_in_bounds(buddy) || !all_discriptors[buddy].available || (all_discriptors[buddy].level != j - 1))
			break;
		import_page(page_id);
		import_page(buddy);
		page_id = MIN(page_id, buddy);
		export_page(page_id, j);
	}
}

size_t buddy_get_alocated_size(void * ptr) {
	uint32_t page_id = get_page_id_addr(pa(ptr));
	return PAGE_SIZE * (1 << all_discriptors[page_id].level);
}



int buddy_allocator_init() {
	buddy_get_component_size();

	all_discriptors = boot_allocator_alloc(discriptors_sz * sizeof(buddy_page_discriptor_t), 1);
	buddy_level_head = boot_allocator_alloc(level_sz * sizeof(struct list_head), 1);

	if(all_discriptors == NULL || buddy_level_head == NULL){
		return -1;
	}

	for(uint64_t i = 0; i < discriptors_sz; i++){
		all_discriptors[i].available = 0;
		all_discriptors[i].addr = i * PAGE_SIZE;
		all_discriptors[i].slab = NULL;
		all_discriptors[i].level = 0;
		list_init(&all_discriptors[i].list_desriptors);
	}


	for(uint32_t i = 0; i < level_sz; i++){
		list_init(&buddy_level_head[i]);
	}

	mmap_entry_t new_page_entry;
	new_page_entry.len = PAGE_SIZE;

	for(uint32_t i = 0; i < discriptors_sz; i++){
		new_page_entry.addr = all_discriptors[i].addr;
		if(mmap_is_block_in_available_mem(&new_page_entry)){
			buddy_free_page(va(all_discriptors[i].addr));
		}
	}

	return 0;
}

void buddy_set_slab(void * page, void * slab){
	uint32_t page_id = get_page_id_addr(pa(page));
	all_discriptors[page_id].slab = slab;
}

void * buddy_get_slab(void *ptr){
	uint32_t page_id = get_page_id_addr(pa(ptr));
	return all_discriptors[page_id].slab;
}
#endif /* BUDDY_ALLOCATOR_C_ */
