#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
	printf("\n\nBEGIN.\n");
	asm_jmp_buf buf;
	printf("\n\nBEGIN.\n");
	int r = asm_setjmp(buf);
	printf("\n\nBEGIN.\n");
	if (r == 0) {
		printf("Enter first branch.\n");
		asm_longjmp(buf, 123);
	} else {
		printf("Enter second branch.\n");
		assert(r == 123);
		printf("PASSED.\n");
	}
	printf("END.\n");
}
