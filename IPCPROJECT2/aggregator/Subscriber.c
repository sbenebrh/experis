#include "Subscriber.h"

#include <stdlib.h> /*calloc*/

#include "cdr.h"
#include "zlog4c.h"



static void init_Subscriber(Subscriber* _subscriber,CDR* _cdr);

Subscriber* Subscriber_Create(CDR* _cdr)
{
	Subscriber* newSubscriber = NULL;
	newSubscriber = (Subscriber*)calloc(1,sizeof(Subscriber));
	if(NULL == newSubscriber)
	{
		return NULL;
	}
	init_Subscriber(newSubscriber, _cdr);
	return newSubscriber;
}

size_t getKey(Subscriber* _subcriber)
{
	return _subcriber -> m_IMSI;
}

void Subscriber_CreateBill(Subscriber* _subscriber,char* _filename)
{
	FILE* fp;

	/*append- open file for output at the end of a file*/
	fp=fopen(_filename, "a");
	if(!fp)
	{
		return;
	}

	fprintf(fp,"IMSI: %lu, ",_subscriber->m_IMSI);
	fprintf(fp,"Calls duration: %lu, ",_subscriber->m_data.m_voiceOut + _subscriber->m_data.m_voiceIn);
	fprintf(fp,"SMS sent: %lu, \n",_subscriber->m_data.m_nOfSmsIn + _subscriber ->m_data.m_nOfSmsout);

	fclose(fp);
}
Subscriber_Result Subscriber_SetData(Subscriber* _subcriber, CDR* _cdr)
{
	CallType type;
	size_t duration = 0;
	size_t upload, download;
	type = _cdr -> m_callType;

	switch(type)
	{
		case CDR_MOC:
			duration = _cdr -> m_duration;
			_subcriber -> m_data.m_voiceOut += duration;
			break;

		case CDR_MTC:
			duration = _cdr -> m_duration;
			_subcriber -> m_data.m_voiceIn += duration;
			break;

		case CDR_SMS_MO:
			_subcriber -> m_data.m_nOfSmsout += 1;
			break;

		case CDR_SMS_MT:
			_subcriber -> m_data.m_nOfSmsIn += 1;
			break;

		case CDR_GPRS:
			download = _cdr -> m_download;
			upload = _cdr -> m_upload;
			_subcriber -> m_data.m_dowloadData += download;
			_subcriber ->m_data.m_uploadData += upload;
			break;
	}
	return SUB_SUCCESS;
}

int Subscriber_Size()
{
	return sizeof(Subscriber);
}
/*********************************************************************/
static void init_Subscriber(Subscriber* _subscriber,CDR* _cdr)
{
	size_t key = 0;
	key = _cdr -> m_IMSI;
	_subscriber -> m_IMSI = key;

	key = _cdr -> m_MSISDN;
	_subscriber -> m_MSISDN = key;

	key = _cdr -> m_IMEI;
	_subscriber -> m_IMEI = key;

	Subscriber_SetData(_subscriber, _cdr);

}
