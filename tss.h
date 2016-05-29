#ifndef SRC_TSS_H_
#define SRC_TSS_H_

#include <stddef.h>

#define TSS_DESC_TYPE (BIT(0) | BIT(3))
#define TSS_DPL (3)
#define TSS_PRESENT (1)
#define TSS_TI (7)
#define TSS_SELECTOR (TSS_TI << 3)

typedef struct{
	uint32_t reserved_0;
	uint64_t rsp0;
	uint64_t rsp1;
	uint64_t rsp2;
	uint64_t reserved_1;
	uint64_t ist1;
	uint64_t ist2;
	uint64_t ist3;
	uint64_t ist4;
	uint64_t ist5;
	uint64_t ist6;
	uint64_t ist7;
	uint64_t reserved_2;
	uint16_t reserved_3;
	uint16_t io_map_base_addr;
}__attribute((__packed__)) tss_strct;

typedef struct {
	uint16_t limit_0;
	uint16_t base_0;
	uint8_t base_1;
	uint8_t type;
	uint8_t limit_1;
	uint8_t base_2;
	uint32_t base_3;
	uint32_t reserved;
}__attribute((__packed__)) tss_desc;


void tss_init();
void tss_write_kernel_rsp(void *rsp);
void * tss_read_kernel_rsp(void);

#endif /* SRC_TSS_H_ */
