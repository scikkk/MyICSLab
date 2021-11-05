#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
  asm_jmp_buf buf;
  int r = asm_setjmp(buf);
  if (r == 0) {
    asm_longjmp(buf, 123);
  } else {
    assert(r == 123);
    printf("PASSED.\n");
  }
}
