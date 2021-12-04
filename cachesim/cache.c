#include "common.h"
#include <inttypes.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);


typedef struct{
	uint32_t data[16];
	uint64_t addr;
	bool valid;
	bool dity;
} cache_line;

cache_line *cache;
static int lu = 0;
static int zu = 0;


static uint64_t cycle_cnt = 0;

void cycle_increase(int n) { cycle_cnt += n; }

// TODO: implement the following functions

uint32_t cache_read(uintptr_t addr) {
	int kuai_qun = (int)addr/16;
	int zu_no = kuai_qun%zu;
	int begin_line = zu_no*lu;
	uintptr_t begin_addr = addr - addr%16;
	// search data in cache
	for(int k = 0; k < lu; k++){
		if((cache[k+begin_line].addr == begin_addr) && cache[k+begin_line].valid){
			return cache[k+begin_line].data[addr & 0xf];
		} 
	}
	// find out if there is a blank line
	for(int k = 0; k <= lu; k++){
		if(!cache[k+begin_line].valid || k == lu){
			if (k == lu) {
				k = rand()%lu;
				if(cache[k+begin_line].dity){
					mem_write(kuai_qun, (uint8_t*)&cache[k+begin_line].data[0]);
				}	
			}
			mem_read(kuai_qun, (uint8_t*)&cache[k+begin_line].data[0]);
			cache[k+begin_line].valid = 1;
			cache[k+begin_line].dity = 0;
			cache[k+begin_line].addr = begin_addr;
			return cache[k+begin_line].data[addr & 0xf];
		}
	}
	return 0;
}

void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {

	int kuai_qun = (int)addr/16;
	int zu_no = kuai_qun%zu;
	int begin_line = zu_no*lu;
	uintptr_t begin_addr = addr - addr%16;
	// search data in cache
	for(int k = 0; k < lu; k++){
		if((cache[k+begin_line].addr == begin_addr) && cache[k+begin_line].valid){
			cache[k+begin_line].data[addr & 0xf] = data&wmask;
			cache[k+begin_line].dity = 1;
			return;
		}
	}
	// find out if there is a blank line
	for(int k = 0; k <= lu; k++){
		if(!cache[k+begin_line].valid || k == lu){
			if (k == lu) {
				k = rand()%lu;
				if(cache[k+begin_line].dity){
					mem_write(kuai_qun, (uint8_t*)&cache[k+begin_line].data[0]);
				}	
			}
			uint8_t d[64];
			/* mem_read(kuai_qun, (uint8_t*)&cache[k+begin_line].data[0]); */
			mem_read(kuai_qun, d);

			cache[k+begin_line].valid = 1;
			cache[k+begin_line].addr = begin_addr;
			cache[k+begin_line].data[addr & 0xf] = data&wmask;
			cache[k+begin_line].dity = 1;
			return;
		}
	}
}

void init_cache(int total_size_width, int associativity_width) {
	lu = exp2(associativity_width);
	zu = exp2(total_size_width-associativity_width) / 64;
	cache = malloc(lu*zu*74);
	for(int k = 0; k < lu*zu; k++){
		cache[k].valid = 0;
		cache[k].dity = 0;
	}
}

void display_statistic(void) {
}
