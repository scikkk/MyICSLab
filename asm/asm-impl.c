#include "asm.h"
#include <string.h>

#define onebit  \
	"movq %[x], %%rax\n" \
	"and $0x1, %%eax\n"  \
	"add %%eax, %[s]\n"  \
	"shrq $0x1, %[x]\n"  

#define eight(x) x x x x x x x x

int64_t asm_add(int64_t a, int64_t b) {
	int64_t ret = 0;
	asm(
			"leaq (%[a],%[b],1), %[ret]"
			: [ret] "+r"(ret)
			: [a] "r"(a), [b] "r"(b)
	   );
	return ret;
}

int asm_popcnt(uint64_t x) {
	int sum = 0, one=1;
	asm (
			eight(eight(onebit))
			:[s] "+r"(sum),[x] "+r"(x)
			:
			: "rax"
		);
	return sum;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
	/* return memcpy(dest, src, n); */
	asm(
			"movq $0 , %%rcx;"
			".cpy:;"
			"movb (%[src], %%rcx, 1) , %%al;"
			"movb %%al, (%[dest], %%rcx, 1);"
			"addq $1, %%rcx;"
			"cmpq %%rcx, %[n];"
			"jg .cpy;"
			: 
			: [n] "r"(n), [dest] "r"(dest), [src] "r"(src)
			: "al", "rcx"
	   );
	return dest;
}

int asm_setjmp(asm_jmp_buf env) {
	/* return setjmp(env); */
	asm(
			"movl %ecx    , 12(%esp);"
			"movl 4(%esp) , %ecx;"
			"movl $0       , (%ecx);"

			"movl %ebx    , 4(%ecx);"
			"movl 12(%esp), %eax;"
			"movl %eax    , 12(%ecx);"

			"movl %edx    , 12(%ecx);"
			"movl %esi    , 16(%ecx);"
			"movl %edi    , 20(%ecx);"
			"movl %ebp    , 24(%ecx);"
			"movl %esp    , 28(%ecx);"

			"movl (%esp)  , %eax;"
			"movl %eax    , 32(%ecx);"

			"movl $0 , %eax;"
	   );
	return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
	/* longjmp(env, val); */
	asm(    "movl  4(%esp) , %ecx;"
			"movl (%ecx)  , %eax;"


			"movl 4(%ecx)  , %ebx;"
			"movl 12(%ecx)  , %edx;"
			"movl 16(%ecx)  , %esi;"
			"movl 20(%ecx)  , %edi;"
			"movl 24(%ecx)  , %ebp;"

			"movl 36(%ecx)  , %ecx;"
			"movl 4(%esp)   , %eax;"
			"movl %ecx      , (%eax);"

			"movl 4(%esp)   , %ecx;"
			"movl 32(%ecx)  , %eax;"
			"movl 28(%ecx)  , %esp;"

			"movl $1 , %eax;"
			"ret;"
	   );
}
