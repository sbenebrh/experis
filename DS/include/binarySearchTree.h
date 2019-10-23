#ifndef __BST_H__
#define __BST_H__
#include"ADTErr.h"
#define FALSE 0
#define TRUE 1
typedef struct Tree Tree;

typedef enum 
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
}TreeTraverse;

/**
* @function: TreeCreate
* @brief create a BST
* 
* 
*
* @return pointer to the BST

* @errors: return null if we have a problem with allocation
*		   
**/
Tree* TreeCreate(void);

/**
* @function: TreeDestroy
* @brief destroy a BST by destroying every node in the BST first
* 
* @param _tree: pointer to the tree
*		
**/
void TreeDestroy(Tree* _tree);

/**
* @function: TreeInsert
* @brief create a new node and insert it at the appropriate place in the tree
* 
* @param _tree: pointer to the tree
* @param _data : the data to insert in the tree
*
* @return err ok if everything was good

* @errors: return err uninitialized if we have _tree doesn t exist
* 			return err allocation if we are not able to create a new node
*    
**/
ADTErr TreeInsert(Tree* _tree, int _data);
/**
* @function: TreeIsDataFound
* @brief check in the tree if the data exist
* 
* @param _tree: pointer to the tree
* @param _data : the data to search in the tree
*
* @return 1 if the data is in the founded and 0 if not

* @errors: return 0 if the tree doesnt exist
*    
**/

int TreeIsDataFound(Tree* _tree, int _data);

/**
* @function: TreePrint
* @brief print every data according to the traversal mode choosen by user
* 
* @param _tree: pointer to the tree
* @param _traverseMode : traversalmode for printing the tree
*
* @return 1 if the data is in the founded and 0 if not

* @errors: return 0 if the tree doesnt exist
*    
**/
void TreePrint(Tree* _tree, TreeTraverse _traverseMode);
#endif
