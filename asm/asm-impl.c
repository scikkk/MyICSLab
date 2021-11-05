#include "asm.h"
#include <string.h>


int64_t asm_add(int64_t a, int64_t b) {
	int64_t ret = 0;
	asm(
			"lea (%[a],%[b],1), %[ret]"
			: [ret] "+r"(ret)
			: [a] "r"(a), [b] "r"(b)
	   );
	return ret;
}

int asm_popcnt(uint64_t x) {
	int sum = 0;
	asm ( "and $0x1, %%eax;"
			"add %%eax %[s];"
		"shrl $0x1 %[x]"
		:[s] "edx"(sum), [x] "rax"(x)
		: 
		: "eax", "edx", "rax"
		);
	return sum;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
	return memcpy(dest, src, n);
}

int asm_setjmp(asm_jmp_buf env) {
	return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
	longjmp(env, val);
}
