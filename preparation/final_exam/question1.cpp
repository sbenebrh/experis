#include <stddef.h>


namespace preparation
{


// in the question it is important to understand the meaning of cycling list because we never get next node = NULL and we can apply this algorithm
typedef struct  Node
{
    Node* m_next;
    int * m_data;
};



static int deleteNext(Node* Iter);

int removeIt(Node* Iter)
{
    if(NULL == Iter)
    {
        return -1;
    }
    Iter -> m_data = Iter -> m_next -> m_data; // copy the next one to the present

    return deleteNext(Iter);

}

/************************************************************/
static int deleteNext(Node* Iter)
{
    //dont need to check null :already check it in main function

    Iter -> m_next = Iter -> m_next -> m_next;
    return 0;
}

}
