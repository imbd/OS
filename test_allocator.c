#include "interrupt.h"
#include "pic.h"
#include "pit.h"
#include "video.h"
#include "handler_wrapper.h"
#include "uart.h"
#include "print.h"
#include "backtrace.h"
#include "mmap.h"
#include "allocator.h"
#include "paging.h"
#include "buddy_allocator.h"
#include "threads.h"
#include <stddef.h>
#include "test.h"

static bool range_intersect(phys_t l0, phys_t r0, phys_t l1, phys_t r1)
{
	if (r0 <= l1)
		return false;
	if (r1 <= l0)
		return false;
	return true;
}

void test_slab(){
    int n = 2;
    int m = 512;
    int ** b = (int**) malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++){
        b[i] = (int *) malloc(m * sizeof (int));
        for(int j = 0; j < m; j++) {
            b[i][j] = j;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            test_assert(b[i][j] == j);
        }
        free(b[i]);
    }
    free(b);
    test_pass("test_slab");
}



void test_buddy(void)
{
#define PAGES 10
	void * page[PAGES];
	int order[PAGES];

	for (int i = 0; i != PAGES; ++i) {
		page[i] = buddy_allocate_page(i);
		if (page[i]) {
			order[i] = i;
		} else {
			test_fail("ALLOC ERROR");
		}
	}


	for (int i = 0; i != PAGES - 1; ++i) {
		if (!page[i])
			break;
		for (int j = i + 1; j != PAGES; ++j) {
			if (!page[j])
				break;

			const phys_t ibegin = pa(page[i]);
			const phys_t iend = ibegin + (PAGE_SIZE << order[i]);

			const phys_t jbegin = pa(page[j]);
			const phys_t jend = jbegin + (PAGE_SIZE << order[j]);

			bool ok = range_intersect(ibegin, iend, jbegin, jend);
			if(ok) {
				test_fail("%d intr with %d\n", i, j);
			}
		}
	}

	for (int i = 0; i != PAGES; ++i) {
		if (!page[i])
			continue;
		buddy_free_page(page[i]);
	}
#undef PAGES
	test_pass("test_buddy");
}
