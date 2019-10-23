#include <stdio.h>
#include<stdlib.h>


Test_Result fileHash()
{
	FILE* file;
	char word[128];

	HashMap* hash = HashMap_Create(2000000, myhashFunc,strCmp);
	if(!hash)
	{
		return fail;
	}

	file = fopen("testfile.txt", "r");
	if(file == NULL)
	{
		return FAIL;
	}
	while( fscanf(file,"%s",word) != EOF && ftell(file) + 1 != EOF)
	{
		if(HashMap_Insert(hash, word,0) == MAP_SUCCESS)
		{
			continue;
		}
	}
}