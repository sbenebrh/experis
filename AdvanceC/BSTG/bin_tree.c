#include<stdlib.h>
#include"bin_tree.h"
/*#include"list.h"
#include"list_itr.h"*/

typedef struct Node
{
	void*			 	m_data;
	struct Node* 		m_left;
	struct Node* 		m_right;
	struct Node* 		m_father;
}Node;


struct BSTree
{

	Node 				m_guard;
	LessComparator   	m_comparatorFunc;

};


/*################STATIC#################*/
static void 		DestroyInside(Node* _destroyNode, void (*_destroyer)(void*) );
static BSTreeItr    BSTree_InsertRec(Node* _root,void* _item, Node* _father, LessComparator _comparator,int* _flag);
static Node* 		createNode(void* _data, Node* _father);
static BSTreeItr 	myBstForEach(BSTree* _tree, Node* _node,int(*f)(void*,void*), void* _context);
static BSTreeItr 	BST_findBegRec(Node* _node);
static void* 		removeLeaf(BSTreeItr _it);
static int 			IsLeaf(BSTreeItr _it);
static void 		SwapItr(BSTreeItr _it1, BSTreeItr _it2);
static BSTreeItr	PreOrderForEach(Node* _node,int(*f)(void*,void*), void* _context);
static BSTreeItr	InOrderForEach(Node* _node,int(*f)(void*,void*), void* _context);
static BSTreeItr	PostOrderForEach(Node* _node,int(*f)(void*,void*), void* _context);
static void			BFS(Node* _node,int(*f)(void*,void*), void* _context);
/*#####################################*/

BSTree* BSTree_Create(LessComparator _less)
{
	BSTree* newTree = (BSTree*)malloc(sizeof(BSTree));
	if(newTree)
	{
		newTree -> m_comparatorFunc = _less;
		newTree -> m_guard.m_left = NULL;
		newTree -> m_guard.m_right = NULL;
		newTree -> m_guard.m_father = NULL;
		newTree -> m_guard.m_data = NULL;

	}
	return newTree;
}

void  BSTree_Destroy(BSTree** _tree, void (*_destroyer)(void*))
{
	if(_tree && *_tree)
	{
		if( (*_tree)-> m_guard.m_left == NULL)
		{
			DestroyInside((*_tree) -> m_guard.m_left, _destroyer);
		}
		free(*_tree);
		*_tree = NULL;
	}
}

BSTreeItr BSTree_Insert(BSTree* _tree, void* _item)
{
	int flag = 0;
	BSTreeItr result = &_tree -> m_guard;
	if(NULL != _tree)
	{
		if(_tree -> m_guard.m_left == NULL)
		{
			_tree -> m_guard.m_left = createNode(_item, &_tree -> m_guard);
			if(NULL != _tree -> m_guard.m_left)
			{
				result =& _tree -> m_guard;
			}
			
			
		}
		else
		{
			result = BSTree_InsertRec(_tree -> m_guard.m_left, _item,& _tree -> m_guard, _tree -> m_comparatorFunc, &flag);
			
		}
	}
	return result;
}

BSTreeItr BSTree_FindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context)
{
	
	if(NULL == _tree || _predicate == NULL || _tree -> m_guard.m_left == NULL)
	{
		return NULL;
	}
	return myBstForEach((void*)_tree,_tree -> m_guard.m_left,_predicate,_context);
}

BSTreeItr BSTreeItr_Begin(const BSTree* _tree)
{
	if(NULL == _tree)
	{
		return NULL;
	}
	if(_tree -> m_guard.m_left == NULL)
	{
		return (void*) &_tree -> m_guard;
	}
	return BST_findBegRec((void*)_tree -> m_guard.m_left);
	
}

BSTreeItr BSTreeItr_End(const BSTree* _tree)
{
	if(_tree)
	{
		return (void*)&_tree -> m_guard;
	}
	return NULL;
}

int BSTreeItr_Equals(BSTreeItr _a, BSTreeItr _b)
{
	if(!_a || !_b)
	{
		return 0;
	}
	return _a == _b;
}

