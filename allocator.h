
#ifndef SRC_ALLOCATOR_H_
#define SRC_ALLOCATOR_H_

#include <stdint.h>
#include <stddef.h>

int allocator_init();
void allocator_set_sync();
void * malloc(uint64_t size);
void * malloc_aligned(size_t size, int64_t align);
void free(void * ptr);
void * realloc(void * ptr, uint64_t new_size);


#endif /* SRC_ALLOCATOR_H_ */
