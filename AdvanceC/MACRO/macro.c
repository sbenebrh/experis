
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define ASSERT(expression) if((expression) == 0) \
							{\
								printf("assertion failed: %s, file: %s,line: %d", #expression, __FILE__, __LINE__);\
								abort();\
							}

#define ASSERT2(ex)		do{((ex) != 0) ? \
							0:\
							write(1,"assertion failed:", strlen("assertion failed:")), \
							write(1,#ex, strlen(#ex)), \
							write(1, "  file:", strlen("  file:")),  \
							write(1, __FILE__, strlen(__FILE__)), \
							write(1," line:", strlen(" line:")), \
							printf(" %d\n", __LINE__),\
							abort() \
							;}while(0)
int main()
{
	ASSERT2(0);
	printf("FAIL\n" );
	return 0;
}