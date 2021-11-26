#include <stdint.h>
#include <stdio.h>

int *sieve(int n);

int main() {
  int *primes = sieve(400);
  for (int *cur = primes, i = 0; *cur; cur++, i++) {
    printf("%8d", *cur);
    if (i % 8 == 7 || !*(cur + 1)) printf("\n");
  }
  printf("wk\n");
  	for(int k = 100, count = 0; k < MAXSIZE; k++){
		bool newline = false;
		if(is_prime[k]){
			newline = true;
			count++;
			cout << k << ' ';
		}
		if (newline && count % 10 == 0){
			cout << '\n';
		}
	}
}
