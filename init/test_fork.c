#include "../test.h"
#include "../syscall_user.h"

void test_fork() {
	uint64_t pid;
	test_assert(fork(&pid) == 0);
	if(pid == 0) {
		test_pass("test fork child");
	} else {
		test_pass("test fork parent");
	}
}
