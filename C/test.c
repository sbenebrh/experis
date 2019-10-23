#include<stdio>
#include"list.h"
#include"ADTErr.h"
#include<string.h>
Person* CreatePerson(int _id,char _name[128],int _age)
{
	Person* newPerson = (Person*)malloc(sizeof(Person));
	newPerson -> m_id = _id;
	strcpy(_name[128], newPerson -> m_name[128] );
	newPerson -> m_age = _age;
	newPerson -> m_next = NULL;
}
	
TestResult testInsertHead1()
{
	Person* firstPerson = CreatePerson(12345,"samuel", 28);
	person* head = ListInsertHead(NULL,firstPerson);
	return !head ? 0: 1;
}

int main()
{
	testInsertHead1();
}
