#include<stdlib.h>
#include<stdio.h>
#include"ADTErr.h"
#include"binarySearchTree.h"
#include"test.h"
#define MAGICNUMBER 0XBEEFBEEF


typedef struct Node
{
	int m_data;
	struct Node* m_left;
	struct Node* m_right;
	struct Node* m_father;
}Node;


struct Tree
{
	size_t m_magicNumber;
	Node* m_root;
};

Tree* TreeCreate(void)
{
	Tree* newTree = (Tree*)malloc(sizeof(Tree));
	if(!newTree)
	{
		return NULL;
	}
	newTree -> m_magicNumber = MAGICNUMBER;
	newTree -> m_root = NULL;

	return newTree;
}
static void TreeDestroyRec(Node* _node)
{
	if(!_node)
	{
		return;
	}
	TreeDestroyRec(_node -> m_left);
	TreeDestroyRec(_node -> m_right);

	free(_node);
		
	
}

void TreeDestroy(Tree* _tree)
{
	if(!_tree || _tree -> m_magicNumber != MAGICNUMBER)
	{
		return;
	}
	TreeDestroyRec(_tree -> m_root);
	_tree -> m_magicNumber = 0;
	free(_tree);
}

static Node* createNode(int _data, Node* _father)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node)
	{
		return NULL;
	}
	node->m_data  	= 	_data;
	node->m_left  	=  	NULL;
	node->m_right 	=	NULL;
	node->m_father	=	_father;
	return node;
}
static Node* NodeInsertRec( Node* _node, int _data, Node *_father)
{
	if(_node == NULL)
	{
		return createNode(_data, _father);
	}
	if(_node -> m_data > _data)
	{
		_father = _node;
		_node -> m_left = NodeInsertRec( _node -> m_left, _data, _father);
	}
	if(_node -> m_data < _data)
	{
		_father = _node;
		_node -> m_right = NodeInsertRec(_node -> m_right, _data, _father);
	}
	return _node;

}


ADTErr TreeInsert(Tree* _tree, int _data)
{
	Node* newNode;
	if(!_tree)
	{
		return ERR_UNINITIALIZED;
	}
	if(_tree -> m_root == NULL)
	{
		_tree -> m_root = createNode(_data, _tree -> m_root);
		if(!_tree -> m_root)
	{
		return ERR_ALLOCATION;
	}
		return ERR_OK;
	}
	NodeInsertRec(_tree ->m_root, _data,_tree ->m_root);

	return ERR_OK;
}


static Node* searchRec(Node* _root, int _data) 
{ 
    if (_root == NULL || _root->m_data == _data) 
    {
       return _root; 
    }
     
    if (_root->m_data < _data) 
    {
       return searchRec(_root->m_right, _data); 
    }
	if( _root->m_data > _data)
   	{
   	 return searchRec(_root->m_left, _data); 
   	}
} 

int TreeIsDataFound(Tree* _tree, int _data)
{
	if(!_tree)
	{
		return FALSE;
	}
	if(searchRec(_tree -> m_root, _data))
	{
		return TRUE;
	}
	return FALSE;
}

static void printPostorder(Node* _node) 
{ 
    if (_node == NULL) 
    {
        return; 
  	}
     printPostorder(_node->m_left); 
     printPostorder(_node->m_right); 
     printf("Data:%d \n", _node->m_data); 
} 
  

static void printInorder(Node* _node) 
{ 
     if (_node == NULL) 
    {
        return; 
  	}
     printInorder(_node->m_left); 
     printf("Data:%d \n", _node->m_data);   
     printInorder(_node->m_right); 
} 
  
static void printPreorder(Node* _node) 
{ 
    if (_node == NULL) 
    {
        return; 
  	}
     printf("%d ",  _node->m_data);   
     printPreorder(_node->m_left);   
     printPreorder(_node->m_right); 
}  

void TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
	switch(_traverseMode)
	{
		case PRE_ORDER:
			printPreorder(_tree -> m_root);
			break;
		case IN_ORDER:
			printInorder(_tree -> m_root);
			break;
		case POST_ORDER:
			printPostorder(_tree -> m_root);

	}
}

int AreSimilarSubTrees(Node* _nodeA, Node* _nodeB)
{
	if(!_nodeA && ! _nodeB)
	{
		return TRUE;
	}
	if((!_nodeA && _nodeB) || (_nodeA && !_nodeB))
	{
		return FALSE;
	}
	if(_nodeB -> m_data == _nodeA -> m_data)
	{
		return AreSimilarSubTrees(_nodeA -> m_left, _nodeB -> m_left) && AreSimilarSubTrees(_nodeA -> m_right, _nodeB -> m_right);
	}
}

int AreSimilarTrees(Tree* _treeA, Tree* _treeB)
{
	if(! _treeA && ! _treeB)
	{
		return TRUE;
	}

	if((!_treeA && _treeB) || _treeA && ! _treeB) 
	{
		return FALSE;
	}

	return AreSimilarSubTrees(_treeA -> m_root, _treeB -> m_root);
}

static int IsFullSubTree(Node* _root)
{
	if(!_root -> m_left && ! _root -> m_right)
	{
		return 1;
	}
	if(_root -> m_left && _root -> m_right)
	{
		return IsFullSubTree(_root -> m_left) && IsFullSubTree(_root -> m_right);
	}
	else 
	{
		return FALSE;
	}
}

int IsFullTree(Tree* _tree)
{
	if(!_tree)
	{
		return TRUE;
	}
	return IsFullSubTree(_tree -> m_root);

}
static int IsPerfectSubTree(Node* _node, int* _counterEfflevel, int _counterLevel)
{
	if(!_node -> m_left && ! _node -> m_right && *_counterEfflevel == _counterLevel)
	{
		return TRUE;
	}
	if(!_node -> m_left && _node -> m_left || _node -> m_left && !_node -> m_left)
	{
		return FALSE;
	}
	if(_root -> m_left && _root -> m_right)
	{

		*_counterEfflevel += 1;
		return IsPerfectSubTree(_node -> m_left, _counterEfflevel, _counterLevel) && IsFullSubTree(_node -> m_right, _counterEfflevel, _counterLevel) ;
	}
}

int IsPerfect(Tree* _tree)
{
	int counterNode = 0;
	int counterLevel = 0;
	if(!_tree)
	{
		return TRUE;
	}
	while(_tree -> m_left)
	{
		_counterLevel ++;
	}
	return IsPerfectSubTree(_tree -> m_root, counterEfflevel, counterLevel);
}