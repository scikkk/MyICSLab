#include <stdint.h>
#include <stddef.h>

/* #define asm_jmp_buf jmp_buf */

typedef struct {
	void* rsv; // 0(eax)
	void* ebx; // 4
	void* ecx; // 8
	void* edx; // 12
	void* esi; // 16
	void* edi; // 20
	void* ebp; // 24
	void* esp; // 28
	void* eip; // 32
} asm_jmp_buf;

int64_t asm_add(int64_t a, int64_t b);
int     asm_popcnt(uint64_t x);
void   *asm_memcpy(void *dest, const void *src, size_t n);
int     asm_setjmp(asm_jmp_buf env);
void    asm_longjmp(asm_jmp_buf env, int val);
