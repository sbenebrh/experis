#include<stdio.h>

int main()
{
	char name[128];
	int age;
	FILE * fp;
	scanf("%s%d", name, &age);
	if((fp = fopen ("testfile.txt", "w")) == NULL)
	{
		printf("%s\n","cannot open file");
		return -1;
	}
	fprintf(fp, "%s\t%d", name, age);
		
	if(fclose(fp)) 
	{
		printf("%s\n","error to close file" );
		return -1;
	}
	printf("%s\n","close done");

	fp = fopen ("testfile.txt", "r");
	if(fp == NULL)
	{
		printf("%s\n","cannot open file");
		return -1;
	}
	
		fscanf(fp,"%s%d", name, &age);
		printf("name: %s\tage: %d\n",name, age);

	if(fclose(fp)) 
	{
		printf("%s\n","error to close file" );
		return -1;
	}
	printf("%s\n","close done");

	return 0;


}