
#ifndef SRC_SLAB_ALLOCATOR_H_
#define SRC_SLAB_ALLOCATOR_H_

#include "list.h"

#include <stdint.h>

typedef struct slab{
	uint64_t size;
	struct list_head desc_list;
	struct list_head slab_list;
	void * pool_ptr;
}slab_t;

typedef struct {
	uint64_t size;
	uint64_t align;
	struct list_head slab_list_head;
}slab_pool;

slab_t * slab_init(uint64_t size, uint64_t align);
void * slab_allocate(slab_t * slab);
void slab_free(slab_t * slab, void * addr);

slab_pool * slab_pool_init(uint64_t size, uint64_t align);
void * slab_pool_allocate(slab_pool * pool);
void slab_pool_free(void * addr);



#endif /* SRC_SLAB_ALLOCATOR_H_ */
