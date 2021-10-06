#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#define U64 "%" PRIu64
#define NUM 10
uint64_t multimod(uint64_t, uint64_t, uint64_t);
void py_mod(char*);
void test(uint64_t a, uint64_t b, uint64_t m) {
	char right[99];
	//  char 	mymod[99];
	sprintf(right, "python3 -c 'print((" U64 "*" U64 ")%%" U64 ")'", a,b,m);
	py_mod(right);
	uint64_t myres = multimod(a, b, m);
	//	sprintf(mymod, "%lu", myres);
	//	if (strcmp(right, mymod) != 0) {
	//		printf("Failure!");
	//		printf("right: %s\nmymod: %s\n", right, mymod);
	//	} 
	//		printf("(%lu * %lu) %% %lu \nright: %s\nmymod: %s\n\n", a, b, m, right, mymod);
	printf("right: (" U64 " * " U64 ") mod " U64 " = %s\n", a, b, m, right);
	printf("myres: (" U64 " * " U64 ") mod " U64 " = " U64 "\n\n", a, b, m, myres);
}

int main() {
	uint64_t a, b, m; 
	srand((unsigned)time(NULL));
	for (int k = 0; k < NUM ; k++) {
		a = rand()*9999 - 10000;
		b = rand()*9999 - 10000;
		m = rand()*9999 - 10000;
		test(a, b, m);
	}
	test(-145221ULL, 121425454553, 114528452154759);
	/* test(-2ULL, -2ULL, -1ULL); // should be 1 */
}

