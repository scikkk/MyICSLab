#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#define U64 "%" PRIu64
uint64_t multimod(uint64_t, uint64_t, uint64_t);
void py_mod(uint64_t, uint64_t, uint64_t);
void test(uint64_t a, uint64_t b, uint64_t m) {
	py_mod(a,b,m);
	printf("(" U64 " * " U64 ") mod " U64 " = " U64 "\n\n", a, b, m, multimod(a, b, m));
}

int main() {

	test(123, 452222222222226, 789);
	/* test(-2ULL, 4, 415); */ 
	/* test(14258, -2ULL, 1425); */ 
	/* test(123, 456, -1ULL); */
	/* test(41258, -2ULL, -1ULL); */
	/* test(-2ULL, 102485, -1ULL); */
	/* test(-2ULL, -2ULL, 142558); */
	/* test(-2ULL, -2ULL, -1ULL); // should be 1 */
}
