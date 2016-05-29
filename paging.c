#include "buddy_allocator.h"
#include "paging.h"
#include "mmap.h"
#include "memory.h"
#include "boot_allocator.h"
#include "print.h"
#include "strings.h"
#include "list.h"
#include "process.h"

#define TWO_GB (0x80000000)

static paging_map_region AFTER_HOLE = {
	.phys_start = 0,
	.virt_start = VA(0)
};

static paging_map_region KERNEL_HIGH = {
	.phys_start = 0,
	.virt_start = KERNEL_VIRT(0),
	.len = TWO_GB
};

static pte_t * pml4;

static inline pte_t * __pml4e(pte_t * pml4, virt_t addr) {
	return pml4 + pml4_i(addr);
}

static inline pte_t * __pdpte(pte_t * pml4, virt_t addr) {
	return pte_level_addr(*__pml4e(pml4, addr)) + pml3_i(addr);
}

static inline pte_t * __pde(pte_t * pml4, virt_t addr) {
	return pte_level_addr(*__pdpte(pml4, addr)) + pml2_i(addr);
}



#define BOOT_ALLOC 0
#define BUDDY_ALLOC 1
static int mode = BOOT_ALLOC;


static void rewrite_addr_with_flags(pte_t * addr, phys_t phys, int page_flags){
	*addr = phys | page_flags;
}

static void rewrite_entry(pte_t * addr, int page_flags){
	void * new_page_addr;
	if(mode == BOOT_ALLOC) {
		new_page_addr = boot_allocator_alloc(PAGE_SIZE, PAGE_SIZE);
	} else {
		new_page_addr = buddy_allocate_page(0);
	}
	memset(new_page_addr, 0, PAGE_SIZE);
	rewrite_addr_with_flags(addr, pa(new_page_addr), page_flags);
}

static void add_map_entry(pte_t * pml4, phys_t paddr, virt_t virtaddr, int flags){
	pte_t * pml4e = __pml4e(pml4, virtaddr);
	if(!pte_present(*pml4e)){
		rewrite_entry(pml4e, (PTE_PRESENT | flags) & (~PTE_LARGE) );
	}
	pte_t * pdpte = __pdpte(pml4, virtaddr);
	if(!pte_present(*pdpte)){
		rewrite_entry(pdpte, (PTE_PRESENT | flags) & (~PTE_LARGE));
	}
	pte_t * pde = __pde(pml4, virtaddr);
	rewrite_addr_with_flags(pde, paddr, PTE_PRESENT | flags | PTE_LARGE);
}

static void remove_map_entry(virt_t virtaddr){
	pte_t * pml4e = __pml4e(pml4, virtaddr);
	if(!pte_present(*pml4e)){
		return;
	}
	pte_t * pdpte = __pdpte(pml4, virtaddr);
	if(!pte_present(*pdpte)){
		return;
	}
	pte_t * pde = __pde(pml4, virtaddr);
	*pde = 0;
}

static void recalculate_map_region_lens(){
	AFTER_HOLE.len = mmap_get_high_memory_level();
}

static uint64_t paging_get_region_mem(paging_map_region * region){
	return (region->len / PAGE_SIZE_2M + 1) * PAGE_SIZE * 2;
}

static void __paging_mmap_region(pte_t * pml4, paging_map_region * region, int flags){
	for(phys_t i = region->phys_start;
			i < region->phys_start + region->len;
			i += PAGE_SIZE_2M){
		add_map_entry(pml4, i, region->virt_start + (i - region->phys_start), flags);
	}
}

static void __paging_ummap_region(paging_map_region * region) {
	for(phys_t i = region->phys_start;
				i < region->phys_start + region->len;
				i += PAGE_SIZE_2M){
		remove_map_entry(region->virt_start + (i - region->phys_start));
	}
}

void paging_mmap_region(paging_map_region * region, int flags){
	__paging_mmap_region(pml4, region, flags);
	store_pml4(pa(pml4));
}

void paging_ummap_region(paging_map_region * region) {
	__paging_ummap_region(region);
	store_pml4(pa(pml4));
}


uint64_t paging_get_component_size(){
	recalculate_map_region_lens();
	return paging_get_region_mem(&AFTER_HOLE) +
		   paging_get_region_mem(&KERNEL_HIGH) + PAGE_SIZE;
}

void paging_ummap_region_defaut_holem(paging_map_region * region){
	paging_map_region new_region = {
			.phys_start = PA(region->virt_start),
			.virt_start = region->virt_start,
			.len = region->len
	};
	paging_mmap_region(&new_region, PTE_WRITE);
}

void paging_init(){
	recalculate_map_region_lens();

	pml4 = boot_allocator_alloc(PAGE_SIZE, PAGE_SIZE);
	memset(pml4, 0, PAGE_SIZE);

	__paging_mmap_region(pml4, &AFTER_HOLE, PTE_WRITE);
	__paging_mmap_region(pml4, &KERNEL_HIGH, PTE_WRITE);
	store_pml4(pa(pml4));
	mode = BUDDY_ALLOC;
}

pte_t * paging_create_newpml_from_process_mm_list(struct list_head *head) {
	pte_t * new_pml4 = boot_allocator_alloc(PAGE_SIZE, PAGE_SIZE);
	memset(new_pml4, 0, PAGE_SIZE);

	__paging_mmap_region(new_pml4, &AFTER_HOLE, PTE_WRITE);
	__paging_mmap_region(new_pml4, &KERNEL_HIGH, PTE_WRITE);
	LIST_FOR_EACH(ptr, head) {
		p_mm_entry * entry = LIST_ENTRY(ptr, p_mm_entry, list);
		__paging_mmap_region(new_pml4, &entry->region, PTE_WRITE | PTE_USER);
	}
	return new_pml4;
}
