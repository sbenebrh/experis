#ifndef __WQUEUE_H__
#define __WQUEUE_H__
/** 
 * @brief Create a Generic waiting Queue data type of a given size
 * that stores pointer to user provided elements of generic type
 * The Waiting Queue is heap allocated and wraps around
 * 
 * @author samuel ben ibgui(benebrhi@gmail.com)
 */ 

#include <stddef.h>  /* size_t */

#define FALSE 0

typedef struct WQueue WQueue;
typedef int	(*QueueElementAction)(void* _element, size_t _index, void* _context);



/**  
 * @brief Dynamically create a new waiting queue object of given capacity and  
 * @param[in] _maxSize - maximal number of elements that can be stored in the queue
  * @return Queue * - on success / NULL on fail 
 *
 * @warning if _maxSize is zero function will return NULL.
 */
WQueue* WQueue_Create(size_t _maxSize);

/**  
 * @brief Dynamically deallocate a previously allocated vector  
 * @param[in] _wqueue - _wqueue to be deallocated.
 * @params[in] _elementDestroy : A function pointer to be used to destroy all
 * 					 remaining elements in the queue or a null if no such destroy is required
 * @return void
 */
void WQueue_Destroy(WQueue** _wqueue, void (*_elementDestroy)(void* _item));

/**  
 * @brief Enqueue an Item to the tail of the Queue.  
 * @param[in] _queue - Queue to operate on.
 * @param[in] _item - Item to enqueue.
 *
 */
void WQueue_Enqueue(WQueue* _wqueue, void* _item);

/**  
 * @brief Dequeue (Remove and obtain) item at head of queue or return an error if queue is empty.  
 * @param[in] _wqueue - waiting Queue to operate on.
 * @param[out] _pValue - pointer to variable that will receive dequeued item
 
 */
void WQueue_Dequeue(WQueue* _wqueue, void** _pValue);

/**  
 * @brief Return true if the queue is empty.
 * @param[in] _queue - Queue to check.
 * @return  1 if empty 0 otherwise
 */
int Queue_IsEmpty(const WQueue* _wqueue);


#endif /*__WQUEUE_H__*/
