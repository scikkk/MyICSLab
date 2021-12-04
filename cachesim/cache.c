#include "common.h"
#include <inttypes.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);

typedef uint32_t[16] Block;
typedef struct{
	Block data;
	bool valid;
} cache_line;

cache_line *cache;
static int lu = 0;


static uint64_t cycle_cnt = 0;

void cycle_increase(int n) { cycle_cnt += n; }

// TODO: implement the following functions

uint32_t cache_read(uintptr_t addr) {
  return 0;
}

void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
}

void init_cache(int total_size_width, int associativity_width) {
	cache = malloc(exp2(total_size_width)+exp2(total_size_width)/64);
	lu = exp2(associativity_width);
}

void display_statistic(void) {
}
