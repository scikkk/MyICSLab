#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define N 10000000

static bool is_prime[N];
static int  primes[N];

int *sieve(int n) {
	assert(n + 1 < N);

	/* for (int i = 2; i <= n; i++) { */
	/*   for (int j = i + i; j <= n; j += i) { */
	/*     is_prime[j] = false; */
	/*   } */
	/* } */

	/* for (int i = 2; i <= n; i++) */
	/*   if (is_prime[i]) { */
	/*     *p++ = i; */
	/*   } */
	/* *p = 0; */
	/* return primes; */
	int primesize = 0;
	memset(is_prime, 4, N);

	/* for (int i = 0; i <= n; i++) */
	/* 	is_prime[i] = true; */
	is_prime[1] = false;
	for(int i=1; i<=n; i++, i++)
	{
		if(is_prime[i]) primes[primesize++] = i;
	int *p = primes;
		for(int j=0; j < primesize && i*(*p) <= n; ++j)
		{
			is_prime[i*(*p)] = false;
			if(i%(*p) == 0) break;
			p++;
		}
	}
	return primes;
}
