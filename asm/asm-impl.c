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
	asm(
			"mov %%esp , %%eax;"
			"mov %%rbx    , (%%eax);"
			"mov %%rsi    , 8(%%eax);"
			"mov %%rdi    , 16(%%eax);"
			"mov %%rbp    , 24(%%eax);"

			"lea 4(%%esp) , %%rcx;"
			"mov %%rcx    , 32(%%eax);"

			"mov (%%esp)  , %%rcx;"
			"mov %%rcx    , 40(%%eax);"
			: [ebx] "r"(env[0]) 
			:
			: "rcx", "rax"
	   );
	return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
	/* longjmp(env, val); */
	asm(    
			"mov 4(%%esp)  , %%rdx;"
			"mov 8(%%esp)  , %%rax;"
			"test %%rax , %%rax;"
			"jnz .L1;"
			"inc %%rax;"

			".L1: ;"
			"mov (%%rdx)   , %%rbx;"
			"mov 8(%%rdx)  , %%rsi;"
			"mov 16(%%rdx)  , %%rdi;"
			"mov 24(%%rdx) , %%rbp;"
	
			"mov 32(%%rdx) , %%rcx;"
			/* "mov %%rcx     , %%rsp;" */

			"mov 40(%%rdx) , %%rcx;"
			"jmp *(%%rcx);"

			:
			:
			: "rax", "rbx", "rcx", "rdx",  "rdi", "rsi"
			);
}

