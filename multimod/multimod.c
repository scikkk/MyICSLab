#include <stdint.h>
#include <stdlib.h>

void multiply_128(uint64_t, uint64_t, uint64_t*, uint64_t*);
void module_128(uint64_t*, uint64_t*, uint64_t);
void sll_128(uint64_t*, uint64_t*, unsigned);
void add_128(uint64_t*, uint64_t*, unsigned);
void sub_128(uint64_t*, uint64_t*, unsigned);

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t *h_64 = (uint64_t*)malloc(8);
  uint64_t *l_64 = (uint64_t*)malloc(8);
  multiply_128(a, b, h_64, l_64);
  module_128(h_64, l_64, m);
  // return (a * b) % m; // buggy
  return *l_64;
}

void module_128(uint64_t* h_64, uint64_t* l_64, uint64_t m){
	uint64_t temp_l;
	while(*h_64 != 0) {
		temp_l = *l_64;
		*l_64 -= m;
		if (*l_64 > temp_l) {
			*h_64 -= 1;
		}
	}
}

void multiply_128(uint64_t a, uint64_t b, uint64_t *hres, uint64_t *lres) {
	*hres &= 0x0;
	*lres = b;
	for (int k = 0; k < 32; k++) {
	   if ((*lres&0x1) == 1) {
			add_128(hres, lres, a);
	   }
	   sll_128(hres,lres,1);
	}
}

void sll_128(uint64_t *h_64, uint64_t *l_64, unsigned num) {
	for (unsigned k = 0; k < num; k++){
		*h_64 <<= 1;
		if ((*l_64|0x8000000000000000) != 0) {
			*h_64 |= 0x1;
		}
		*l_64 <<= 1;
	}
}

void add_128(uint64_t *h_64, uint64_t *l_64, unsigned num) {
	uint64_t temp = *l_64;
	*l_64 += num;
	if (*l_64 < temp) {
		*h_64 += 1;
	}
}

void sub_128(uint64_t *h_64, uint64_t *l_64, unsigned num) {
	uint64_t temp = *l_64;
	*l_64 -= num;
	if (*l_64 > temp) {
		*h_64 -= 1;
	}
}
