#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
	/* printf("\n\nBEGIN.\n"); */
	asm_jmp_buf buf;
	buf.ebp = 0;
	asm_setjmp(buf);
	/* int r = asm_setjmp(buf); */
	/* if (r == 0) { */
	/* 	/1* printf("Enter first branch.\n"); *1/ */
	/* 	asm_longjmp(buf, 123); */
	/* } else { */
	/* 	/1* printf("Enter second branch.\n"); *1/ */
	/* 	assert(r == 123); */
	/* 	/1* printf("PASSED.\n"); *1/ */
	/* } */
	/* printf("END.\n"); */
}
