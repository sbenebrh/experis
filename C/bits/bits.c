#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"bits.h"
#define BYTE_SIZE 8
struct bitMap
{
	size_t m_nOfFeatures;
	char* m_features;
};


void	BitMapPrint(bitMap* _bitMap, char* *_arr)
{
	int i;

	if(NULL == _bitMap){ return;}

	if(_arr == NULL) {return ;}
	if (_bitMap->m_nOfFeatures == 0)
	{
		return;
	}

	for (i = 0; i < _bitMap->m_nOfFeatures; ++i)
	{
		if (bitOnOf(_bitMap,i + 1) == 1)
		{
			*_arr[i] == '1';
			printf("%c",'1' );
		}
		else if (bitOnOf(_bitMap,i + 1) == 0)
		{
			*_arr[i] == '0';
			printf("%c",'0' );
		}
	}
	_arr[i + 1] = '\0';

}
static unsigned char PowerTwo(int n)
{
	int i;
	unsigned char result = 1;

	if(n < 0 || n > 7){return 0;}

	for (i = 1; i < 8 - n ; ++i)
	{
		result = result << 1;
	}

	return result;
}

bitMap* createBM(size_t _nOfFeatures)
{
	bitMap* newBitMap = NULL;

	if(0 ==_nOfFeatures)
	{
		return newBitMap;
	}

	newBitMap = (bitMap*) malloc(sizeof(bitMap));
	if(NULL == newBitMap)
	{
		return newBitMap;
	}

	newBitMap -> m_features = (char*) calloc(_nOfFeatures/8 + 1, sizeof(char));
	if(NULL == newBitMap -> m_features)
	{
		free(newBitMap);
		return NULL;
	}
	newBitMap -> m_nOfFeatures = _nOfFeatures;

	return newBitMap;
}

void destroyBM(bitMap* _bm)
{
	if(NULL != _bm)
	{
		if(NULL != _bm -> m_features)
		{free(_bm -> m_features);}
		free(_bm);
	}
}


int bitOn(bitMap * _bm, size_t _bitNum)
{
	int blockBit;
	int PosInBlock;
	char * temp;
	if(NULL == _bm || _bm -> m_nOfFeatures < _bitNum)/* return -1 in case of error(i have a null pointer or the position of the features is greater than the number of features)*/
	{
		return -1;
	}
	_bitNum -= 1;
	blockBit = _bitNum / BYTE_SIZE;
	PosInBlock = _bitNum % BYTE_SIZE;
	
	_bm -> m_features[blockBit] |= PowerTwo(PosInBlock);
	return 0;
}


int bitOf(bitMap * _bm, size_t _bitNum)
{
	int blockBit;
	int PosInBlock;
	char number;

	if(NULL == _bm || _bm -> m_nOfFeatures < _bitNum)/* return -1 in case of error(i have a null pointer or the position of the features is greater than the number of features)*/
	{
		return -1;
	}
	if(bitOnOf(_bm, _bitNum) == 0)
	{
		return 0;
	}
	_bitNum -= 1;
	blockBit = _bitNum / BYTE_SIZE;
	PosInBlock = _bitNum % BYTE_SIZE;
	_bm -> m_features[blockBit] = _bm -> m_features[blockBit] ^ PowerTwo(PosInBlock);

	return 0;
}

int bitOnOf(bitMap * _bm, size_t _bitNum)
{
	int blockBit;
	int PosInBlock;
	char check;

	if(NULL == _bm || _bm -> m_nOfFeatures < _bitNum)/* return -1 in case of error(i have a null pointer or the position of the features is greater than the number of features)*/
	{
		return -1;
	}
	_bitNum -= 1;
	blockBit = _bitNum / BYTE_SIZE;
	PosInBlock = _bitNum % BYTE_SIZE;

	check = _bm -> m_features[blockBit] & PowerTwo(PosInBlock);
	if(check == PowerTwo(PosInBlock))
	{
		return 1;
	}
	return 0;

}

