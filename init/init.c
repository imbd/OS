#include <stdint.h>
#include "tests_list_user.h"
#include <stddef.h>
#include "../syscall_user.h"
#include "../test.h"

void main()
{
	test_set_log(uprintf);
	test_fork();
	while(1);
}
