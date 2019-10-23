#ifndef __TEST_VEC_H__
#define __TEST_VEC_H__

#include"vector.h"
typedef enum 
{
	SUCCEED,
	FAIL
}TestResult;
/*create vector expect no error*/
TestResult TestVecCreate1(Vector_Result* _status);

/*create vector with 0,0 input expect error*/
TestResult TestVecCreate2(Vector_Result* _status);

/*create vector with 0, size input expect no error*/
TestResult TestVecCreate3(Vector_Result* _status);

/*create vector with size,0 input expect no error*/
TestResult TestVecCreate4(Vector_Result* _status);

/*destroy vector expect no error*/
TestResult TestVecDestroy1(Vector_Result* _status);

/*destoy vector twice expect no bug*/
TestResult TestVecDestroy2(Vector_Result* _status);

/*append element to the vector expect no bug*/
TestResult TestVecAppend1(Vector_Result* _status);

/*append element to the vector and check number of element*/
TestResult TestVecAppend2(Vector_Result* _status);
TestResult TestVecAppend3(Vector_Result* _status);
TestResult TestVecAppend4(Vector_Result* _status);

/*append element to the vector using resize*/
TestResult TestVecAppend5(Vector_Result* _status);
TestResult TestVecRemove1(Vector_Result* _status);
TestResult TestVecRemove2(Vector_Result* _status);
TestResult TestVecRemove3(Vector_Result* _status);
TestResult TestVecGet1(Vector_Result* _status);
TestResult TestVecGet2(Vector_Result* _status);
TestResult TestVecSet1(Vector_Result* _status);
TestResult TestVecSet2(Vector_Result* _status);

TestResult TestVecAppend11(Vector_Result* _status);
TestResult TestVecAppend12(Vector_Result* _status);
TestResult TestVecAppend13(Vector_Result* _status);
TestResult TestVecAppend14(Vector_Result* _status);

TestResult TestVeDestroy11(Vector_Result* _status);

TestResult TestVecRemove12(Vector_Result* _status);





#endif