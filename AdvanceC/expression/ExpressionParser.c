#include "ExpressionParser.h"

#include <stdlib.h> /*malloc*/
#include <string.h>	/*strcmp*/
#include <ctype.h>	/*isdigit*/
#include <stdio.h>	/*printf for debug*/

#include "HashMap.h"
#include "list.h"

#define FUNC_CAPACITY	32
#define VAR_CAPACITY	32
#define LPARENT			"("
#define RPARENT			")"
struct Ep
{
	HashMap* 		m_funcHash;
	HashMap* 		m_var;
};

typedef struct structFunc
{
	int 			m_IsBinaryF;
	char* 			m_name;
	union func 		m_func;

}structFunc;

typedef struct StructVar
{
	char* 			m_name;
	double 			m_value;
}StructVar;

/*#############################################*/
static size_t 					Hashfunc(const void* _key);
static int 						ComparFunc(const void* _firstKey, const void* _secondKey);
static structFunc* 				structFunc_create(union func _pf , int _flag, const char* _name);
static Expression_Result 		translator(Map_Result _result);
static StructVar* 				StructVar_create(double _value,const char* _name);
static List*					Parse(char* _expression);
static List* 					PostOrderExpression(List* _exp,HashMap* _funcHash);
static N* 						treeExpList(List* _postList,HashMap* _funcHash, HashMap* _varHash);
static double 					transformToDigit(const void* pItem);
static int 						IsVar(HashMap* _varHash,void* _item);
static double					getValue(HashMap* _varHash,void* _item);
static int 						IsBinary(HashMap* _funcHash, void* _item);
static int 						IsDigit(char* _token);
static int 						IsFunc(HashMap* _funcHash,void* _item);
static void						structsDestroy(void* _item);
static int						printKey(const void* _key, void* _value, void* _context);
/*#############################################*/
Ep* ExpressionParser_Create()
{
	Ep* newEp = NULL;
	newEp = (Ep*)malloc(sizeof(Ep));
	if(NULL == newEp)
	{
		return NULL;
	}
	newEp -> m_funcHash = HashMap_Create(FUNC_CAPACITY, Hashfunc, ComparFunc);
	if(NULL == newEp -> m_funcHash)
	{
		free(newEp);
		return NULL;
	}

	newEp -> m_var = HashMap_Create(VAR_CAPACITY, Hashfunc, ComparFunc);
	if(NULL == newEp -> m_funcHash)
	{
		HashMap_Destroy(&(newEp -> m_funcHash), NULL, NULL);
		free(newEp);
		return NULL;
	}
	return newEp;

}

void ExpressionParser_Destroy(Ep** _ep)
{
	if(!_ep || !*_ep)
	{
		return;
	}
	HashMap_Destroy(&((*_ep) -> m_funcHash), NULL, structsDestroy);
	HashMap_Destroy(&((*_ep) -> m_var),NULL,structsDestroy);
	free(*_ep);
	*_ep = NULL;
}

Expression_Result ExpressionParser_add_func(Ep* _ep,union func _pf , int _flag, const char* _name)
{
	structFunc* sFunc = NULL;
	
	if(NULL == _ep)
	{
		return EXPRESSION_PARSER_UNINITIALIZED_ERROR;
	}
	/*TODO when to destroy*/
	if(NULL == (sFunc = structFunc_create(_pf , _flag, _name)))
	{
		return EXPRESSION_PARSER_ALLOCATION_ERROR;
	}
	
	return translator(HashMap_Insert(_ep->m_funcHash, sFunc -> m_name, sFunc));

}




Expression_Result ExpressionParser_add_Var(Ep* _ep, double _value, const char* _name)
{
	StructVar* var = NULL;
	Expression_Result result;
	void* pkey = malloc(strlen(_name) * sizeof(char));
	void* pValue;

	if(NULL == _ep)
	{
		return EXPRESSION_PARSER_UNINITIALIZED_ERROR;
	}
	/*TODO when to destroy*/
	if(NULL == (var = StructVar_create(_value, _name)))
	{
		return EXPRESSION_PARSER_ALLOCATION_ERROR;
	}
	if(EXPRESSION_PARSER_KEY_DUPLICATE_ERROR == (result = translator(HashMap_Insert(_ep -> m_var, var -> m_name, var))))
	{
		translator(HashMap_Remove(_ep -> m_var, var -> m_name, &pkey, &pValue));
		free(pValue);
		result = translator(HashMap_Insert(_ep -> m_var, var -> m_name, var));	
	}
	return result;
}

N* ExpressionParser_parse(Ep* _ep, char* _expression)
{
	N* calculable = NULL;
	List* postList = NULL;
	List* exp  = NULL;
	if(NULL == _ep || NULL == _expression)
	{
		return NULL;
	}

	exp = Parse(_expression);

	postList = PostOrderExpression(exp, _ep -> m_funcHash);

	calculable = treeExpList(postList, _ep -> m_funcHash, _ep -> m_var);

	/*TODO function to destroy inside struct*/
	List_Destroy(&exp,NULL);
	List_Destroy(&postList,NULL);

	return calculable;
}

