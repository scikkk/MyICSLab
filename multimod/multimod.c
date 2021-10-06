#include <stdint.h>

void multiply_128(uint64_t, uint64_t, uint64_t*, uint64_t*);
void module_128(uint64_t*, uint64_t*, uint64_t);
void srl_128(short , uint64_t*, uint64_t*);

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
	short len = 64;
	while((m>>(len-1))==0) {len--;}
	short len_0 = 64 - len;
	while (len_0 >= 0){
		while (a >= (m<<len_0)) {
			a -= (m<<len_0);
		}
		len_0--;
	}
	len_0 = 64 - len;
	while (len_0 >= 0){
		while (b >= (m<<len_0)) {
			b -= (m<<len_0);
		}
		len_0--;
	}
	uint64_t h, l;
	uint64_t *h_64 = &h;
	uint64_t *l_64 = &l;
	multiply_128(a, b, h_64, l_64);
	module_128(h_64, l_64, m);
	return *l_64;
}

void module_128(uint64_t* h_64, uint64_t* l_64, uint64_t m){
	uint64_t temp_l;
	short len = 64;
	while((m>>(len-1))==0) {len--;}
	short len_0 = 64 - len;
	while (len_0 >= 0){
		while (*h_64 >= (m<<len_0)) {
			*h_64 -= (m<<len_0);
		}
		len_0--;
	} 
	len_0 = 64 - len;
	short r_num = 0;
	while (len_0 >= 0){
		while (*h_64 != 0 || *l_64 >= (m<<len_0)) {
			temp_l = *l_64;
			*l_64 -= (m<<len_0);
			if (*l_64 > temp_l) {
				*h_64 -= 1;
			}
			if ((*l_64 & 0x1) == 0) {
				srl_128(0,h_64,l_64);
				r_num++;
			}
		}
		if(r_num >0 )	{
			*h_64 <<= r_num;
			*h_64 |= *l_64 >> (64 - r_num);
			*l_64 <<= r_num;
		}
		r_num = 0;
		len_0--;
	}
	while (*h_64 != 0 || *l_64 >= m) {
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
	short cout1 = 0;
	short cout2 = 0;
	short y0 = 0,y1;
	for (int k = 0; k < 65; k++) {
		y1 = *lres&0x1;
		if (y0-y1==1) {
			uint64_t h_63_0 = *hres;
			h_63_0 >>= 1;
			if (cout1) {h_63_0 |= 0x8000000000000000;}
			uint64_t temp = h_63_0;
			h_63_0 += a;
			if (temp > h_63_0) {cout2 = 1 - cout2;}
			cout1 = ((h_63_0&0x8000000000000000) == 0x8000000000000000);
			if ((*hres & 0x1) == 0){
				*hres = h_63_0;
				*hres <<= 1;
			}
			else {
				*hres = h_63_0;
				*hres <<= 1;
				*hres |= 0x1;
			}
		}
		else if (y1 - y0 == 1){
			uint64_t h_63_0 = *hres;
			h_63_0 >>= 1;
			if (cout1) {h_63_0 |= 0x8000000000000000;}
			uint64_t temp = h_63_0;
			h_63_0 -= a;
			if (temp < h_63_0) {cout2 = 1 - cout2;}
			cout1 = ((h_63_0&0x8000000000000000) == 0x8000000000000000);
			if ((*hres & 0x1) == 0){
				*hres = h_63_0;
				*hres <<= 1;
			}
			else {
				*hres = h_63_0;
				*hres <<= 1;
				*hres |= 0x1;
			}
		}
		srl_128(cout1, hres,lres);
		cout1 = cout2;
		y0 = y1;
	}
}

void srl_128( short c1, uint64_t *h_64, uint64_t *l_64) {
	*l_64 >>= 1;
	if ((*h_64&0x1)== 1) {
		*l_64 |= 0x8000000000000000;
	} 
	*h_64 >>= 1;
	if (c1 == 1 ){
		*h_64 |= 0x8000000000000000; 
	}
}


