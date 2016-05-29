#ifndef SRC_KMAP_H_
#define SRC_KMAP_H_

#include "memory.h"
#include "list.h"

typedef struct {
	phys_t start;
	struct list_head list_segm;
	uint64_t len;
}phys_segm;

typedef struct {
	uint64_t size;
	struct list_head phys_segm_head;
}phys_area;

void kmap_phys_area_init(phys_area * area);
void kmap_phys_segm_init(phys_segm * segm, phys_t start, uint64_t len);

void kmap_phya_area_add_segm(phys_area * area, phys_segm * segm);

void * kmap_mmap(phys_area * area);

void kmap_ummap(void * ptr, phys_area * area);



#endif /* SRC_KMAP_H_ */
