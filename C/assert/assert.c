#include<stdio.h>
#include <assert.h>

int main(){
	int i = 20;
	assert (i == 10);
	printf("after i != %d\n", i);
	assert(i == 20);
	printf("after i ==20");
	return 0;
}

