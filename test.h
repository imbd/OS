#ifndef SRC_TEST_H_
#define SRC_TEST_H_

int (*log)(const char *format, ...);

#define test_fail(...) \
	log("FAILED : "); \
	log(__VA_ARGS__); \
	log("\n"); \
	return;

#define test_pass(...) \
	log("PASSED : "); \
	log(__VA_ARGS__); \
	log("\n"); \
	return;

#define test_assert(assertion) \
	if(!(assertion)) { \
		test_fail(#assertion); \
	}

static inline void test_set_log(int (*log_arg)(const char *format, ...)) {
	log = log_arg;
}



#endif /* SRC_TEST_H_ */
