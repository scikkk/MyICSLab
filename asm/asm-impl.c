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

	asm volatile(
			"movq %%rax,0(%%rdi);"
			"movq %%rbx,8(%%rdi);"
			"movq %%rcx,16(%%rdi);"
			"movq %%rdx,24(%%rdi);"
			"movq %%rdi,32(%%rdi);"
			"movq %%rsi,40(%%rdi);"
			"movq %%rbp,%%rbx;"
			"add $16,%%rbx;"
			"movq %%rbx,48(%%rdi);"  //esp
			"movq 0(%%rbp),%%rbx;"
			"movq %%rbx,56(%%rdi);"	//ebp
			"movq 8(%%rbp),%%rbx;"
			"movq %%rbx,64(%%rdi);"  //eip
			:
			:
			: "rbx"
		);

	return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
	/* longjmp(env, val); */


	asm volatile(
			"movq 0(%%rdi),%%rax;"
			"movq 16(%%rdi),%%rcx;"
			"movq 24(%%rdi),%%rdx;"
			"movq 48(%%rdi),%%rsp;"
			"movq 56(%%rdi),%%rbp;"
			"movq 64(%%rdi),%%rbx;"
			"pushq %%rbx;"			//eip
			"movq 8(%%rdi),%%rbx;"
			"movq 32(%%rdi),%%rdi;"
			"movq 40(%%rdi),%%rsi;"
			"ret;"					//eip
			:
			:
			: "rax", "rbx", "rcx", "rdx", "rdi", "rsi"
		);
}

