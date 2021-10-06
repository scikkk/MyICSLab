#include <stdint.h>
uint64_t mod(uint64_t sum, uint64_t m) {
    
	return sum%m;
}
uint64_t addmod(uint64_t a, uint64_t b, uint64_t m) {
    if (a + b < a || a + b < b) {
	 uint64_t res =  mod(mod(a+b, m) + mod(-1ULL, m) + 1,m);
	 
	 return res;
	}
	else {
	return mod(a+b,m);
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

