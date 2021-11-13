#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
	printf("\n\nBEGIN.\n");
  /* asm_jmp_buf buf; */
  /* int r = asm_setjmp(buf); */
  /* if (r == 0) { */
  /*   asm_longjmp(buf, 123); */
  /* } else { */
  /*   assert(r == 123); */
  /*   printf("PASSED.\n"); */
  /* } */
  char a[] = "wangke2002";
  char b[] = "00000000000000";
  asm_memcpy(b, a, 6);
  printf("a:%s\nb:%s\n", a, b);
    printf("END.\n");
}