BSTreeItr BSTreeItr_Next(BSTreeItr _it)
{
	Node* node;
	if(_it)
	{
		node = ((Node*)_it);
		if(((Node*)_it) -> m_right != NULL)
		{
			return BST_findBegRec(((Node*)_it) -> m_right);
		}

		while(node -> m_father -> m_right == node)
		{
			node = node -> m_father;
		}
			/*one element in the tree*/
		return (BSTreeItr)node -> m_father;
	}
	return NULL;
}
BSTreeItr BSTreeItr_Prev(BSTreeItr _it)
{
	Node* node;
	if(_it)
	{
		node = ((Node*)_it);
		if(((Node*)_it) -> m_left == ((Node*)_it))
		{
			return _it;
		}
		if(((Node*)_it) -> m_left)
		{
			while(node -> m_right)
			{
				node = node -> m_right;
			}
			return(BSTreeItr) node;
		}
		while(node -> m_father -> m_left == node)
		{
			node = node -> m_father;
		}
		if(node -> m_father == node)
		{
			while(node -> m_left)
			{
				node = node -> m_left;
				
			}
			return (BSTreeItr)node;
		}
		return (BSTreeItr)node -> m_father;

	}
	return NULL;
}
/*TODO REPAIR FUNCTION*/
void* BSTreeItr_Remove(BSTreeItr _it)
{
	BSTreeItr itr;
	void* data;

	if(!_it)
	{
		return NULL;
	}
	if(_it == BSTreeItr_Next(_it))
	{
		return NULL;
	}
	/*a leaf*/
	if((((Node*)_it) -> m_right == NULL &&  ((Node*)_it) -> m_left == NULL) || (((Node*)_it) -> m_right == NULL &&  
		((Node*)_it) -> m_left == ((Node*)_it) -> m_left -> m_left))
	{
		data = removeLeaf(_it);
		return data;
	}
	itr = BSTreeItr_Next(_it);

	while(!IsLeaf(itr))
	{
		itr = BSTreeItr_Next(itr);
	}

	SwapItr(_it, itr);

	data = removeLeaf(itr);
	return data;

}

void* BSTreeItr_Get(BSTreeItr _it)
{
	if(_it)
	{
		return ((Node*) _it) -> m_data;
	}
	return NULL;
}

BSTreeItr BSTree_ForEach(const BSTree* _tree, TreeTraversalMode _mode,
                 ActionFunction _action, void* _context)
{
	Node * node;
	switch(_mode)
	{
		case BSTREE_TRAVERSAL_PREORDER:
			node = PreOrderForEach((void*)&_tree -> m_guard.m_left,_action,_context);
			break;
		case BSTREE_TRAVERSAL_INORDER:
			node = InOrderForEach((void*)_tree -> m_guard.m_left,_action,_context);
			break;
		case BSTREE_TRAVERSAL_POSTORDER:
			node = PostOrderForEach((void*)&_tree -> m_guard.m_left,_action,_context);
			break;
		case BSTREE_TRAVERSAL_BREADTH_FIRST:
			 BFS((void*)&_tree -> m_guard,_action,_context);
			break;
	}
	return node;

}
/*#################################STATICS##############*/
static void DestroyInside(Node* _destroyNode, void (*_destroyer)(void*))
{
	if(_destroyNode == NULL)
	{
		return;
	}/*beside this condition change left to begin to NULL*/
	if(_destroyNode == _destroyNode -> m_left)
	{	
		_destroyNode -> m_left = NULL;
	}
	DestroyInside(_destroyNode -> m_left, _destroyer);
	DestroyInside(_destroyNode -> m_right, _destroyer);
	if(_destroyer != NULL)
	{
		_destroyer(_destroyNode -> m_data);
	}
	
	free(_destroyNode);
	
}

static BSTreeItr BSTree_InsertRec(Node* _root,void* _item, Node* _father, LessComparator _comparator,int* _flag)
{
	if(_root == NULL )
	{
		return (BSTreeItr)createNode(_item, _father);
	}
	if(_root -> m_left == _root && _comparator(_item,_root ->  m_data) == 1)
	{
		_root  = (BSTreeItr)createNode(_item, _father);
		return _root ;
	}
	if(_comparator(_item,_root ->  m_data) == 1)
	{
		_father = _root;
		_root -> m_left = BSTree_InsertRec( _root -> m_left, _item, _father,_comparator,_flag);
	}
	else if(_comparator(_item,_root -> m_data) == 0)
	{
		_father = _root;
		*_flag = 1;
		_root -> m_right = BSTree_InsertRec(_root -> m_right, _item, _father,_comparator, _flag);
		
	}
}

