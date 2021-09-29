#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

void multiply_128(uint64_t, uint64_t, uint64_t*, uint64_t*);
void module_128(uint64_t*, uint64_t*, uint64_t);
void srl_128(uint64_t*, uint64_t*, bool);
bool add_128(uint64_t*, unsigned);
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
	bool cin = 0;
	for (int k = 0; k < 64; k++) {
		if ((*lres&0x1) == 1) {
			cin = add_128(hres, a);
		}
		srl_128(hres,lres,cin);
		cin = 0;
	}
}

void srl_128(uint64_t *h_64, uint64_t *l_64, bool cin) {
	*l_64 >>= 1;
	if ((*h_64&0x1)== 1) {
		*l_64 |= 0x1000000000000000;
	}
	*h_64 >>= 1;
	if (cin) {*h_64 |= 0x1000000000000000;}	
}

bool add_128(uint64_t *h_64, unsigned num) {
	uint64_t temp = *h_64;
	*h_64 += num;
	if (*h_64 < temp) {
		return 1;
	}
	return 0;
}

void sub_128(uint64_t *h_64, uint64_t *l_64, unsigned num) {
	uint64_t temp = *l_64;
	*l_64 -= num;
	if (*l_64 > temp) {
		*h_64 -= 1;
	}
}
