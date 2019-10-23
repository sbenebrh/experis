#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"
#include"ADTErr.h"

Person* CreatePerson(int _id, char _name[128], int _age)
{
	Person* NewPerson = (Person*) malloc(sizeof(Person));
	NewPerson -> m_id = _id;
	strcpy(NewPerson -> m_name, _name);
	NewPerson -> m_age = _age;
	return NewPerson;
}
TestResult TestInsertHead()
{
	Person* head = (Person*) malloc(sizeof(Person));
	Person* pers1 = CreatePerson(1234,"samuel", 28);
	Person* pers2 = CreatePerson(1235,"sam", 20);

	head = ListInsertHead(head, pers1);
	head = ListInsertHead(head, pers2);
	PrintList(head);
	free(pers2);
	free(pers1);
	free(head);
	return head ? SUCCEED: FAIL;
}
TestResult TestListInsertByKey()
{
	Person* head = (Person*) calloc(1, sizeof(Person));
	Person* pers1 = CreatePerson(1234,"samuel", 28);
	Person* pers2 = CreatePerson(1235,"sam", 20);
	Person* pers3 = CreatePerson(1236,"sam", 21);

	head = ListInsertByKey(head, 1236,pers3);
	head = ListInsertByKey(head, 1234,pers1);
	head = ListInsertByKey(head, 1235,pers2);
	PrintList(head);
	free(pers2);
	free(pers1);
	free(pers3);
	free(head);
	return head ? SUCCEED: FAIL;
}
TestResult TestListInsertByKeyRec()
{
	Person* head = (Person*) calloc(1, sizeof(Person));
	Person* pers1 = CreatePerson(1234,"samuel", 28);
	Person* pers2 = CreatePerson(1235,"sam", 20);
	Person* pers3 = CreatePerson(1236,"sam", 21);

	head = ListInsertByKeyRec(head, 1236,pers3);
	head = ListInsertByKeyRec(head, 1234,pers1);
	head = ListInsertByKeyRec(head, 1235,pers2);
	PrintList(head);
	free(pers2);
	free(pers1);
	free(pers3);
	free(head);
	return head ? SUCCEED: FAIL;
}
TestResult TestListRemoveHead()
{
	Person* head = (Person*) calloc(1, sizeof(Person));
	Person* pers1 = CreatePerson(1234,"samuel", 28);
	Person* pers2 = CreatePerson(1235,"sam", 20);
	Person* pers3 = CreatePerson(1236,"sam", 21);

	head = ListInsertByKey(head, 1236,pers3);
	head = ListInsertByKey(head, 1234,pers1);
	head = ListInsertByKey(head, 1235,pers2);
	head = ListRemoveHead(head, &pers3);
	PrintList(head);
	head = ListRemoveHead(head, &pers2);
	PrintList(head);
	free(pers2);
	free(pers1);
	free(pers3);
	free(head);
	return head ? SUCCEED: FAIL;
}
TestResult TestListRemoveByKey()
{
	Person* head = (Person*) calloc(1, sizeof(Person));
	Person* pers1 = CreatePerson(1234,"samuel", 28);
	Person* pers2 = CreatePerson(1235,"sam", 20);
	Person* pers3 = CreatePerson(1236,"sam", 21);

	head = ListInsertByKey(head, 1236,pers3);
	head = ListInsertByKey(head, 1234,pers1);
	head = ListInsertByKey(head, 1235,pers2);
	head = ListRemoveByKey(head, 1236,&pers3);
	PrintList(head);
	head = ListRemoveByKey(head, 1235,&pers2);
	PrintList(head);
	free(pers2);
	free(pers1);
	free(pers3);
	free(head);
	return head ? SUCCEED: FAIL;
}
TestResult TestListRemoveByKeyRec()
{
	Person* head = (Person*) calloc(1, sizeof(Person));
	Person* pers1 = CreatePerson(1234,"samuel", 28);
	Person* pers2 = CreatePerson(1235,"sam", 20);
	Person* pers3 = CreatePerson(1236,"sam", 21);

	head = ListInsertByKey(head, 1236,pers3);
	head = ListInsertByKey(head, 1234,pers1);
	head = ListInsertByKey(head, 1235,pers2);
	head = ListRemoveByKeyRec(head, 1236,&pers3);
	PrintList(head);
	head = ListRemoveByKeyRec(head, 1235,&pers2);
	PrintList(head);
	free(pers2);
	free(pers1);
	free(pers3);
	free(head);
	return head ? SUCCEED: FAIL;
}
int main()
{
	printf("\n%s\t%s\n","TestInsertHead",(TestInsertHead() == SUCCEED)? "succeed": "failed" );
	printf("\n%s\t%s\n","TestListInsertByKey",(TestListInsertByKey() == SUCCEED)? "succeed": "failed" );
	printf("\n%s\t%s\n","TestListInsertByKeyRec",(TestListInsertByKeyRec() == SUCCEED)? "succeed": "failed" );
	printf("\n%s\t%s\n","TestListRemoveHead",(TestListRemoveHead() == SUCCEED)? "succeed": "failed" );
	printf("\n%s\t%s\n","TestListRemoveByKey",(TestListRemoveByKey() == SUCCEED)? "succeed": "failed" );
	printf("\n%s\t%s\n","TestListRemoveByKeyRec",(TestListRemoveByKeyRec() == SUCCEED)? "succeed": "failed" );

	return 0;
}
