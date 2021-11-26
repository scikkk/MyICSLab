#include <stdint.h>
#include <stdio.h>

int *sieve(int n);

int main() {
  int *primes = sieve(10000000);
  for (int *cur = &primes[9999990], i = 0; *cur; cur++, i++) {
    printf("%8d", *cur);
    if (i % 8 == 7 || !*(cur + 1)) printf("\n");
  }
  printf("wk\n");
}
