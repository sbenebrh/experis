#ifndef __PRODUCERS_H__
#define __PRODUCERS_H__
/** 
 * @brief Create a framework for producers using generique waiting queue 
 * that stores pointer to user provided elements of generic type
 *
 * 
 * @author samuel ben ibgui(benebrhi@gmail.com)
 */
#include <stdio.h> /*size_t*/

#include "wQueue.h"/*_wqueue*/

typedef struct Producers Producers;

Producers* create_producers(size_t numbers, WQueue* _wqueue);

void* run_producer(void* arg);

void join_producers(Producers* _producers);

void Destroy_producers(Producers** _producers);
#endif
