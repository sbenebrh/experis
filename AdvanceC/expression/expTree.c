#include "expTree.h"

#include <stdlib.h>/*malloc*/
#include <stdio.h>/*printf for debug*/
#include <math.h>/*pow*/

#include "HashMap.h"

#define CHECKNULLPARAM(X)   do{if(NULL == (X)) return NULL;}while(0)





union data
{
	double 		(*m_uni)(double);
	double		(*m_bin)(double,double);
	double 		m_value;
};

struct N
{
	enum NodeType 	m_type;
	union data 		m_data;
	N*	  			m_left;
	N*    			m_right;
};

/*##########################################################################*/
static void  		initialiseNode(N* _initialN, N* _sonL, N* _sonR, enum NodeType _type);
static N* 			createNode();
static double 		addition(double _l, double _r);
static double 		substraction(double _l, double _r);
static double 		multiplication(double _l, double _r);
static double 		division(double _l, double _r);
static double 		powerF(double _l, double _r);
/*##########################################################################*/

N* num(double _num)
{
	N* numN= NULL;

	numN = createNode();
	CHECKNULLPARAM(numN);

	initialiseNode(numN, NULL, NULL, VALUE);
	numN -> m_data.m_value = _num;
	return numN;
}


N* add(N* _lnum, N* _rnum)
{
	N* addN = NULL;
	CHECKNULLPARAM(_lnum);
	CHECKNULLPARAM(_rnum);

	addN = createNode();
	CHECKNULLPARAM(addN);

	initialiseNode(addN, _lnum, _rnum, BINARY_OP);
	addN -> m_data.m_bin = addition; 

	return addN;
}

N* subs(N* _lnum, N* _rnum)
{
	N* subN = NULL;
	CHECKNULLPARAM(_lnum);
	CHECKNULLPARAM(_rnum);

	subN = createNode();
	CHECKNULLPARAM(subN);

	initialiseNode(subN, _lnum, _rnum, BINARY_OP);
	subN -> m_data.m_bin = substraction; 

	return subN;
}

N* binOp(N* _lnum, N* _rnum,double(*f)(double,double))
{
	N* binN = NULL;
	CHECKNULLPARAM(_lnum);
	CHECKNULLPARAM(_rnum);

	binN = createNode();
	CHECKNULLPARAM(binN);

	initialiseNode(binN, _lnum, _rnum, BINARY_OP);
	binN -> m_data.m_bin = f; 

	return binN;
}
N* unOp(N* _lnum, double(*f)(double))
{
	N* uniN = NULL;
	CHECKNULLPARAM(_lnum);

	uniN = createNode();
	CHECKNULLPARAM(uniN);

	initialiseNode(uniN, _lnum, NULL, BINARY_OP);
	uniN -> m_data.m_uni = f; 

	return uniN;
}
N* mul(N* _lnum, N* _rnum)
{
	N* mulN = NULL;
	CHECKNULLPARAM(_lnum);
	CHECKNULLPARAM(_rnum);

	mulN = createNode();
	CHECKNULLPARAM(mulN);

	initialiseNode(mulN, _lnum, _rnum, BINARY_OP);
	mulN -> m_data.m_bin = multiplication; 

	return mulN;
}

N* divid(N* _lnum, N* _rnum)
{
	N* divN = NULL;
	CHECKNULLPARAM(_lnum);
	CHECKNULLPARAM(_rnum);

	divN = createNode();
	CHECKNULLPARAM(divN);

	initialiseNode(divN, _lnum, _rnum, BINARY_OP);
	divN -> m_data.m_bin = division;

	return divN;
}

N* power(N* _lnum, N* _rnum)
{
	N* powN = NULL;
	CHECKNULLPARAM(_lnum);
	CHECKNULLPARAM(_rnum);

	powN = createNode();
	CHECKNULLPARAM(powN);

	initialiseNode(powN, _lnum, _rnum, BINARY_OP);
	powN -> m_data.m_bin = powerF;

	return powN;
}

double calc(N* _root, HashMap* vars)
{
	switch(_root -> m_type)
	{
		case VALUE:
			return _root ->m_data.m_value;
		case BINARY_OP:
			return _root -> m_data.m_bin(calc(_root -> m_left,vars), calc(_root -> m_right,vars));
		case UNARY_OP:
			return _root -> m_data.m_uni(calc(_root->m_left,vars));
		default:
		/*TODO error*/
			return -1;
	}
}

/*for debug*/
double PrintData(N* _node)
{
	return  _node -> m_data.m_value ;
}
enum NodeType getType(const N* _node)
{
	return _node -> m_type;
}
double getValueN(const N* _node)
{
	return _node -> m_data.m_value;
}

double doubleBinFunc(const N* _node,double _first, double _second)
{
	return _node -> m_data.m_bin(_first, _second);
}
double doubleUnFunc(const N* _node,double _first)
{
	return _node -> m_data.m_uni(_first);
}
N* getsonL(const N* _node)
{
	return _node -> m_left;
}
N* getsonR(const N* _node)
{
	return _node -> m_right;
}
/*##########################################################################*/
static void  initialiseNode(N* _initialN, N* _sonL, N* _sonR, enum NodeType _type)
{
	_initialN -> m_right = _sonR;
	_initialN -> m_left = _sonL;
	_initialN -> m_type = _type;
}

static N* createNode()
{
	N* newN= NULL;
	newN = (N*)malloc(sizeof(N));
	return newN;
}

static double addition(double _l, double _r)
{
	return _l + _r;
}

static double substraction(double _l, double _r)
{
	return _l - _r;
}

static double multiplication(double _l, double _r)
{
	return (_l) * (_r);
}

static double division(double _l, double _r)
{
	if(0 == _r)
	{
		return 0;
	}
	return (_l) / (_r);
}

static double powerF(double _l, double _r)
{
	return pow(_l, _r);
}
