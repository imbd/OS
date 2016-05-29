
#ifndef SRC_BOOT_ALLOCATOR_H_
#define SRC_BOOT_ALLOCATOR_H_

#include <stdint.h>

#define BOOT_ALLOCATOR_MAX_OBJECTS 100

void * boot_allocator_alloc(uint64_t size, uint64_t align);
void boot_allocator_init(uint64_t size);

#endif /* SRC_BOOT_ALLOCATOR_H_ */
