#include <stdlib.h>/*free*/
#include <stdio.h>/*printf*/
#include "expTree.h"
#include "ExpressionParser.h"
#include "../unitest/mu_test.h"

static double addition(double _l, double _r)
{
	return _l + _r;
}

UNIT(expP_create)
	Ep* test = NULL;
	test = ExpressionParser_Create();
	ASSERT_THAT(test != NULL);
	ExpressionParser_Destroy(&test);

END_UNIT

UNIT(expP_addFunc)
	Ep* test = NULL;
	union func pf;
	pf.m_bin = addition;
	test = ExpressionParser_Create();
	ASSERT_THAT(test != NULL);

	ASSERT_THAT(ExpressionParser_add_func(test,pf, BINARYOP, "addition") == EXPRESSION_PARSER_SUCCEES);
	ExpressionParser_Destroy(&test);

END_UNIT

UNIT(expP_addVar1)
	Ep* test = NULL;
	int a = 10;
	char var1[10] = "X";
	test = ExpressionParser_Create();

	ASSERT_THAT(ExpressionParser_add_Var(test, a, var1) == EXPRESSION_PARSER_SUCCEES);
	ExpressionParser_Destroy(&test);

END_UNIT

UNIT(expP_addVar2)
	Ep* test = NULL;
	int a = 10;
	char var1[10] = "X";
	test = ExpressionParser_Create();

	ASSERT_THAT(ExpressionParser_add_Var(test, a, var1) == EXPRESSION_PARSER_SUCCEES);
	ASSERT_THAT(ExpressionParser_add_Var(test, a, var1) == EXPRESSION_PARSER_SUCCEES);
	ExpressionParser_Destroy(&test);

END_UNIT

UNIT(expP_addfunc2)
	Ep* test = NULL;
	union func pf;
	pf.m_bin = addition;
	test = ExpressionParser_Create();
	ASSERT_THAT(test != NULL);

	ASSERT_THAT(ExpressionParser_add_func(test,pf, BINARYOP, "+") == EXPRESSION_PARSER_SUCCEES);
	printKeyStruct(test, 1);
	ExpressionParser_Destroy(&test);

END_UNIT

UNIT(expP_addVar3)
	Ep* test = NULL;
	int a = 10, b = 9;
	char var1[10] = "X";
	char var2[10] = "Y";
	test = ExpressionParser_Create();

	ASSERT_THAT(ExpressionParser_add_Var(test, a, var1) == EXPRESSION_PARSER_SUCCEES);
	ASSERT_THAT(ExpressionParser_add_Var(test, b, var2) == EXPRESSION_PARSER_SUCCEES);

	printKeyStruct(test, 0);
	ExpressionParser_Destroy(&test);

END_UNIT

UNIT(expP_parse)
	Ep* test = NULL;
	union func pf;
	N* exp = NULL;
	pf.m_bin = addition;
	char statement[10] = "1 + 2 ";
	test = ExpressionParser_Create();
	ASSERT_THAT(test != NULL);

	ASSERT_THAT(ExpressionParser_add_func(test,pf, BINARYOP, "+") == EXPRESSION_PARSER_SUCCEES);
	exp = ExpressionParser_parse(test, statement);
	ASSERT_THAT(exp != NULL);
	ExpressionParser_Destroy(&test);

END_UNIT

UNIT(expP_calc)
	Ep* test = NULL;
	union func pf;
	N* exp = NULL;
	double result = 0;
	pf.m_bin = addition;
	char statement[10] = "1 + 2 ";
	test = ExpressionParser_Create();
	ASSERT_THAT(test != NULL);

	ASSERT_THAT(ExpressionParser_add_func(test,pf, BINARYOP, "+") == EXPRESSION_PARSER_SUCCEES);

	exp = ExpressionParser_parse(test, statement);
	ASSERT_THAT(exp != NULL);
	
	result = ExpressionParser_calc(test,exp);
	printf("%f\n"	,result);
	ASSERT_THAT(result > 0);
	ExpressionParser_Destroy(&test);

END_UNIT

UNIT(expP_calc2)
	Ep* test = NULL;
	union func pf;
	N* exp = NULL;
	double result;
	pf.m_bin = addition;
	int a = 10;
	char var1[10] = "X";
	char statement[10] = "1 + X + 2 ";
	test = ExpressionParser_Create();
	ASSERT_THAT(test != NULL);

	ASSERT_THAT(ExpressionParser_add_func(test,pf, BINARYOP, "+") == EXPRESSION_PARSER_SUCCEES);
	ASSERT_THAT(ExpressionParser_add_Var(test, a, var1) == EXPRESSION_PARSER_SUCCEES);
	exp = ExpressionParser_parse(test, statement);
	ASSERT_THAT(exp != NULL);
	result = ExpressionParser_calc(test,exp);
	printf("%f\n",result );
	ASSERT_THAT(result > 0);
	ExpressionParser_Destroy(&test);

END_UNIT

TEST_SUITE(Unit test for ExpressionParser)
	TEST(expP_create)
	TEST(expP_addFunc)
	TEST(expP_addVar1)
	TEST(expP_addVar2)
	TEST(expP_addfunc2)
	TEST(expP_addVar3)
	TEST(expP_parse)
	TEST(expP_calc)
	TEST(expP_calc2)
END_SUITE





/*
typedef enum 
{
	SUCCEED,
	FAIL
}TestResult;

void PrintResult(char* _testName, TestResult _result)
{
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}

TestResult TestCreateNumber()
{
	N* number = NULL;
	int a = 10;
	number = num(a);
	if(PrintData(number) == 10)
	{
		free(number);
		return SUCCEED;
	}
	free(number);
	return FAIL;
}

TestResult TestAddNumber()
{
	TestResult result = FAIL;
	N* addn = NULL, *left = NULL, *right = NULL ;
	double a = 21;
	double b = -21;

	left = num(a);
	right = num(b);
	addn = add(left, right);
	if(addn)
	{
		result = SUCCEED;
	}
	free(left);
	free(right);
	free(addn);

	return result;
}

TestResult TestsubNumber()
{
	TestResult result = FAIL;
	N* subn = NULL, *left = NULL, *right = NULL ;
	double a = 21;
	double b = -21;

	left = num(a);
	right = num(b);
	subn = subs(left, right);
	if(subn)
	{
		result = SUCCEED;
	}
	free(left);
	free(right);
	free(subn);

	return result;
}
TestResult TestmulNumber()
{
	TestResult result = FAIL;
	N* muln = NULL, *left = NULL, *right = NULL ;
	double a = 21;
	double b = -21;

	left = num(a);
	right = num(b);
	muln = mul(left, right);
	if(muln)
	{
		result = SUCCEED;
	}
	free(left);
	free(right);
	free(muln);

	return result;
}

TestResult TestcalNumber()
{
	TestResult result = FAIL;
	N* addn = NULL, *left = NULL, *right = NULL ;
	double a = 21;
	double b = -21;

	left = num(a);
	right = num(b);
	addn = add(left, right);
	if(calc(addn,NULL) == 0)
	{
		result = SUCCEED;
	}
	free(left);
	free(right);
	free(addn);

	return result;
}*/

/*int main()
{
	PrintResult("TestCreateNumber", TestCreateNumber());
	PrintResult("TestAddNumber", TestAddNumber());
	PrintResult("TestsubNumber", TestsubNumber());
	PrintResult("TestmulNumber", TestmulNumber());
	PrintResult("TestcalNumber", TestcalNumber());
	return 0;
}*/
