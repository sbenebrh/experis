#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"files.h"
#include"map.h"
#include"ADTErr.h"
typedef struct Map
{
	char 	m_letter;
	int 	m_occurence;
}Map;


void PrintNLastLines(char* _filePath, int _nLastLines)
{
	int posNLastLine[_nLastLines] ;
	int pos, i, index = 0, line = 1;
	char words[1024];

	FILE * file = fopen(_filePath,"r");
	if(file == NULL)
	{
		return;
	}

	posNLastLine[0] = 0;
	while(fgets(words, 1024, file) != NULL )
	{	
		pos = ftell(file);
		index = (index + 1) % _nLastLines;
		posNLastLine[index] = pos;
		
		line += 1;

	}

	if(line < _nLastLines)
	{
		_nLastLines = line;
	}
	
	fseek(file,posNLastLine[index],0);

	for(i = 0; i < _nLastLines; i++)
	{

		if(fgets(words,1024,file))
		{
			printf("%s",words );
		}
	}

	fclose(file);
	free(file);

}



void DictNumberOfLetters(char* _filePath)
{
	int freq[52] ={0};
	char letter;
	int i = 0;
	FILE * file = fopen(_filePath,"r");
	if(file == NULL)
	{
		return;
	}
	do
	{
		if(feof(file))
		{
			break;
		}

		letter = fgetc(file);
		if(letter >='a' && letter <= 'z')
        {
            freq[(letter - 'a')*2]++;
        }
        else if(letter >='A' && letter <= 'Z')
        {
            freq[(letter - 'A' )*2 + 1]++;
        }
	}
	while(!feof(file));

	if(fclose(file))
	{
		return;
	}

	file = fopen("resultQuestion2.txt","w");
	if(!file)
	{
		return;
	}
	for(i = 0; i < 52; i++)
	{
		 if(freq[i] != 0 && i % 2 == 0)
        {
            fprintf(file,"'%c' %d\n", (i/2)+'a', freq[i]);
        }
        if(freq[i] != 0 && i % 2 != 0)
        {
        	fprintf(file,"'%c' %d\n", (i/2) - 1 +'A', freq[i]);
        }
	}
	if(! fclose(file))
	{
		return;
	}
	free(file);

}
/*TODO check creation of vector*/
void FrequenciesWords(char* _fileName)
{
	FILE* file;
	Vector* vector;
	char word[128];
	int i,flag = 0;

	if(!_fileName)
	{
		return;
	}
	file = fopen(_fileName, "r");
	if(!file)
	{
		return;
	}
	vector = createVector(10);
	if(NULL == vector)
	{
		fclose(file);
		return;
	}

	while( fscanf(file,"%s",word) != EOF && ftell(file) + 1 != EOF)
	{
		for(i = 0;i < CounterWords(vector); i++)
		{
			if(strcmp(word, getWord(vector, i)) == 0)
			{
				increment(vector,i);
				flag = 1;
				break;
			}
			
		}
		if(flag == 0)
		{
			if(addWord(vector,word) != ERR_OK)
			{
				fclose(file);
				DestroyVector(vector);

				return;
			}

		}
		flag = 0;
	}
	fclose(file);

	file = fopen("Result3.txt", "w");
	for(i = 0;i < CounterWords(vector); i++)
	{
		fprintf(file, "%s\t%d\n",getWord(vector, i), getFrequence(vector, i) );
	}
	DestroyVector(vector);


}


void inBinaryFile(const char* _fileName, char * _name,const int _age)
{
	FILE* file;
	int nBytes;
	int age;
	char* name;
	file = fopen(_fileName,"wb");
	if(NULL == file)
	{
		return;
	}
	nBytes = fwrite(_name, sizeof(char)  , strlen(_name) + 1, file);
	nBytes = fwrite(&_age, sizeof(int), 1, file);

	if(NULL == (name = (char*) malloc((strlen(_name) + 1) * sizeof(char))))
	{
		fclose(file);
		return ;
	}

	nBytes = fread(name, sizeof(char), (strlen(_name) + 1) , file);
	nBytes = fread(&age,sizeof(int), 1, file);

	printf("%s\t %d\n", name, age);
	fclose(file);


}