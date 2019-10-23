#include<stdio.h>
#include"prog.h"
#include"libx.h"

int func_b(void)
{
	x2();
	return printf("%s\n","call func_b" );
	
}