static Node* createNode(void* _data, Node* _father)
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
/*check if it work*/
static BSTreeItr myBstForEach(BSTree* _tree,Node* _node,int(*f)(void*,void*), void* _context)
{
	BSTreeItr it = BSTreeItr_Begin(_tree);
	while(it != BSTreeItr_End(_tree) && f(((Node*)it) -> m_data, _context) == 0)
	{
		it = BSTreeItr_Next(it);
	}
	return it;
}

static BSTreeItr BST_findBegRec(Node* _node)
{
	if(NULL == _node -> m_left)
	{
		return _node;
	}
	if(_node -> m_left == _node)
	{
		return _node;
	}

	if(_node -> m_left != _node)
	{
		return BST_findBegRec(_node -> m_left);
	}
}

static void* removeLeaf(BSTreeItr _it)
{
	void* data;
	Node* node = ((Node*)_it);
	/*begin*/
	if(_it == ((Node*)_it) -> m_left)
	{
		((Node*)_it)-> m_father -> m_left = ((Node*)_it) -> m_father;
	}
	data = ((Node*)_it) -> m_data;
	((Node*)_it) -> m_data = NULL;
	free(node);
	return data;

}
static int IsLeaf(BSTreeItr _it)
{
	return (((Node*)_it) -> m_right == NULL &&  ((Node*)_it) -> m_left == NULL);
}

static void SwapItr(BSTreeItr _it1, BSTreeItr _it2)
{
	void* tmp = ((Node*)_it1) -> m_data;
	((Node*)_it1) -> m_data =  ((Node*)_it2) -> m_data;
	((Node*)_it2) -> m_data = tmp;
}

static BSTreeItr PreOrderForEach(Node* _node,int(*f)(void*,void*), void* _context)
{
	if(_node == NULL || _node == _node -> m_left)
	{
		return _node;
	}
	if(f(_node -> m_data,_context) == 0)
	{
		return _node;
	}
	PreOrderForEach(_node -> m_left,f,_context);
	PreOrderForEach(_node -> m_right,f,_context);
}

static BSTreeItr InOrderForEach(Node* _node,int(*f)(void*,void*), void* _context)
{
	if(_node == NULL || _node == _node -> m_left)
	{
		return _node;
	}
	InOrderForEach(_node -> m_left,f,_context);
	if(f(_node -> m_data,_context) == 0)
	{
		return _node;
	}
	InOrderForEach(_node -> m_right,f,_context);

	return _node;
}

static BSTreeItr	PostOrderForEach(Node* _node,int(*f)(void*,void*), void* _context)
{
	if(_node == NULL || _node == _node -> m_left)
	{
		return _node;
	}
	PostOrderForEach(_node -> m_left,f,_context);
	PostOrderForEach(_node -> m_right,f,_context);
	if(f(_node -> m_data,_context) == 0)
	{
		return _node;
	}
}
/*
static void	BFS(Node* _node,int(*f)(void*,void*), void* _context)
{
	List* _list = List_Create();
	ListItr itr = _node -> m_left;
	int flag = 0;
	Node* n;
	if(NULL == _list)
	{
		return;
	}
	if(List_PushTail(_list, _node -> m_left ) != LIST_SUCCESS)
	{
		return;
	}
	while(ListItr_Equals(ListItr_Begin(_list),ListItr_End(_list)) == 0)
	{
		itr = ListItr_Next(ListItr_Begin(_list));
		n = (Node*)ListItr_Remove(ListItr_Begin(_list));
		if(f(n -> m_data) == 0)
		{
			return;
		}
		if(n -> m_right)
		{
			ListItr_InsertBefore(ListItr_End(_list),n -> m_right);
		}
		if(n -> m_left && n -> m_left != n)
		{
			ListItr_InsertBefore(ListItr_End(_list),n -> m_left);
		}
		if(n -> m_left == n && !flag)
		{
			ListItr_InsertBefore(ListItr_End(_list),n -> m_left);
			flag = 1;
		}
	}
}*/
static void	BFS(Node* _node,int(*f)(void*,void*), void* _context)
{

}