#include <stdint.h>

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
	uint64_t res = 0;
	while(b != 0){
	if ((b&0x1)==1){
	res = (res+a)%m;
	}
	a = (a+a)%m;
	b >>= 1;
	
	}
	return res;
}
