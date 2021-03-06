/* #include <stdbool.h> */
#include <stdint.h>
/* #include <stdlib.h> */
/* #include <stdio.h> */
void multiply_128(uint64_t, uint64_t, uint64_t*, uint64_t*);
void module_128(uint64_t*, uint64_t*, uint64_t);
void srl_128(short , uint64_t*, uint64_t*);

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
	// printf("0x%016lx %016lx\n", a, b);
	/*
	   short count = 0;
	   while(a >= m && count < 10000) {
	   a -= m;
	   count++;
	//	printf("%lu\n",a);
	}
	while(b >= m && count < 20000) {
	b -= m;
	count++;
	// printf("%lu\n", b);
	}
	*/
	short len = 64;
	while((m>>(len-1))==0) {len--;}
	short len_0 = 64 - len;
	while (len_0 >= 0){
		while (a >= (m<<len_0)) {
			a -= (m<<len_0);
			//	printf("0x%016lx %016lx\n", *h_64, *l_64);
		}
		len_0--;
	}
	len_0 = 64 - len;
	while (len_0 >= 0){
		while (b >= (m<<len_0)) {
			b -= (m<<len_0);
			//	printf("0x%016lx %016lx\n", *h_64, *l_64);
		}
		len_0--;
	}
    uint64_t h, l;
	uint64_t *h_64 = &h;
	uint64_t *l_64 = &l;
	// printf("0x%016lx %016lx\n", a, b);
	multiply_128(a, b, h_64, l_64);
//	printf("0x%016lx %016lx\n", *h_64, *l_64);
	module_128(h_64, l_64, m);
	// return (a * b) % m; // buggy
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
			//	printf("0x%016lx %016lx\n", *h_64, *l_64);
		}
		len_0--;
	} 
	len_0 = 64 - len;
	short r_num = 0;
	while (len_0 >= 0){
		//	printf("0x%016lx %016lx\n", *h_64, *l_64);
		while (*h_64 != 0 || *l_64 >= (m<<len_0)) {
			temp_l = *l_64;
			*l_64 -= (m<<len_0);
			if (*l_64 > temp_l) {
				*h_64 -= 1;
			}
			//	printf("0x%016lx %016lx\n", *h_64, *l_64);
			if ((*l_64 & 0x1) == 0) {
				srl_128(0,h_64,l_64);
				r_num++;
				//	printf(">>1: 0x%016lx %016lx\n", *h_64, *l_64);
			}
		}
		if(r_num >0 )	{
			*h_64 <<= r_num;
			*h_64 |= *l_64 >> (64 - r_num);
			*l_64 <<= r_num;
		}
		//	printf("<<%d: 0x%016lx %016lx\n\n", r_num,*h_64, *l_64);
		r_num = 0;
		len_0--;
	}
	while (*h_64 != 0 || *l_64 >= m) {
		temp_l = *l_64;
		*l_64 -= m;
		if (*l_64 > temp_l) {
			*h_64 -= 1;
		}
		//	printf("0x%016lx %016lx\n", *h_64, *l_64);
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
		//	printf("0x%d%d %016lx %016lx %d%d\n",cout2, cout1, *hres, *lres, y1, y0);
		if (y0-y1==1) {
			uint64_t h_63_0 = *hres;
			h_63_0 >>= 1;
			if (cout1) {h_63_0 |= 0x8000000000000000;}
			uint64_t temp = h_63_0;
			//	printf("temp: %016lx\n",temp);
			h_63_0 += a;
			//	printf("h_63_0: %016lx\n",h_63_0);
			//	if ((temp > h_63_0&&(a>>63)==0x0)||((temp < h_63_0)&&(a>>63)==0x1)) {cout2 = !cout2;}
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
			//	printf("temp: %016lx\n",temp);
			h_63_0 -= a;
			//	printf("h_63_0: %016lx\n",h_63_0);
			//	if ((temp < h_63_0&&(a>>63)==0x0)||((temp > h_63_0)&&(a>>63)==0x1)) {cout2 = !cout2;}
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
		//	printf("0x%d%d %016lx %016lx %d%d\n\n",cout2, cout1, *hres, *lres, y1, y0);
		srl_128(cout1, hres,lres);
		cout1 = cout2;
		y0 = y1;
	}

	//	printf("0x%d%d %016lx %016lx %d%d\n",cout2, cout1, *hres, *lres, y1, y0);
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


