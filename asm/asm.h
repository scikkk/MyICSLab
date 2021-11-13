#include <stdint.h>
#include <stddef.h>

/* #define asm_jmp_buf jmp_buf */

typedef struct {
	void* ebx;
	/* void* edx; */
	void* esi;
	void* edi;
	void* ebp;
	void* esp;
	void* eip;
} asm_jmp_buf;

int64_t asm_add(int64_t a, int64_t b);
int     asm_popcnt(uint64_t x);
void   *asm_memcpy(void *dest, const void *src, size_t n);
int     asm_setjmp(asm_jmp_buf env);
void    asm_longjmp(asm_jmp_buf env, int val);
