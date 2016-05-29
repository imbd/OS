#ifndef UTILS_H_
#define UTILS_H_

#define BIT(x) (1L<<(x))
#define SPLICE(x, begin, end) (x >> begin) & (BIT(end - begin) - 1)
#define LOW(x, mod) SPLICE(x, 0, mod)

#define STR(...) #__VA_ARGS__
#define EXPAND(name) STR(name)

#define VOID_FUNC(name) void name()
#define CHECK_FLAG(x, value) ((x & value) > 0)

#define CONTAINER_OF(ptr, type, member) \
	(type *)( (char *)(ptr) - offsetof(type, member) )

#define MIN(a, b) (a < b ? a : b)

#define MAX(a, b) (a > b ? a : b)

#define barrier() __asm__ volatile("" ::: "memory")

#define wmb() asm volatile ("sfence" ::: "memory")



#endif
