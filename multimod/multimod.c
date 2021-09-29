#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
void multiply_128(uint64_t, uint64_t, uint64_t*, uint64_t*);
void module_128(uint64_t*, uint64_t*, uint64_t);
void srl_128(uint64_t*, uint64_t*);
bool add_128(uint64_t*, unsigned);
void sub_128(uint64_t*, uint64_t*, unsigned);

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
	while(a >= m) {a -= m;}
	while(b >= m) {b -= m;}
	uint64_t *h_64 = (uint64_t*)malloc(8);
	uint64_t *l_64 = (uint64_t*)malloc(8);
	printf("0x%lx%lx\n", *h_64, *l_64);
	multiply_128(a, b, h_64, l_64);
	printf("0x%lx%lx\n", *h_64, *l_64);
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
	while (*l_64 >= m) {*l_64 -= m;}
}

void multiply_128(uint64_t a, uint64_t b, uint64_t *hres, uint64_t *lres) {
	*hres &= 0x0;
	*lres = b;
	short y0 = 0,y1;
	for (int k = 0; k < 64; k++) {
        y1 = *lres&0x1;
		if (y0-y1==1) {
			add_128(hres, a);
		}
		else if (y1 - y0 == 1){
		*hres-= a;
		}
		srl_128(hres,lres);
		y0 = y1;
	}
}

void srl_128(uint64_t *h_64, uint64_t *l_64 ) {
	*l_64 >>= 1;
	if ((*h_64&0x1)== 1) {
		*l_64 |= 0x8000000000000000;
	} 
	if ((*h_64>>63)==1){
	
	*h_64 >>= 1;
	*h_64 |= 0x8000000000000000; 
	}
	else{
	*h_64 >>= 1;
	}
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
