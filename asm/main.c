#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
	/* printf("\n\nBEGIN.\n"); */
	asm_jmp_buf buf;
	int r = asm_setjmp(buf);
	printf("r:%d\n", r);
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
