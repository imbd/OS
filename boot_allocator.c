#include "boot_allocator.h"
#include "mmap.h"
#include "memory.h"
#include "print.h"
#include <stddef.h>

static mmap_entry_t * region;
static virt_t current_addr;

void boot_allocator_init(uint64_t size){
	region = mmap_get_entry(mmap_reserve_new_subblock(size));
	current_addr = (virt_t) va(region->addr);
}

static int addr_in_bounds(uint64_t addr){
	return addr >= region->addr && addr < region->addr + region->len;
}

void * boot_allocator_alloc(uint64_t size, uint64_t align){
	virt_t new_addr = current_addr;
	if(align && current_addr % align)
		new_addr = (current_addr / align + 1) * align;
	void * ret = (void *)new_addr;
	if(!addr_in_bounds(pa(ret))){
		return NULL;
	}

	current_addr = new_addr + size;
	return ret;
}
