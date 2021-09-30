#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#define U64 "%" PRIu64
#define NUM 1000
uint64_t multimod(uint64_t, uint64_t, uint64_t);
void py_mod(uint64_t, uint64_t, uint64_t, char*);
void test(uint64_t a, uint64_t b, uint64_t m) {
	char right[99], mymod[99];
	py_mod(a,b,m,right);
	uint64_t myres = multimod(a, b, m);
	sprintf(mymod, "%lu", myres);
	if (strcmp(right, mymod) != 0) {
		printf("Failure!");
		printf("right: %s\nmymod: %s\n", right, mymod);
	} 
	else {
		printf("Success!\n");
	}
	//	printf("right: %s\nmymod: "  U64 "\n", right,myres);
	//	printf("(" U64 " * " U64 ") mod " U64 " = " U64 "\n\n", a, b, m, multimod(a, b, m));
}

int main() {
	uint64_t a, b, m; 
	srand((unsigned)time(NULL));
	for (int k = 0; k < NUM ; k++) {
		a = rand() - 999;
		b = rand() - 999;
		m = rand() - 999;
		test(a, b, m);
	}
	test(-2ULL, -2ULL, -1ULL); // should be 1
}

