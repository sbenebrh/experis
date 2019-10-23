#ifndef _RECURSIVE_H
#define _RECURSIVE_H


#include"../DS/include/stack.h"
/*
* @function:factorial
*
* @brief: calculate the n factorial using recursion

* @param _n: the number wich we want to solve its factorial
*
* @return the factorial
* @error if n < 0
*/
int factorial(int _n);

/*
* @function:power
*
* @brief: calculate the n power k using recursion

* @param _n: the base
* @param _k : the exponent
*
* @return the pow of n by k
* @error if n < 0
*/
int power(int _num,int _k);

/*
* @function:sum
*
* @brief: calculate the sum of element in  an array using recursion

* @param arr: the array
* @param size : the size of the array
*
* @return the sum of the array
* @error if invalide array
*/
int sum(int* arr, int size);

/*
* @function:maximum
*
* @brief: calculate the maximum of  an array using recursion

* @param arr: the array
* @param size : the size of the array
*
* @return the maximum item of the array
* @error if invalide array
*/
int maximum(int ar[], int n);

/*
* @function:average
*
* @brief: calculate the average of element in  an array using recursion

* @param arr: the array
* @param size : the size of the array
*
* @return the average of the array
* @error if invalide array
*/
double average(int a[], int n);

/*
* @function:fiboRecursive
*
* @brief: calculate the neme element of fibonacci using recursion

* @param _n: the element wich we want to calculate its fibo
* 
*
* @return the fibo n number
*
*/
size_t fiboRecursive(size_t _n);
int IsPalyndromeBis(char*_str);
char* reverseString(char* _str);

/*
* @function:fiboRecursive
*
* @brief: calculate the neme element of fibonacci using recursion

* @param _n: the element wich we want to calculate its fibo
* 
*
* @return the fibo n number
*
*/
size_t fiboIter(size_t _n);
int IsPalindrome(char* _str);
void Hanoi(int _n, char _from, char _to, char _via);
void StackHanoi(int _n, char _from, char _to, char _via);



#endif
