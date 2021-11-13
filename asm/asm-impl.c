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
			"push %%rbp;"
			"movq %%rsp,%%rbp;"
			"mov (%%rbp),%%rax;"
			"mov %%rax, (%%rdi);"
			"lea 16(%%rsp), %%rax;"
			"mov %%rax,8(%%rdi);" //rsp
			"mov %%rbx,16(%%rdi);"
			"mov 8(%%rsp),%%rax;"
			"mov %%rax,24(%%rdi);" //pc
			"mov %%r12,32(%%rdi);"
			"mov %%r13,40(%%rdi);"
			"mov %%r14,48(%%rdi);"
			"mov %%r15,56(%%rdi);"//save register
			"mov %%rbp,%%rsp;"
			"pop %%rbp;"
			:
			: "rdi"(env)
			: "memory", "rdi"
			);

	return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
	/* longjmp(env, val); */


	uint64_t pc=0;

	asm volatile(
			"movq(%%rdi),%%rbp;"
			"movq Ox8(%%rdi), %%rsp;"
			"movq 0x10(%%rdi),%%rbx;"
			"movq 0x20(%%rdi,%%r12;"
			"movq 0x28(%%rdi), %%r13;"
			"movq 0x30(%%rdi),%%r14;"
			"movq 0x38(%%rdi),%%r15;" 
			"movl %[v],%%eax;"

			"movq 0x18(%%rdi),%[pc];"
			"jmp *%[pc]"
			:[pc]"+r"(pc)
			: "rdi"(env), [v]"r"(val)
			: "rax"
		);
}


