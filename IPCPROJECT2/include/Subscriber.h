#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__

#include "cdr.h"

struct dataCounter
{
	size_t 				m_nOfSmsIn;
	size_t 				m_nOfSmsout;
	size_t 				m_dowloadData;
	size_t 				m_uploadData;
	size_t 				m_voiceOut;
	size_t 				m_voiceIn;
};

struct  Subscriber
{
	size_t 				m_IMSI;
	size_t 			   	m_MSISDN;
	size_t 			   	m_IMEI; 
	struct dataCounter 	m_data;
};

typedef enum Subscriber_Result {
	SUB_SUCCESS = 0,	
	SUB_NULL_ERROR,	
	SUB_ALLOCATION_ERROR,				
	SUB_PARAMETER_NULL_ERROR		
}Subscriber_Result;

typedef struct Subscriber Subscriber;
/* IMEI imsi(key) MSISDN(phone number) SMS_MO SMS_MT DOWLOAND UPLAOAD MOC MTC DURATION UPGOING and Duration intcomming
*	*/
Subscriber* Subscriber_Create(CDR* _cdr);

void Subscriber_Destroy(Subscriber** _subcriber);

Subscriber_Result Subscriber_SetData(Subscriber* _subcriber, CDR* _cdr);

size_t getKey(Subscriber* _subcriber);

void Subscriber_CreateBill(Subscriber* _subscriber, char* filename);

int Subscriber_Size();

#endif