double ExpressionParser_calc(const Ep* _ep, const N * _treeExpression)
{
	enum NodeType type;
	type = getType(_treeExpression);
	switch(type)
	{
		case VALUE:
			return getValueN(_treeExpression);

		case BINARY_OP:
			return doubleBinFunc(_treeExpression, ExpressionParser_calc(_ep,getsonL(_treeExpression)), 
														ExpressionParser_calc(_ep,getsonR(_treeExpression)));

		case UNARY_OP:
			return doubleUnFunc(_treeExpression, ExpressionParser_calc(_ep,getsonL(_treeExpression)));
		default:
		/*TODO error*/
			return -1;
	}
}

void printKeyStruct(Ep *_ep, int _flag)
{
	/*funcHash*/
	if(_flag)
	{
		HashMap_ForEach(_ep -> m_funcHash, printKey, NULL);
	}
	else
	{
		HashMap_ForEach(_ep -> m_var, printKey, NULL);
	}
	
}
/*########################################################*/

static size_t Hashfunc(const void* _key)
{
	char* ptr = (char*) _key;
	return ptr[0];
}

static int ComparFunc(const void* _firstKey, const void* _secondKey)
{
	return ! strcmp((char*)(_firstKey) , (char*)(_secondKey));
}

static structFunc* structFunc_create(union func _pf , int _flag, const char* _name)
{
	structFunc* sFunc = NULL;
	int lenght = 0;
	sFunc = (structFunc*)malloc(sizeof(structFunc));
	if(NULL == sFunc)
	{
		return NULL;
	}

	if(_flag == BINARYOP)
	{
		sFunc -> m_IsBinaryF = BINARYOP;
		sFunc -> m_func.m_bin = _pf.m_bin;
	}
	else
	{
		sFunc -> m_IsBinaryF = UNARYOP;
		sFunc -> m_func.m_uni = _pf.m_uni;
	}

	lenght = strlen(_name);
	sFunc -> m_name = (char*)malloc(lenght * sizeof(char));
	if(NULL == sFunc -> m_name)
	{
		free(sFunc);
		return NULL;
	}
	strcpy(sFunc -> m_name, _name);

	return sFunc;
}

static Expression_Result translator(Map_Result _result)
{
	Expression_Result result;
	switch(_result)
	{
		case MAP_SUCCESS:
			result = EXPRESSION_PARSER_SUCCEES;
			break;

		case MAP_UNINITIALIZED_ERROR:
			result = EXPRESSION_PARSER_UNINITIALIZED_ERROR;
			break;

		case MAP_KEY_NULL_ERROR:
			result = EXPRESSION_PARSER_KEY_NULL_ERROR;
			break;

		case MAP_KEY_DUPLICATE_ERROR:
			result = EXPRESSION_PARSER_KEY_DUPLICATE_ERROR;
			break;

		case MAP_KEY_NOT_FOUND_ERROR:
			result = EXPRESSION_PARSER_KEY_NOT_FOUND_ERROR;
			break;

		case MAP_ALLOCATION_ERROR:
			result = EXPRESSION_PARSER_ALLOCATION_ERROR;
			break;

		case MAP_EMPTY_ERROR:
			result = EXPRESSION_PARSER_EMPTY_ERROR;
			break;
		default:
			result = EXPRESSION_PARSER_DEFAULT;
			break;
	}
	return result;
}

static StructVar* StructVar_create(double _value, const char* _name)
{
	StructVar* var = NULL;
	int lenght = 0;
	var = (StructVar*)malloc(sizeof(StructVar));
	if(NULL == var)
	{
		return NULL;
	}

	lenght = strlen(_name);
	var -> m_name = (char*)malloc(lenght * sizeof(char));
	if(NULL == var -> m_name)
	{
		free(var);
		return NULL;
	}

	strcpy(var -> m_name, _name);
	var -> m_value = _value;

	return var;
}

static List* Parse(char* _expression)
{
	List* parseList = NULL;
	char* delim = " ";
	char *token;

	parseList = List_Create();
	if(NULL == parseList)
	{
		return NULL;
	}

	token = strtok(_expression, delim);
	ListItr_InsertBefore(ListItr_End(parseList), token);
	while(1)
	{
		token = strtok(NULL, delim);
		if(NULL == token)
		{
			break;
		}
		ListItr_InsertBefore(ListItr_End(parseList), token);
	}

	return parseList;
}

