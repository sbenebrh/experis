#include<stdio.h>
#include"prog.h"


int func_a(void)
{
	func_c();
	return printf("%s\n","call func_a" );
	
}

int main()
{
	func_a();
	func_b();
	func_c();
}