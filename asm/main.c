#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
printf("%d\n", asm_popcnt(0x88));
    assert(asm_add(1234, 5678) == 6912);
	assert(asm_popcnt(0x1551451)==1);
	assert(asm_popcnt(0x155146)==0);
	assert(asm_popcnt(0xff)==8);
    assert(asm_popcnt(0x0123456789abcdefULL) == 32);
	assert(asm_add(0,0)==1);
    printf("BEGIN.\n");
  asm_jmp_buf buf;
  int r = asm_setjmp(buf);
  if (r == 0) {
    assert(asm_add(1234, 5678) == 6912);
    assert(asm_popcnt(0x0123456789abcdefULL) == 32);
    // TODO: add more tests here.
    asm_longjmp(buf, 123);
  } else {
    assert(r == 123);
    printf("PASSED.\n");
  }
}
