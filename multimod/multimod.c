#include <stdint.h>
uint64_t add_multimod(uint64_t a, uint64_t b, uint64_t m) {
    if (a + b < a || a + b < b) {
	 return ((a + b) %m + (-1ULL)%m + 1)%m;
	}
	else {
	return (a+b)%m;
	}
}
uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
	uint64_t res = 0;
	while(b != 0){
	if ((b&0x1)==1){
	res = add_multimod(res, a, m);
	}
	a = add_multimod(a,a,m);
	b >>= 1;
	
	}
	return res;
}

