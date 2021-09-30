#include <stdint.h>
#include <string.h>
//#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define U64 "%" PRIu64

void py_mod( char *res){
	/* sprintf(exec, "python3 -c 'print((" U64 "*" U64 ")%%" U64 ")'", a,b,m); */
//	printf("%s\n",exec);
	FILE *fp = popen(res, "r");
	assert(fp);
	char buf[100];
	fscanf(fp, "%s", buf);
//	printf("py_mod returns: %s\n", buf);
//	printf("%s\n", buf);
    strcpy(res, buf);
	pclose(fp);
	/* FILE *fp = popen("python3 -c 'print(10**10 - 1)'", "r"); */
	/* assert(fp); */
	/* char buf[100]; */
	/* fscanf(fp, "%s", buf); */
	/* printf("popen() returns: %s\n", buf); */
	/* pclose(fp); */
}
