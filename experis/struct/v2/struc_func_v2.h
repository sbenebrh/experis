/*
 * struc_func_v2.h
 *  Framework 
 *     a tiny unit framework for struct and sort the struct array. 
 * Version: 0.01
 * creation date : 06/12/2018
 * last Change : 06/12/2018
 *      Author: samuel ben ibgui   
 * 	    benebrhi@gmail.com
 */

#include<stdio.h>
#define IS_SWAPPED 0
#define SEGMENTATION_FAULT 
#define ERR_ARRAY_SIZE


/** 
 * @description struct of student contain info about him
 *
 * @param id : id of the student
 * @param age : age of the student
 * @param edu : number of years studies
 * 
 **/
typedef struct students
{
	int id;
	int age;
	int edu;
	
}student;

void print(personn * _arrayPersonn, int _size);
void BubbleSortForStruct(personn * _arrayPersonn,int _size);
