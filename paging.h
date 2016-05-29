#ifndef __PAGING_H__
#define __PAGING_H__

#include <stdbool.h>
#include <stdint.h>

#include "memory.h"
#include "list.h"

typedef uint64_t pte_t;

#define PTE_PRESENT ((pte_t)1 << 0)
#define PTE_WRITE   ((pte_t)1 << 1)
#define PTE_USER    ((pte_t)1 << 2)
#define PTE_LARGE   ((pte_t)1 << 7)

static inline bool pte_present(pte_t pte)
{ return (pte & PTE_PRESENT) != 0; }

static inline bool pte_write(pte_t pte)
{ return (pte & PTE_WRITE) != 0; }

static inline bool pte_user(pte_t pte)
{ return (pte & PTE_USER) != 0; }

static inline bool pte_large(pte_t pte)
{ return (pte & PTE_LARGE) != 0; }

static inline phys_t pte_phys(pte_t pte)
{ return (phys_t)((pte >> 12) & 0xfffffffffull); }

static inline pte_t* pte_level_addr(pte_t pte){
	return (pte_t *) va(pte_phys(pte) << 12);
}

static inline int pml4_i(virt_t addr)
{ return (int)((addr >> 39) & 0x1ff); }

static inline int pml3_i(virt_t addr)
{ return (int)((addr >> 30) & 0x1ff); }

static inline int pml2_i(virt_t addr)
{ return (int)((addr >> 21) & 0x1ff); }

static inline int pml1_i(virt_t addr)
{ return (int)((addr >> 12) & 0x1ff); }

static inline int page_off(virt_t addr)
{ return (int)(addr & 0xfff); }

static inline virt_t canonical(virt_t addr)
{
	if ((addr & (1ull << 47)) == 0)
		return addr;
	return addr | 0xffff000000000000llu;
}

static inline virt_t linear(virt_t addr)
{ return addr & 0x0000ffffffffffffllu; }

static inline void store_pml4(phys_t pml4)
{ __asm__ volatile ("movq %0, %%cr3" : : "a"(pml4) : "memory"); }

static inline phys_t load_pml4(void)
{
	phys_t pml4;

	__asm__ volatile ("movq %%cr3, %0" : "=a"(pml4));
	return pml4;
}

static inline void flush_tlb_addr(virt_t addr)
{ __asm__ volatile ("invlpg (%0)" : : "r"(addr) : "memory"); }

static inline void flush_tlb(void)
{ store_pml4(load_pml4()); }

uint64_t paging_get_component_size();
void paging_init();

typedef struct{
	phys_t phys_start;
	virt_t virt_start;
	uint64_t len;

}paging_map_region;

void paging_mmap_region(paging_map_region * region, int flags);
void paging_ummap_region_defaut_holem(paging_map_region * region);
void paging_ummap_region(paging_map_region * region);
pte_t * paging_create_newpml_from_process_mm_list(struct list_head *head);

#endif /*__PAGING_H__*/
