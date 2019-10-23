#ifndef __HASH_H__
#define __HASH_H__

#include"ADTErr.h"

#define FALSE 0
#define TRUE 1

typedef struct Hash Hash;

Hash* HashCreate(const size_t _size);
void HashDestroy(Hash* _hash);

ADTErr HashInsert(Hash* _hash, int _data);
ADTErr HashRemove(Hash* _hash, int _data);

int HashIsFound(const Hash* _hash, int _data);

size_t HashCapacity(const Hash* _hash);
size_t HashNumOfItems(const Hash* _hash);
double HashAverageRehashes(const Hash* _hash);
size_t HashMaxReHash(const Hash* _hash);

void HashPrint(const Hash* _hash);

#endif