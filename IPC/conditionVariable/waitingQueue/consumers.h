#ifndef __CONSUMERS_H__
#define __CONSUMERS_H__

#include <stdio.h> /*size_t*/

#include "wQueue.h"/*_wqueue*/

typedef struct Consumers Consumers;

Consumers* Create_Consumers(size_t _numbers, WQueue* _wqueue);

void* run_Consumer(void* _arg);

void join_Consumers(Consumers* _consumers, WQueue* _wqueue);

void kill_Consumers(Consumers* _consumers,WQueue* _wqueue);

void Destroy_Consumers(Consumers** _consumers);
#endif
