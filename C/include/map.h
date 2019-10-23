#ifndef _MAP_H
#define _MAP_H

#include"ADTErr.h"

typedef struct Vector Vector;

Vector* createVector(size_t _size);
void DestroyVector( Vector* _vector);
ADTErr addWord(Vector* _vector, char _word[128]);
size_t CounterWords(Vector* _vector);
char* getWord(Vector* _vector, int _index);
int getFrequence(Vector* _vector, int _index);
void increment(Vector* _vector, int _index);


#endif
