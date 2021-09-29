#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
void py_mod(uint64_t a,uint64_t b, uint64_t m ){
	char exec[120];
	sprintf(exec, "python3 -c 'print((%lu*%lu)%%%lu)'", a,b,m);
	printf("%s\n",exec);
	FILE *fp = popen(exec, "r");
	assert(fp);
	char buf[100];
	fscanf(fp, "%s", buf);
	printf("py_mod returns: %s\n", buf);
	pclose(fp);
	/* FILE *fp = popen("python3 -c 'print(10**10 - 1)'", "r"); */
	/* assert(fp); */
	/* char buf[100]; */
	/* fscanf(fp, "%s", buf); */
	/* printf("popen() returns: %s\n", buf); */
	/* pclose(fp); */
}
