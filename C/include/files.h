/*
 * queue.h
 * framework for files
 * Version: 0.1
 * creation: 19/12/2018
 * last change: 20/12/2018
 *      Author: samuel ben ibgui   
 * 	    benebrhi@gmail.com
*/

#ifndef _FILES_H
#define _FILES_H


/** 
 * @function: PrintNLastLines
 * print on screen the last N lines of a file
 *
 * @param _filePath : the path of the file 
 * @param _nLastLines: numbers of lines the user want to print
 * @return no return value
 *			
 **/
void PrintNLastLines(char* _filePath, int _nLastLines);


/** 
 * @function: DictNumberOfLetters
 * create a dictionnary with keys = letters and value = number of occurence of a letter in a file 
 * print the dictionnary in result file
 *
 * @param _filePath : the path of the file 
 *
 * @return no return value
 *			
 **/
void DictNumberOfLetters(char* _filePath);

/** 
 * @function: FrequenciesWords
 * create a dictionnary with keys = words and value = number of occurence of a letter in a file 
 * print the dictionnary in result file
 *
 * @param _filePath : the path of the file 
 *
 * @return no return value
 *			
 **/
void FrequenciesWords(char* _fileName);


#endif
