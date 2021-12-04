#include "common.h"
#include <inttypes.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);


typedef struct{
	uint32_t data[16];
	uint64_t kuai_no;
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
	uint64_t kuai_qun = addr >> BLOCK_WIDTH;
	int zu_no = kuai_qun%zu;
	int begin_line = zu_no*lu;
	// search data in cache
	for(int k = 0; k < lu; k++){
		if((cache[k+begin_line].kuai_no == kuai_qun) && cache[k+begin_line].valid){
			printf("%d:hit read quai_num =%lu\n", __LINE__, kuai_qun);
			return cache[k+begin_line].data[(addr>>2)&0xf];
		} 
	}
	// find out if there is a blank line
	for(int k = 0; k <= lu; k++){
		if(!cache[k+begin_line].valid || k == lu){
			if (k == lu) {
				k = rand()%lu;
				if(cache[k+begin_line].dity){
					mem_write(cache[k+begin_line].kuai_no, (uint8_t*)&cache[k+begin_line].data[0]);
					printf("%d:write back kuai_num =%lu\n", __LINE__, cache[k+begin_line].kuai_no);
				}	
			}
			mem_read(kuai_qun, (uint8_t*)&cache[k+begin_line].data[0]);
			cache[k+begin_line].valid = 1;
			cache[k+begin_line].dity = 0;
			cache[k+begin_line].kuai_no = kuai_qun;
			printf("%d:load read kuai_num =%lu\n", __LINE__, kuai_qun);
			return cache[k+begin_line].data[(addr>>2)&0xf];
		}
	}
	printf("LINE==%d\n", __LINE__);
	return 0;
}

void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {

	uint64_t kuai_qun = addr >> BLOCK_WIDTH;
	int zu_no = kuai_qun%zu;
	int begin_line = zu_no*lu;
	// search data in cache
	for(int k = 0; k < lu; k++){
		if((cache[k+begin_line].kuai_no == kuai_qun) && cache[k+begin_line].valid){
			uint32_t *p = &cache[k+begin_line].data[(addr>>2)&0xf];
			*p = (*p & ~wmask) | (data & wmask);
			cache[k+begin_line].dity = 1;
					printf("%d:hit write kuai_num =%lu\n", __LINE__, kuai_qun);
			return;
		}
	}
	// find out if there is a blank line
	for(int k = 0; k <= lu; k++){
		if(!cache[k+begin_line].valid || k == lu){
			if (k == lu) {
				k = rand()%lu;
				if(cache[k+begin_line].dity){
					mem_write(cache[k+begin_line].kuai_no, (uint8_t*)&cache[k+begin_line].data[0]);
					printf("%d:write back kuai_num =%lu\n", __LINE__, cache[k+begin_line].kuai_no);
				}	
			}
			mem_read(kuai_qun, (uint8_t*)&cache[k+begin_line].data[0]);
			cache[k+begin_line].valid = 1;
			cache[k+begin_line].kuai_no = kuai_qun;
			uint32_t *p = &cache[k+begin_line].data[(addr>>2)&0xf];
			*p = (*p & ~wmask) | (data & wmask);
			cache[k+begin_line].dity = 1;
					printf("%d:load write kuai_num =%lu\n", __LINE__, kuai_qun);
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
