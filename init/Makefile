CC ?= gcc
LD ?= gcc

FLAGS=-mno-red-zone -mno-mmx -mno-sse -mno-sse2 -ffreestanding -Wall -Wextra -Werror -pedantic  -nostdlib --std=c11 
all:init

init:init.o test_fork.o
	$(LD) -T init.ld -o init init.o test_fork.o ../syscall_user.o ../print.o ../strings.o ../syscall_s.o --unresolved-symbols=ignore-all
init.o:init.c
	$(CC)  -c init.c $(FLAGS) 
test_fork.o:test_fork.c
	$(CC)  -c test_fork.c $(FLAGS) 
clean:
	rm -f init init.o test_fork.o