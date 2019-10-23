#ifndef __MYSEMAPHORE_H__
#define __MYSEMAPHORE_H__

#define FAIL -1
typedef struct Mysemaphore Mysemaphore;

Mysemaphore* 	Semaphore_Create(size_t val);
void 		 	Semaphore_Destroy(Mysemaphore **_semaphore);
int 		 	Up(Mysemaphore* _semaphore);
int 			Down(Mysemaphore* _semaphore);

#endif



