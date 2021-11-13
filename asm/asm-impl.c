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
			"mov %%rdi , %%rax;"
			"mov %%rbx    , (%%rax);"
			"mov %%rsi    , 8(%%rax);"
			"mov %%rdi    , 16(%%rax);"
			"mov %%rbp    , 24(%%rax);"

			"lea 4(%%rsp) , %%rcx;"
			"mov %%rcx    , 32(%%rax);"

			"mov (%%rsp)  , %%rcx;"
			"mov %%rcx    , 40(%%rax);"
			: 
			:
			: "rcx", "rax"
	   );
	return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
	/* longjmp(env, val); */
	asm(    
			"mov 4(%%rsp)  , %%rdx;"
			"mov 8(%%rsp)  , %%eax;"
			"test %%eax    , %%eax;"
			"jnz .L1;"
			"inc %%eax;"

			".L1: ;"
			"mov (%%rdx)   , %%ebx;"
			"mov 4(%%rdx)  , %%esi;"
			"mov 8(%%rdx)  , %%edi;"
			"mov 12(%%rdx) , %%ebp;"
	
			"mov 16(%%rdx) , %%ecx;"
			"mov %%ecx     , %%esp;"

			"mov 20(%%edx) , %%ecx;"
			"jmp *(%%ecx);"

			:
			:
			: "rax", "ebx", "ecx", "edx", "esi"
			);
}

