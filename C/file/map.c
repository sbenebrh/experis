#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"map.h"
#include"ADTErr.h"

typedef struct Map
{
	char 	m_word[128];
	size_t 	m_frequence;
}Map;


struct Vector
{
  	size_t 	m_size;
	Map*	*m_maps;
	size_t m_nitems;
};

Vector* createVector(size_t _size)
{
	Vector* newVector = (Vector*) calloc(1, sizeof(Vector));
	 if(NULL == newVector)
	{
		return NULL;
	}
	if(NULL == (newVector -> m_maps = (Map**) calloc(_size,sizeof(Map*))))
	{
		free(newVector);
		return NULL;
	}
	newVector -> m_size = _size;
	return newVector;
}
void DestroyVector( Vector* _vector)
{
	int i;
	if(_vector)
	{
		if(_vector -> m_maps)
		{
			for (i = _vector -> m_nitems; i ; --i)
			{
				free(_vector -> m_maps[i]);
			}
			free(_vector -> m_maps);
		}
		free(_vector);
	}
}
Map* createMap(char _word[128])
{
	Map* newMap = (Map*) malloc(sizeof(Map));
	if(NULL == newMap)
	{
		return NULL;
	}
	strcpy(newMap -> m_word, _word);
	newMap -> m_frequence = 0;
	
	return newMap;
	
}
ADTErr addWord(Vector* _vector, char _word[128])
{
	Map* *temp = NULL;
	Map* newMap = createMap(_word);
	if(NULL == newMap)
	{
		return ERR_UNINITIALIZED;
	} 
	if(_vector -> m_size == _vector -> m_nitems)
	{
	temp = (Map**)realloc(_vector -> m_maps, (_vector -> m_size * 2) * sizeof(Map*));
		if(NULL == temp)
		{
			return ERR_REALLOCATION;
		}
		_vector -> m_maps = temp;
		_vector -> m_size *= 2;
	}
	_vector -> m_maps[_vector -> m_nitems] = newMap;
	_vector -> m_maps[_vector -> m_nitems] -> m_frequence = 1;
	_vector -> m_nitems += 1;
	
	
	return ERR_OK;
}


size_t CounterWords(Vector* _vector)
{
	return _vector -> m_nitems;
}

char* getWord(Vector* _vector, int _index)
{
	return _vector -> m_maps[_index] -> m_word;
}

int getFrequence(Vector* _vector, int _index)
{
	return _vector -> m_maps[_index] -> m_frequence;
}


void increment(Vector* _vector, int _index)
{
	_vector -> m_maps[_index] -> m_frequence += 1;
}
		
