#include<stdio.h>

int main(){
	int arr[2] = {0,1};
	int* p = arr;
	int* ptr  = arr;
	int* y = ptr - p;
	ptr++;
	printf("%d\n", y);
}