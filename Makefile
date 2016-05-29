CC ?= gcc
LD ?= gcc

MAKE:=make
CFLAGS := -g -m64 -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -ffreestanding \
	-mcmodel=kernel -Wall -Wextra -pedantic -std=c11 \
	-Wframe-larger-than=4096 -Wstack-usage=4096 -Wno-unknown-warning-option
LFLAGS := -nostdlib -z max-page-size=0x1000

ASM := bootstrap.S videomem.S threads_s.S syscall_s.S
AOBJ:= $(ASM:.S=.o)
ADEP:= $(ASM:.S=.d)

SRC := main.c pic.c interrupt.c pit.c video.c uart.c \
	backtrace.c print.c mmap.c \
	boot_allocator.c list.c buddy_allocator.c \
	slab_allocator.c allocator.c \
	paging.c kmap.c \
	lock.c threads.c \
	tmpfs.c strings.c \
	test_allocator.c test_threads.c\
	initramfs.c avl_tree.c process.c elf.c syscall.c tss.c handler_wrapper.c \
	syscall_user.c

OBJ := $(AOBJ) $(SRC:.c=.o)
DEP := $(ADEP) $(SRC:.c=.d)

all: kernel init

kernel: $(OBJ) kernel.ld
	$(LD) $(LFLAGS) -T kernel.ld -o $@ $(OBJ)
	
%.o: %.S
	$(CC) -D__ASM_FILE__ -g -MMD -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEP)

.PHONY: clean
clean:
	rm -f kernel $(OBJ) $(DEP) 
	$(MAKE) -C init clean
	
	
.PHONY: init
init:syscall_user.o print.o strings.o syscall_s.o
	$(MAKE) -C init
	rm -rf initramfs
	mkdir initramfs
	cp init/init initramfs
	./make_initramfs.sh initramfs initramfs.img

