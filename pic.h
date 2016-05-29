#ifndef PIC_H_
#define PIC_H_

#include "utils.h"

#define PIC_FIRST_COMMAND_WORD ( BIT(0) | BIT(4) )

#define PIC_MASTER_SLAVE_PORT BIT(2)
#define PIC_SLAVE_MASTER_PORT BIT(1)

#define PIC_FOURTH_COMMAND_WORD BIT(0)

#define PIC_INTERRUPT_MASK 0x0

#define PIC_MASTER_COMMAND_REGISTER_PORT 0x20
#define PIC_SLAVE_COMMAND_REGISTER_PORT 0xA0

#define PIC_MASTER_DATA_REGISTER_PORT 0x21
#define PIC_SLAVE_DATA_REGISTER_PORT 0xA1

#define PIC_EOI BIT(5)

void pic_setup();
void pic_eoi(int master);

#endif


