#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
void multiply_128(uint64_t, uint64_t, uint64_t*, uint64_t*);
void module_128(uint64_t*, uint64_t*, uint64_t);
void srl_128(bool, uint64_t*, uint64_t*);

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
	printf("0x%016lx %016lx\n", a, b);
	while(a >= m) {a -= m;printf("%lu\n",a);}
	while(b >= m) {b -= m;printf("%lu\n", b);}
	uint64_t *h_64 = (uint64_t*)malloc(8);
	uint64_t *l_64 = (uint64_t*)malloc(8);
	printf("0x%016lx %016lx\n", a, b);
	multiply_128(a, b, h_64, l_64);
	printf("0x%016lx %016lx\n", *h_64, *l_64);
	module_128(h_64, l_64, m);
	// return (a * b) % m; // buggy
	return *l_64;
}

void module_128(uint64_t* h_64, uint64_t* l_64, uint64_t m){
	uint64_t temp_l;
	while (*h_64 >= m) {*h_64 -= m;}
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
	bool cout1 = 0;
	bool cout2 = 0;
	short y0 = 0,y1;
	for (int k = 0; k < 65; k++) {
		y1 = *lres&0x1;
		printf("0x%d%d %016lx %016lx %d%d\n",cout2, cout1, *hres, *lres, y1, y0);
		if (y0-y1==1) {
			uint64_t temp = *hres;
			*hres += (a<<1);
			if (temp > *hres){
				if (cout1){
					cout1 = 0;
					cout2 = !cout2;
				}
				else {
					cout1 = 1;
				}
			}
			if ((a & 0x8000000000000000) != (a & 0x4000000000000000)){
				if (cout1) {
					cout1 = 0;
					cout2 = 1;
				}
				else {
					cout1 = 1;
				}

			}
		}
		else if (y1 - y0 == 1){
			uint64_t temp = *hres;
			*hres-= (a<<1);
			if(*hres > temp) {
				if (cout1) {
					cout1 = 0;

				}
				else if(cout2) {
					cout1 = 1;
					cout2 = 0;
				}
				else {
					cout1 = 1;
					cout2 = 1;
				}
			}
			if ((a & 0x8000000000000000) != (a & 0x4000000000000000)) {
				if (cout1) {
					cout1 = 0;

				}
				else if(cout2) {
					cout1 = 1;
					cout2 = 0;
				}
				else {
					cout1 = 1;
					cout2 = 1;
				}
			}
		}
		srl_128(cout1, hres,lres);
		cout1 = cout2;
		y0 = y1;
	}

		printf("0x%d%d %016lx %016lx %d%d\n",cout2, cout1, *hres, *lres, y1, y0);
}

void srl_128( bool c1, uint64_t *h_64, uint64_t *l_64) {
	*l_64 >>= 1;
	if ((*h_64&0x1)== 1) {
		*l_64 |= 0x8000000000000000;
	} 
	*h_64 >>= 1;
	if (c1 ){
		*h_64 |= 0x8000000000000000; 
	}
}


