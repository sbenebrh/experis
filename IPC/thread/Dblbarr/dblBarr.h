#ifndef __DBL_BARR_H__
#define  __DBL_BARR_H__
#define FAIL -1
#define SUCCEES 0

typedef struct dblBar dblBar;

dblBar* dblBarr_Create(size_t _count);

void dblBarr_Destroy(dblBar** _dblbarr);

void dblBarrWait(dlbBar* _db, void*(*_func)(void*), void* _arg);

#endif