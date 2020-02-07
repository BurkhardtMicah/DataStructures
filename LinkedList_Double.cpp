#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;




/* definition of the list node class */
class Node
{
    friend class LinkedList;
private:
    int value; 
    Node *pNext;
    Node *pPrev;
    
public:
    /* Constructors with No Arguments */
    Node(void)
    : pNext(NULL), pPrev(NULL)
    { }
    
    /* Constructors with a given value */
    Node(int val)
    : value(val), pNext(NULL), pPrev(NULL)
    { }
    
    /* Constructors with a given value and a link of the next node */
    Node(int val, Node* previous, Node* next)
    : value(val), pPrev(previous), pNext(next)
    {}
    
    /* Getters */
    int getValue(void)
    { return value; }
    
    Node* getNext(void)
    { return pNext; }
    
    Node* getPrevious(void)
    { return pPrev; }    
};

/* definition of the linked list class */
class LinkedList
{
private:
    /* pointer of head node */
    Node *pHead;
    /* pointer of tail node */
    Node *pTail;
    
public:
    /* Constructors with No Arguments */
    LinkedList(void);
    /* Constructors with a given value of a list node */
    LinkedList(int val);
    /* Destructor */
    ~LinkedList(void);
    
    /* Traversing the list and printing the value of each node */
    void traverse_and_print();
	void traverse_and_printBackwards();
	
	
	void push_back(int val);
};

LinkedList::LinkedList()
{
    /* Initialize the head and tail node */
    pHead = pTail = NULL;
}

LinkedList::LinkedList(int val)
{
    /* Create a new node, acting as both the head and tail node */
    pHead = new Node(val);
    pTail = pHead;
}

LinkedList::~LinkedList()
{
    
}

void LinkedList::traverse_and_print()
{
    Node *p = pHead;
    
    /* The list is empty? */
    if (pHead == NULL) {
        cout << "The list is empty" << endl;
        return;
    }
    
    cout << "LinkedList: ";
    /* A basic way of traversing a linked list */
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        cout << p->value;
        /* The pointer moves along to the next one */
        p = p->pNext;
    }
    cout << endl;
}


void LinkedList::traverse_and_printBackwards()
{
    Node *p = pTail;
    
    /* The list is empty? */
    if (pHead == NULL) {
        cout << "The list is empty" << endl;
        return;
    }
    
    cout << "LinkedList: ";
    
    while(p != NULL)
    {
    	cout << p->value;
    	
    	p = p->pPrev;
	}
    
    
    cout << endl;
}

//#####################################################################
/*Adds a new node to the end of the current list*/
void LinkedList::push_back(int val){
	/*Your code here*/
	
	if(this->pHead != 0)//If list is not empty
	{
		Node *currNode = this->pTail;
	
		currNode->pNext = this->pTail = new Node(val,currNode,NULL);
	}
	else
	{
		this->pHead = this->pTail = new Node(val);	
	}
}
//#####################################################################

int main(int argc, const char * argv[])
{
    /* Create an empty list */
    LinkedList list1;
    cout << "Created an empty list named list1." << endl;
    /* output the result */
    cout << "list1:" << endl;
    list1.traverse_and_print();
    
    /* Create a list with only one node */
    LinkedList list2(10);
    cout << "Created a list named list2 with only one node." << endl;
    /* output the result */
    cout << "list2:" << endl;
    list2.traverse_and_print();	
	
	//for testing pushback on a non-empty list
	for (int i = 0 ; i < 10; i++){
		list2.push_back(i);
	}
	cout<<"\nPushback f->b traversal List2"<<endl;
	list2.traverse_and_print();
	
	cout<<"\nPushback b->f traversal List2"<<endl;
	list2.traverse_and_printBackwards();
	
	

	//for testing pushback on an originally empty list
	for (int i = 0 ; i < 10; i++){
		list1.push_back(i);
	}
	cout<<"\nPushback f->b traversal List1"<<endl;
	list1.traverse_and_print();	
	
	cout<<"\nPushback b->f traversal List1"<<endl;
	list1.traverse_and_printBackwards();
    return 0;
}

