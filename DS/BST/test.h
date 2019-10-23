#ifndef __TEST_BST_H__
#define __TEST_BST_H__
#include"ADTErr.h"
#include"binarySearchTree.h"


void PrintResult(char* _testName, TestResult _result, ADTErr _stat);
TestResult TestCreateBST();
TestResult TestDestroy();
TestResult TestInsert1(ADTErr* _status);
TestResult TestInsert2(ADTErr* _status);
TestResult Testsearch1();
TestResult Testsearch2();
TestResult Testsearch3();
TestResult Testsearch4();
TestResult TestIsFullTree1(ADTErr* _status);
TestResult TestIsFullTree2(ADTErr* _status);
TestResult TestAreSimilareTrees1(ADTErr* _status);
TestResult TestAreSimilareTrees2(ADTErr* _status);
#endif
