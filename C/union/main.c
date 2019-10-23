#include<stdio.h>
#define SIZE 3

enum status {ERR_ARRAY_SIZE = -2,ERR, OK};

union age{
	int intAge;
	float floatAge;

};
typedef struct 
{
	int id;
	union age _age;
	int edu;
	
}student;

enum status print(student * _arrayPersonn, int _size)
{	
	int i;
	if(!_arrayPersonn) return ERR;

	if(_size < 0){
		return ERR_ARRAY_SIZE;
	}
	printf("%s\t%s\t%s\t%s\n", "personn","id","age","edu");
	printf("%s\n","------------------------------" );
	for(i = 0; i < _size;i++)
	{
		if(!(_arrayPersonn[i].id % 2 ))
		{
			printf("%d\t%d\t%d\t%d\n", i + 1, _arrayPersonn[i].id,_arrayPersonn[i]._age.intAge,_arrayPersonn[i].edu);
		}
		else
			printf("%d\t%d\t%.2f\t%d\n", i + 1, _arrayPersonn[i].id,_arrayPersonn[i]._age.floatAge,_arrayPersonn[i].edu);
	}
	return OK;
}

int main()
{
	int i;
	enum status sttus;
	student studentArray[SIZE];
	for(i = 0;i < SIZE; i++)
	{
		printf("enter id: \n");
		scanf("%d",&studentArray[i].id);
		printf("%s\n","enter age: " );
		if(!(studentArray[i].id % 2))
		{
			scanf("%d",&studentArray[i]._age.intAge);

		}
		else
			scanf("%f",&studentArray[i]._age.floatAge);
		printf("%s\n","enter edu: " );
		scanf("%d", &studentArray[i].edu);

	}
	sttus = print(studentArray, SIZE);
	if(!sttus) 
		printf("print well");
	else printf("%s\n","error" );

	return 0;


}