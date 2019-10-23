#include "mu_test.h"
#include <limits.h>

/************************/
/* functions under test */
int add(int a, int b)
{
	return a + b;
}

/************************/


UNIT(add_small_ints)	
	int a = 42 -16;
	int b = 16;

	long int r = add(a, b);

	ASSERT_THAT(r == 42);		
END_UNIT

UNIT(add_is_commutative)	
	int a = 8762;
	int b = 9321;

	long int r1 = add(a, b);
	long int r2 = add(b, a);		
	ASSERT_THAT(r1 == r2);	
END_UNIT

UNIT(add_0_does_not_change_result)	
	int a = 131415;
	int b = 0;

	long int r1 = add(a, b);
	long int r2 = add(b, a);	

	ASSERT_THAT(r1 == a);
	ASSERT_THAT(r2 == a);
	ASSERT_THAT(r1 == r1);
END_UNIT

UNIT(add_big_ints)	
	int a = INT_MAX / 2;
	int b = INT_MAX / 3;

	int r = add(a, b);
	
	ASSERT_THAT(r > a);	
	ASSERT_THAT(r > b);	
END_UNIT



UNIT(add_really_big_ints)	
	int a = INT_MAX - INT_MAX / 4;
	int b = INT_MAX / 2;

	int r = add(a, b);
	
	ASSERT_THAT(r > a);	
	ASSERT_THAT(r > b);	
END_UNIT


TEST_SUITE(C Unit Test Demo for mu_test!)
	TEST(add_small_ints)
	IGNORE_TEST(add_is_commutative)	
	TEST(add_0_does_not_change_result)	
	TEST(add_big_ints)	
	TEST(add_really_big_ints)	
END_SUITE



