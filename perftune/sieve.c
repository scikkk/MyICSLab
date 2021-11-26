#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define N 10000000

static bool is_prime[N];
static int  primes[N];

int *sieve(int n) {
  assert(n + 1 < N);
  /* for (int i = 0; i <= n; i++) */
  /*   is_prime[i] = true; */

  /* for (int i = 2; i <= n; i++) { */
  /*   for (int j = i + i; j <= n; j += i) { */
  /*     is_prime[j] = false; */
  /*   } */
  /* } */

  /* int *p = primes; */
  /* for (int i = 2; i <= n; i++) */
  /*   if (is_prime[i]) { */
  /*     *p++ = i; */
  /*   } */
  /* *p = 0; */
  /* return primes; */
  	short primesize = 0;
    memset(is_prime,1,sizeof(is_prime));
    is_prime[1]=false;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i])primes[primesize++]=i;
         for(int j=0;j<primesize&&i*primes[j]<=n;j++)
         {
            is_prime[i*primes[j]]=false;
            if(i%primes[j]==0)break;
        }
    }
    return primes;
}
