
#ifndef MMAP_H_
#define MMAP_H_

#include <stdint.h>
#include <stddef.h>

struct mmap_entry{
	uint64_t addr;
	uint64_t len;
#define REGION_AVAILABLE 1
#define REGION_RESERVED 2
#define KERNEL_REGION 3
	uint32_t type;
};
typedef struct mmap_entry mmap_entry_t;


int mmap_init();
void mmap_print();
mmap_entry_t * mmap_get_entry(int32_t index);
int32_t mmap_get_size();
void map_insert(mmap_entry_t * entry, mmap_entry_t * new_entry);
int32_t mmap_reserve_new_subblock(uint64_t size);
int32_t mmap_reserve_subblock(void * addr, size_t size);
uint64_t mmap_get_high_memory_level();
int mmap_is_block_in_available_mem(mmap_entry_t * new_entry);

#endif
