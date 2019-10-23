#include<stdio.h>
#include <stdlib.h>
#include "test.h"
#include "vector.h"
#define  SIZE		32
typedef struct  
{
	size_t m_ID;

}Person;

int f(void* a, size_t b, void* c)
	{
		return 1;
	}
void dest(void* _item)
{
	free(_item);
}

TestResult TestVecCreate1(Vector_Result* _status)
{
	Vector* test = Vector_Create(SIZE,SIZE);

	if(NULL == test)
	{
		return FAIL;
	}
	Vector_Destroy(&test, NULL);
	return SUCCEED;
}

TestResult TestVecCreate2(Vector_Result* _status)
{
	Vector* test = Vector_Create(0,0);

	if(NULL == test)
	{
		return SUCCEED;
	}
	Vector_Destroy(&test, NULL);
	return FAIL;
}

TestResult TestVecCreate3(Vector_Result* _status)
{
	Vector* test = Vector_Create(0,SIZE);

	if(NULL == test)
	{
		return FAIL;
	}
	Vector_Destroy(&test, NULL);
	return SUCCEED;
}

TestResult TestVecCreate4(Vector_Result* _status)
{
	Vector* test = Vector_Create(SIZE,0);

	if(NULL == test)
	{
		return FAIL;
	}
	Vector_Destroy(&test, NULL);
	return SUCCEED;
}

TestResult TestVecDestroy1(Vector_Result* _status)
{
	Vector* test = Vector_Create(SIZE,SIZE);

	Vector_Destroy(&test, NULL);
	if(NULL == test)
	{
		return SUCCEED;
	}
	return FAIL;
}

TestResult TestVecDestroy2(Vector_Result* _status)
{
	Vector* test = Vector_Create(SIZE,SIZE);

	Vector_Destroy(&test, NULL);
	Vector_Destroy(&test, NULL);
	if(NULL == test)
	{
		return SUCCEED;
	}
	return FAIL;
}


TestResult TestVecAppend1(Vector_Result* _status)
{
	int a = 10;
	Vector* test = Vector_Create(SIZE,SIZE);

	if(VECTOR_SUCCESS!=Vector_Append(test,&a))
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	Vector_Destroy(&test, NULL);
	return SUCCEED;
	
}


TestResult TestVecAppend2(Vector_Result* _status)
{
	int a = 10;

	Vector* test = Vector_Create(SIZE,SIZE);

	if(VECTOR_SUCCESS!=Vector_Append(test,&a))
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}


	if(Vector_ForEach(test,f,NULL) == 1)
	{	
		Vector_Destroy(&test, NULL);
		return SUCCEED;
	}
	return FAIL;
	
}

TestResult TestVecAppend3(Vector_Result* _status)
{
	int a = 10, b = 21;

	Vector* test = Vector_Create(SIZE,SIZE);

	if(VECTOR_SUCCESS!=Vector_Append(test,&a))
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	if(VECTOR_SUCCESS!=Vector_Append(test,&b))
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	if(Vector_ForEach(test,f,NULL) == 2)
	{	
		Vector_Destroy(&test, NULL);
		return SUCCEED;
	}
	return FAIL;
	
}

TestResult TestVecAppend4(Vector_Result* _status)
{
	int a = 10, b = 21;

	Vector* test1 = Vector_Create(SIZE,SIZE);
	Vector* test2 = Vector_Create(SIZE,SIZE);

	if(VECTOR_SUCCESS!=Vector_Append(test1,&a))
	{
		Vector_Destroy(&test1,NULL);
		Vector_Destroy(&test2,NULL);
		return FAIL;
	}

	if(VECTOR_SUCCESS!=Vector_Append(test2,&b))
	{
		Vector_Destroy(&test1,NULL);
		Vector_Destroy(&test2,NULL);
		return FAIL;
	}

	if(Vector_ForEach(test1,f,NULL) == 1  &&  Vector_ForEach(test2,f,NULL) == 1)
	{	
		Vector_Destroy(&test1,NULL);
		Vector_Destroy(&test2,NULL);
		return SUCCEED;
	}
	return FAIL;
	
}

TestResult TestVecAppend5(Vector_Result* _status)
{
	int a = 10;
	Vector* test = Vector_Create(0,1);

	if(VECTOR_SUCCESS!=Vector_Append(test,&a))
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	Vector_Destroy(&test, NULL);
	return SUCCEED;
}

TestResult TestVecRemove1(Vector_Result* _status)
{
	int* a;
	Vector* test = Vector_Create(SIZE,SIZE);

	*_status = Vector_Remove(test,(void*)&a);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return SUCCEED;
	}
	printf("%d\n",*a );
	Vector_Destroy(&test, NULL);
	return FAIL;
	
}

