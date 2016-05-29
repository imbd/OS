#include "backtrace.h"
#include "uart.h"
#include "print.h"
#include "utils.h"


int64_t getAdressE8(int64_t operand_begin, int64_t base){
	return base + ((int32_t)(operand_begin & 0xFFFFFFFF));
}

int checkE8(int64_t after_call){
	int64_t temp = *((int64_t *)(after_call - 5));
	return (temp & (0xFF)) == 0xE8;
}

void backtrace(int64_t *buf, int size, int iret){
	int64_t rbp;
	__asm__ volatile("mov %%rbp, %0" : "=r"(rbp));
	printf("backtrace begin=============================\n\n");
	for(int i = 0; i < size; i++, iret--, rbp = *((int64_t *)rbp)){
		int64_t after_call = *((int64_t *)(rbp + 8));
		if(!iret){
			printf("IRET TO [%p]\n\n", after_call);
			continue;
		}

		printf("CALLER POINT ADRESS (after call) [%p]\n", after_call);

		if(!checkE8(after_call)){
			printf("UNSUPPORTED CALL FORMAT\n\n");
			break;
		}

		int64_t temp = *((int64_t *)(after_call - 4));
		buf[i] = getAdressE8(temp, after_call);
		printf("CURRENT ADRESS CALL [%p]\n\n", buf[i]);
	}
	printf("backtrace end=============================\n");
}
