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
			"mov %%esp  , %%eax;"
			"mov %%ebx    , (%%eax);"
			"mov %%esi    , 4(%%eax);"
			"mov %%edi    , 8(%%eax);"
			"mov %%ebp    , 12(%%eax);"

			"lea 4(%%esp) , %%ecx;"
			"mov %%ecx    , 16(%%eax);"
			"mov (%%esp)  , %%ecx;"
			"mov %%ecx    , 20(%%eax);"
			: 
			:
			: "ecx", "eax"
	   );
	return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
	/* longjmp(env, val); */
	asm(    
			"movl 4(%%esp)  , %%edx;"
			"movl 8(%%esp)  , %%eax;"
			"test %%eax     , %%eax;"
			"jnz .L1;"
			"inc %%eax;"

			".L1: ;"


			"movl (%%edx)   , %%ebx;"
			"movl 4(%%edx)  , %%esi;"
			"movl 8(%%edx) , %%edi;"
			"movl 12(%%edx) , %%ebp;"
			"movl 16(%%edx) , %%ecx;"
			"movl %%ecx      , %%esp;"


			"movl 20(%%edx) , %%ecx;"
			"jmp *(%%ecx);"

			:
			:
			: "eax", "ebx", "ecx", "edx", "esi"
			);
}
