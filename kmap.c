#include "kmap.h"
#include "paging.h"
#include "list.h"
#include "allocator.h"

void kmap_phys_area_init(phys_area * area){
	area->size = 0;
	list_init(&area->phys_segm_head);
}

void kmap_phys_segm_init(phys_segm * segm, phys_t start, uint64_t len){
	segm->start = start;
	segm->len = len;
	list_init(&segm->list_segm);
}

void kmap_phya_area_add_segm(phys_area * area, phys_segm * segm) {
	area->size += segm->len;
	list_add(&segm->list_segm, &area->phys_segm_head);
}

static void fill_region(paging_map_region * new_region, phys_segm * segm, virt_t virt_begin){
	new_region->phys_start = segm->start;
	new_region->virt_start = virt_begin;
	new_region->len = segm->len;
}

void * kmap_mmap(phys_area * area){
	void * ret = malloc(area->size);
	virt_t  virt_begin = (virt_t) ret;

	LIST_FOR_EACH(ptr, &area->phys_segm_head){
		phys_segm * segm = LIST_ENTRY(ptr, phys_segm, list_segm);
		paging_map_region new_region;
		fill_region(&new_region, segm, virt_begin);
		paging_mmap_region(&new_region, PTE_WRITE);
		virt_begin += segm->len;
	}

	return ret;
}

void kmap_ummap(void * ptr, phys_area * area){
	virt_t  virt_begin = (virt_t) ptr;
	LIST_FOR_EACH(ptr, &area->phys_segm_head){
		phys_segm * segm = LIST_ENTRY(ptr, phys_segm, list_segm);
		paging_map_region new_region;
		fill_region(&new_region, segm, virt_begin);
		paging_ummap_region_defaut_holem(&new_region);
		virt_begin += segm->len;
	}
	free(ptr);
}
