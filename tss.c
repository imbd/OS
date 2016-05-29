#include "memory.h"
#include "tss.h"
#include "allocator.h"
#include "utils.h"
#include "strings.h"
#include "print.h"

static tss_strct tss;

static void tss_gdt_desc_init() {
	void * gdt = get_gdt_ptr();
	const virt_t tss_addr = (virt_t) &tss;
	const size_t tss_size_desc = (sizeof(tss_strct)) - 1;

	tss_desc desc = {
		.base_0 = SPLICE(tss_addr, 0, 16),
		.base_1 = SPLICE(tss_addr, 16, 24),
		.base_2 = SPLICE(tss_addr, 24, 32),
		.base_3 = SPLICE(tss_addr, 32, 64),
		.limit_0 = SPLICE(tss_size_desc, 0, 16),
		.limit_1 = SPLICE(tss_size_desc, 16, 20),
		.type = (TSS_DESC_TYPE) | (TSS_DPL << 5) | (TSS_PRESENT << 7),
	};
	*(tss_desc *)(((uint64_t* )gdt) + TSS_TI) = desc;
}

static void tss_selector_load() {
	load_tr(TSS_SELECTOR);
}

void tss_init() {
	memset(&tss, 0, sizeof(tss_strct));
	tss_gdt_desc_init();
	tss_selector_load();
}

void tss_write_kernel_rsp(void *rsp){
	tss.rsp0 = (int64_t) rsp;
}

void * tss_read_kernel_rsp() {
	return (void *)tss.rsp0;
}
