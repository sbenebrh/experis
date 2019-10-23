#ifndef __EXPRESSION_PARSER_H__
#define __EXPRESSION_PARSER_H__
/*TODO comment*/
#include "expTree.h"/* N */

#define BINARYOP		1
#define UNARYOP			0
typedef enum 
{
	EXPRESSION_PARSER_SUCCEES,
	EXPRESSION_PARSER_UNINITIALIZED_ERROR,
	EXPRESSION_PARSER_KEY_NULL_ERROR,
	EXPRESSION_PARSER_KEY_DUPLICATE_ERROR,
	EXPRESSION_PARSER_KEY_NOT_FOUND_ERROR,
	EXPRESSION_PARSER_ALLOCATION_ERROR,
	EXPRESSION_PARSER_EMPTY_ERROR,
	EXPRESSION_PARSER_DEFAULT
}Expression_Result;

typedef struct Ep Ep;

union func
{
	double 		(*m_uni)(double);
	double		(*m_bin)(double,double);
};

Ep* ExpressionParser_Create();

Expression_Result ExpressionParser_add_func(Ep* _ep,union func _pf , int flag, const char* name);
Expression_Result ExpressionParser_add_Var(Ep* _ep, double _value, const char* name);

N* ExpressionParser_parse(Ep* _ep, char* _expression);
double ExpressionParser_calc(const Ep* _ep, const N* _treeExpression);


void ExpressionParser_Destroy(Ep** _ep);

/*for debug*/
void printKeyStruct(Ep *_ep, int _flag);

#endif /*__EXPRESSION_PARSER_H__*/
