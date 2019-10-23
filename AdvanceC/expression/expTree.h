#ifndef __EXP_TREE_H__
#define __EXP_TREE_H__
/** 
 *  @file expTree.h
 *  @brief framework for creating a expression tree and calculate result
 * 
 *  @details creating node according to an expression or number
 *  
 * 
 *  @author samuel ben Ibgui(benebrhi@gmail.com) 
 * 
 *  
 */ 

#include "HashMap.h"

enum NodeType
{
	VALUE,
	UNARY_OP,
	BINARY_OP,
	VARIABLE
};

typedef struct N N;

/** 
 * @brief num
 * @details create a node to contains number
 *
 * @params[in] _num : the number to be contain
 * 
 * return a new node on success and null on fail
 */
N* num(double _num);
/** 
 * @brief add/subs/mul/divid/power
 * @details create a node to contains an expression and pointeur to two nodes
 *
 * @params[in] _lnum : the left node of the expression
 * @params[in] _rnum : the right node of the expression
 * 
 * return a new node on success and null on fail
 */
N* add(N* _lnum, N* _rnum);
N* subs(N* _lnum, N* _rnum);
N* mul(N* _lnum, N* _rnum);
N* divid(N* _lnum, N* _rnum);
N* power(N* _lnum, N* _rnum);

N* binOp(N* _lnum, N* _rnum,double(*f)(double,double));
N* unOp(N* _lnum, double(*f)(double));


double calc(N* _root, HashMap* vars);
void DestroyTree(N* _root);

enum NodeType getType(const N* _node);
double getValueN(const N* _node);
double doubleBinFunc(const N* _node,double _first, double second);
double doubleUnFunc(const N* _node,double _first);
N* getsonL(const N* _node);
N* getsonR(const N* _node);
/*for debug*/
double PrintData(N* _node);
#endif
