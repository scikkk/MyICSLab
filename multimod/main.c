#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#define U64 "%" PRIu64
#define NUM 10
uint64_t multimod(uint64_t, uint64_t, uint64_t);
void py_mod(uint64_t, uint64_t, uint64_t);
void test(uint64_t a, uint64_t b, uint64_t m) {
	py_mod(a,b,m);
	printf( U64 "\n", multimod(a, b, m));
	printf("(" U64 " * " U64 ") mod " U64 " = " U64 "\n\n", a, b, m, multimod(a, b, m));
}

int main() {
	int a, b, m; 
	for (int k = 0; k < NUM ; k++) {
    srand((unsigned)time(NULL));
	a = rand();
	b = rand();
	m = rand();
	test(a, b, m);
	}
	test(-2ULL, -2ULL, -1ULL); // should be 1
}

