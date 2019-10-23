#ifndef __CDR_H__
#define __CDR_H__

#include <stddef.h>
#define OP_NAME_BUFF 64

typedef enum CallType
{
	CDR_MOC, 									/* outgoing voice call  				*/
	CDR_MTC,									/* incoming voice call 					*/
	CDR_SMS_MO, 								/* outgoing message 					*/
	CDR_SMS_MT,									/* incomming message 					*/
	CDR_GPRS
}CallType;

typedef struct CDR
{
	size_t 		m_IMSI; 						/* the id of each subscriber(unique) 	*/
	size_t 		m_MSISDN; 						/* phone number 						*/
	size_t 		m_IMEI; 						/* IMEI number of the mobile phone 		*/
	char 		m_OpName[OP_NAME_BUFF]; 		/* opeartor brand name maximum 64 bytes */
	CallType 	m_callType; 					/* type of call ref to the enum calltype*/
	size_t 		m_duration; 					/* call duration(internet or sms :0s) 	*/
	size_t		m_download;						/* download data from internet      	*/	
	size_t      m_upload; 						/* upload data from internet      		*/
	size_t		m_partyMSISDN;              	/* other side phone number(empty inter) */
	char		m_partyOperator[OP_NAME_BUFF]; 	/* opearator name of the other side     */ 
}CDR;                                                                                                                                                                                                                                                                                                      

#endif /*__CDR_H__*/
