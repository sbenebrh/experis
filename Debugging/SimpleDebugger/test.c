#include<stdio.h>

/*#pragma pack*/

int IsLittle()
{
	unsigned int i = 1;
	if(*(char*)&i)
	{
		return 1;
	}
	return 0;
}
struct test_sizes
{
	char c1;
	long num1;
	char c2;
};
int main()
{
	/*struct items
	{
		char c1;
		long num;
	}items1,items2;
	int res; 
	items1.c1 = 'a';
	items2.c1 = 'a';
	items1.num = 15;
	items2.num = 15;
	printf("%d\n", sizeof(items1));
	printf("%d\n", sizeof(items2));
	res = memcmp(&items1,&items2,sizeof(items1));
	printf("%d\n", IsLittle());
	if(res != 0) printf("not equal!");
	return 0;*/
	
	int n = 5;
	int j = 4;
	int num;
	num = 3,4,5;
	printf("%d\n",(j++,n++,6));
	printf("%d\n",(3,4,5));
	printf("%d\n",num );
	printf("%d", num = (3,4,5));
	
	
	return 0;
}
