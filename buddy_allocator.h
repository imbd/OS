#ifndef SRC_BUDDY_ALLOCATOR_H_
#define SRC_BUDDY_ALLOCATOR_H_
#include <stdint.h>
#include <stddef.h>

uint64_t buddy_get_component_size();
void * buddy_allocate_page(uint32_t level);
void buddy_free_page(void * page);
int buddy_allocator_init();
void buddy_set_slab(void * page, void * slab);
void * buddy_get_slab(void *ptr);
size_t buddy_get_alocated_size(void * ptr);

#endif /* SRC_BUDDY_ALLOCATOR_H_ */
