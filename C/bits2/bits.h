#ifndef BITS_H
#define BITS_H
#define SIZE_BYTE  8
#define SIZE_INT 32

void IntToBin(unsigned int _a, char* _result);
void CharToBin(unsigned char _a, unsigned char* _result);
unsigned char SetBits_1(unsigned char _X,unsigned int _N,unsigned int _P,unsigned char _Y );
unsigned int SetBits_2(unsigned char _W, unsigned char i,unsigned char j, unsigned char value);
unsigned char complement(unsigned char _source);
unsigned char rotate(unsigned char _n, unsigned char _x);

#endif
