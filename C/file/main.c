#include<stdio.h>
#include"files.h"
void testfiles1()
{
	PrintNLastLines("main.c", 10);
}
void testfiles2()
{
	PrintNLastLines("testfile.txt", 4);
}
void testfiles3()
{
	FrequenciesWords("testfile.txt");
}
int main()
{
	/*testfiles1();
	testfiles2();*/
	int age;
	char name[20];
	DictNumberOfLetters("testfile");
	testfiles3();
	printf("%s\n", "what is your name and age?" );
	scanf("%s%d", name, &age);
	inBinaryFile("resultBinaryFile.txt", name, age);
	return 0;
}
