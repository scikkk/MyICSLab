#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
	/* printf("\n\nBEGIN.\n"); */
	asm_jmp_buf buf = {1,2,3,4,5,6};

	int r = asm_setjmp(buf);

	/* asm_longjmp(buf, 123); */














	/* if (r == 0) { */
	/* 	printf("Enter first branch.\n"); */
	/* 	asm_longjmp(buf, 123); */
	/* 	printf("End first branch.\n"); */
	/* } else { */
	/* 	printf("Enter second branch.\n"); */
	/* 	assert(r == 123); */
	/* 	printf("PASSED.\n"); */
	/* } */
	/* printf("END.\n"); */
}
