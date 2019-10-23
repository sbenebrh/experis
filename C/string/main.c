#include<stdio.h>
#include<ctype.h>
#include"string_function.h"

typedef char* (*str)(char*, const char*);

char* operateStringFunc(str f , char* _source, char* _destination)
{
	return f(_source, _destination);
}

int main ()
{
	char source[64];
	char destination[64];
	int result1;
	int menuChoice = 1;
	
	str strfunc[2] = {strcopy, myStrcat};
	printf(" Welcome what do you want to do\n");
	
	while(menuChoice)
	{
		printf("--press 1 for copy\n"
		       "--press 2 for concatenate 2 string\n"
		       "--press 3 for comparate 2 string\n"
		       "--press 4 for ascii to int\n"
		       "--press 0 to exit\n");
		scanf("%d", &menuChoice);
		
		if(1 ==  menuChoice)
		{
			break;
		} 
		if(menuChoice == 1 || menuChoice == 2)
		{
			printf("enter a source \t");
			scanf("%s", source);
			printf("enter a destination \t");
			scanf("%s", destination);
			
			printf("%s\n", operateStringFunc(strfunc[menuChoice - 1],source, destination));
			
		 }
		 else if (menuChoice == 3)
		 {
		 	
			printf("enter a source \t");
			scanf("%s", source);
			printf("enter a destination \t");
			scanf("%s", destination);
			result1 = mystrcmp(source, destination);
			printf("%d", result1);
		}
		else if (menuChoice == 4)
		{
			printf("enter a source \t");
			scanf("%s", source);
			result1 = charToInt(source);
			printf("%d", result1);
		}
		
	}
	
	return 0;
}
