#include <stdint.h>
uint64_t inplacemod(uint64_t a, uint64_t b, uint64_t m) {

	return (a+b)%m;
}
uint64_t addmod(uint64_t a, uint64_t b, uint64_t m) {
    if (a + b < a || a + b < b) {
	 uint64_t res =  inplacemod(a, b, m) + inplacemod(-1ULL, 0 , m);
	 if (res + 1 < m) {
	 return res + 1;
	 }
	 else {
	 return 0;
	 }
	}
	else {
	return inplacemod(a,b,m);
	}
}
uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
	uint64_t res = 0;
	while(b != 0){
	if ((b&0x1)==1){
	res = addmod(res, a, m);
	}
	a = addmod(a,a,m);
	b >>= 1;
	
	}
	return res;
}