TestResult TestVecRemove2(Vector_Result* _status)
{
	int* a;
	int b = 10;
	Vector* test = Vector_Create(SIZE,SIZE);

	*_status = Vector_Append(test, &b);
	if(VECTOR_SUCCESS != *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	*_status = Vector_Remove(test,(void*)&a);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}
	if(*a != 10)
		{
			Vector_Destroy(&test, NULL);
			return FAIL;
		}

		Vector_Destroy(&test, NULL);
		return SUCCEED;
	
}
/*test resize */
TestResult TestVecRemove3(Vector_Result* _status)
{
	int* a;
	int b = 10;
	int c = 12;
	int d = 14;

	Vector* test = Vector_Create(0,1);

	*_status = Vector_Append(test, &b);
	if(VECTOR_SUCCESS != *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	*_status = Vector_Append(test, &c);
	if(VECTOR_SUCCESS != *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	*_status = Vector_Append(test, &d);
	if(VECTOR_SUCCESS != *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	*_status = Vector_Remove(test,(void*)&a);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}
	*_status = Vector_Remove(test,(void*)&a);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	if(*a != 12)
		{
			Vector_Destroy(&test, NULL);
			return FAIL;
		}

		Vector_Destroy(&test, NULL);
		return SUCCEED;
	
}

/*test out of bound*/
TestResult TestVecGet1(Vector_Result* _status)
{
	int* a;
	Vector* test = Vector_Create(SIZE,SIZE);

	*_status = Vector_Get(test,0,(void*)&a);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return SUCCEED;
	}
	Vector_Destroy(&test, NULL);
	return FAIL;
	
}

TestResult TestVecGet2(Vector_Result* _status)
{
	int a = 10;
	int* b;
	Vector* test = Vector_Create(SIZE,SIZE);

	*_status = Vector_Append(test,&a);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	*_status = Vector_Get(test,0,(void*)&b);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	if(*b != 10)
	{
		Vector_Destroy(&test, NULL);
		return FAIL;
	}

	Vector_Destroy(&test, NULL);
	return SUCCEED;

}

/*test out of bound*/
TestResult TestVecSet1(Vector_Result* _status)
{
	int a = 10;
	Vector* test = Vector_Create(SIZE,SIZE);

	*_status = Vector_Set(test,0,&a);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return SUCCEED;
	}
	Vector_Destroy(&test, NULL);
	return FAIL;
	
}

TestResult TestVecSet2(Vector_Result* _status)
{
	int a = 10;
	int b = 20;
	int* c;
	Vector* test = Vector_Create(SIZE,SIZE);

	*_status = Vector_Append(test,&a);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return SUCCEED;
	}

	*_status = Vector_Set(test,0,&b);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	*_status = Vector_Get(test,0,(void*)&c);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}
	if(*c != 20)
	{
		Vector_Destroy(&test, NULL);
		return FAIL;
	}

	Vector_Destroy(&test, NULL);
	return SUCCEED;

}




/*#############TEST FOR STRUCT#############*/

TestResult TestVecAppend11(Vector_Result* _status)
{
	Vector* test = Vector_Create(SIZE,SIZE);
	Person p ={1234} ;
	if(VECTOR_SUCCESS!=Vector_Append(test,&p))
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	Vector_Destroy(&test, NULL);
	return SUCCEED;
}
TestResult TestVecAppend12(Vector_Result* _status)
{
	Person p ={1234} ;

	Vector* test = Vector_Create(SIZE,SIZE);

	if(VECTOR_SUCCESS!=Vector_Append(test,&p))
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}


	if(Vector_ForEach(test,f,NULL) == 1)
	{	
		Vector_Destroy(&test, NULL);
		return SUCCEED;
	}
	Vector_Destroy(&test, NULL);
	return FAIL;
	
}

TestResult TestVecAppend13(Vector_Result* _status)
{
	Person p ={1234} , b = {21};

	Vector* test = Vector_Create(SIZE,SIZE);

	if(VECTOR_SUCCESS!=Vector_Append(test,&p))
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	if(VECTOR_SUCCESS!=Vector_Append(test,&b))
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	if(Vector_ForEach(test,f,NULL) == 2)
	{	
		Vector_Destroy(&test, NULL);
		return SUCCEED;
	}
	Vector_Destroy(&test,NULL);
	return FAIL;
	
}

TestResult TestVeDestroy11(Vector_Result* _status)
{
	Vector* test = Vector_Create(SIZE,SIZE);
	Person* p =malloc(10 * sizeof(Person)) ;
	if(VECTOR_SUCCESS!=Vector_Append(test,p))
	{
		Vector_Destroy(&test,dest);
		return FAIL;
	}

	Vector_Destroy(&test, dest);
	return SUCCEED;
}

TestResult TestVecAppend14(Vector_Result* _status)
{
	Person p ={1234}, b = {21};

	Vector* test1 = Vector_Create(SIZE,SIZE);
	Vector* test2 = Vector_Create(SIZE,SIZE);

	if(VECTOR_SUCCESS!=Vector_Append(test1,&p))
	{
		Vector_Destroy(&test1,NULL);
		Vector_Destroy(&test2,NULL);
		return FAIL;
	}

	if(VECTOR_SUCCESS!=Vector_Append(test2,&b))
	{
		Vector_Destroy(&test1,NULL);
		Vector_Destroy(&test2,NULL);
		return FAIL;
	}

	if(Vector_ForEach(test1,f,NULL) == 1  &&  Vector_ForEach(test2,f,NULL) == 1)
	{	
		Vector_Destroy(&test1,NULL);
		Vector_Destroy(&test2,NULL);
		return SUCCEED;
	}
	return FAIL;
	
}

TestResult TestVecRemove12(Vector_Result* _status)
{
	Person* a;
	Person b = {10};
	Vector* test = Vector_Create(SIZE,SIZE);

	*_status = Vector_Append(test, &b);
	if(VECTOR_SUCCESS != *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	*_status = Vector_Remove(test,(void*)&a);
	if(VECTOR_SUCCESS!= *_status)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}
	if(a -> m_ID != 10)
		{
			Vector_Destroy(&test, NULL);
			return FAIL;
		}

		Vector_Destroy(&test, NULL);
		return SUCCEED;
	
}