static List* PostOrderExpression(List* _exp, HashMap* _func)
{
	void* pItem;
	List* operator ;
	List* orderList = List_Create();
	int size,sizeOp;
	if(NULL == orderList)
	{
		return NULL;
	}

	operator = List_Create();
	if(NULL == operator)
	{
		return NULL;
	}

	size = List_Size(_exp);
	while(size)
	{

		pItem = ListItr_Remove(ListItr_Begin(_exp));
		if(IsDigit((char*)pItem))
		{
			ListItr_InsertBefore(ListItr_End(orderList), pItem);
		}
		else if(IsFunc(_func, pItem))
		{
			ListItr_InsertBefore(ListItr_Begin(operator), pItem);
		}
		else if(strcmp((char*)pItem, LPARENT) == 0)
		{
			ListItr_InsertBefore(ListItr_Begin(operator), pItem);
		}
		else if(strcmp((char*)pItem, RPARENT) == 0)
		{
			while(1)
			{	
				pItem = ListItr_Remove(ListItr_Begin(_exp));
				if(strcmp((char*)pItem, LPARENT) == 0)
				{
					break;
				}
				ListItr_InsertBefore(ListItr_End(orderList), pItem);
			}
		}
		/*variable*/
		else
		{
			ListItr_InsertBefore(ListItr_End(orderList), pItem);
		}
		size--;	
	}
	/*to empty the operatorList*/
	sizeOp = List_Size(operator);
	while(sizeOp)
		{
			pItem = ListItr_Remove(ListItr_Begin(operator));
			ListItr_InsertBefore(ListItr_End(orderList), pItem);	
			sizeOp--;		
		}
	List_Destroy(&operator, NULL);
	return orderList;
}

static N* treeExpList(List* _postList, HashMap* _func, HashMap* _var)
{
	List* treeList = NULL;
	void* pItem;
	int size = 0;
	void* pItem1,*pItem2;
	double value;
	void* pValue;

	treeList = List_Create();
	if(NULL == treeList)
	{
		return NULL;
	}

	size = List_Size(_postList);
	while(size)
	{
		pItem = ListItr_Remove(ListItr_Begin(_postList));
		if(IsDigit((char*)pItem))
		{
			value = transformToDigit(pItem);
			ListItr_InsertBefore(ListItr_End(treeList), num(value));
		}
		else if(IsVar(_var, pItem))
		{
			value = getValue(_var,pItem);
			ListItr_InsertBefore(ListItr_End(treeList), num(value));
		}
		else if(IsFunc(_func,pItem))
		{
			if(IsBinary(_func, pItem))
			{
				pItem1 = ListItr_Remove(ListItr_Prev(ListItr_End(treeList)));
				pItem2 = ListItr_Remove(ListItr_Prev(ListItr_End(treeList)));
				/*List_PopTail(treeList, &pItem1);
				List_PopTail(treeList, &pItem2);*/

				HashMap_Find(_func, pItem, &pValue);
				ListItr_InsertBefore(ListItr_End(treeList), 
									binOp(pItem2,pItem1,((structFunc*) pValue) -> m_func.m_bin));
				
			}
			else if(!IsBinary(_func, pItem))
			{
				HashMap_Find(_func, pItem, &pValue);
				List_PopTail(treeList, &pItem1);
				ListItr_InsertBefore(ListItr_End(treeList), 
									unOp(pItem1,((structFunc*) pValue )-> m_func.m_uni));
			}
		}
		size--;
		
	}
	pItem = ListItr_Remove(ListItr_Begin(treeList));
	/*TODO Destroy inside func*/
	/*List_Destroy(&treeList, NULL);*/
	return (N*)pItem;
}

static double transformToDigit(const void* _pItem)
{
	return atof((char*)_pItem);
}

static int IsVar(HashMap* _var,void* _item)
{
	if(HashMap_Find(_var, (char*) _item,NULL) == MAP_SUCCESS)
	{
		return 1;
	}
	return 0;
}

static double getValue(HashMap* _var,void* _item)
{
	void* pValue = NULL;
	HashMap_Find(_var, _item,&pValue);
	return ((StructVar*)pValue) -> m_value;
}

static int 	IsBinary(HashMap* _funcHash, void* _item)
{
	void* pValue = NULL;
	int isBinaryFlag = 0;
	HashMap_Find(_funcHash, _item,&pValue);
	isBinaryFlag = ((structFunc*) pValue) -> m_IsBinaryF;

	return isBinaryFlag;
}

static int 	IsDigit(char* _token)
{
	return isdigit(*_token);
}

static int IsFunc(HashMap* _funcHash,void* _item)
{
	if(HashMap_Find(_funcHash, (char*) _item, NULL) == MAP_SUCCESS)
	{
		return 1;
	}
	return 0;
}

static void	structsDestroy(void* _item)
{
	free(_item);
}

static int	printKey(const void* _key, void* _value, void* _context)
{
	printf("%s\n",(char*)_key);
	return 1;
}