#ifndef _BITS_H
#define _BITS_H

typedef struct bitMap bitMap;

bitMap* createBM(size_t _nOfFeatures);
void destroyBMs(bitMap* _bm);

int bitOn(bitMap * bm, size_t _bitNum);
int bitOf(bitMap * bm, size_t _bitNum);
int bitOnOf(bitMap * bm, size_t _bitNum);





#endif