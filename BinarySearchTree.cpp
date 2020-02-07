#include <iostream>
#include <cstddef>

//Micah Burkhardt

//CECS 503-50

//09072019

using std::cout;
using std::endl;

class Node {
    int value;
public:
    Node* left;       // left child
    Node* right;      // right child
    Node* p;          // parent
    Node(int data) {
        value = data;
        left = NULL;
        right = NULL;
        p  = NULL;
    }
    ~Node()
	{}
	
    int d()//Method used to access value stored in private member
	{
        return value;
    }
    void print()
	{
        std::cout << value << std::endl;
    }
    
};

//Function Prototypes
void insert(Node *, Node *);
void delete_node(int, Node *);
Node *search(int, Node *);
Node *FindMin(Node *);


int main(int argc, const char * argv[])
{
//Creating Tree
	cout<<"Created root node\n";
	Node *root = NULL;
	root = new Node(2);
	
	
	int iArray[11] = {1,4,5,9,3,6,7,10,12,11}; //Storing requested values
	int i;
	for(i = 0; i< 10; i++)//create and insert nodes with values from array
	{
    	Node *nPtr = NULL;
    	nPtr = new Node(iArray[i]);
		//cout<<"\nCreated node: "<<i<<endl;
		insert(nPtr, root);
	}

//Searching tree tree before deletion
	cout<<"\nSearch:";
	search(12, root);
	search(4, root);
	
//Delete 4 and 9
	cout<<"\nDelete:";
	delete_node(4,root);
	delete_node(9,root);

//Searching tree tree before deletion
	cout<<"\nFinal Search";
	search(12, root);
	search(4, root);//not in tree as it was deleted
	
	return 0;
}

void insert(Node *insert_node, Node *tree_root)
{
	if(insert_node->d() < tree_root->d()) //Move left
	{
		if(tree_root->left != NULL)
		{
			insert(insert_node,tree_root->left);
		}
		else
		{
			tree_root->left = insert_node;
			insert_node->p = tree_root;
			cout<<"\nNode "<<insert_node->d()<<" Placed LEFT of "<<tree_root->d()<<endl;			
		}
	}
	else if(insert_node->d() > tree_root->d()) //Move right
	{
		if(tree_root->right != NULL)
		{
			insert(insert_node,tree_root->right);
		}
		else
		{
			tree_root->right = insert_node;
			insert_node->p = tree_root;
			cout<<"\nNode "<<insert_node->d()<<" Placed RIGHT of "<<tree_root->d()<<endl;
		}
	}	
	else
	{} //duplicate
}

void delete_node(int value, Node *tree_root)
{
	//find the node that needs removed
	Node *remove_node = NULL;
	remove_node = search(value, tree_root);
	
	if(remove_node == NULL)//Value is not found
	{
		cout<<"A Node with value "<<value<<"does not exist"<<endl;
	}
	else
	{
		if(remove_node->left == NULL && remove_node->right == NULL)//Node is a leaf
		{
			if(remove_node->p->left->d() == remove_node->d())//checking to see where if the node is right or left of parent
			{
				remove_node->p->left = NULL;
				delete remove_node;
				cout<<"Node deleted";
			}
			else if(remove_node->p->right->d() == remove_node->d())
			{
				remove_node->p->right = NULL;
				
				delete remove_node;
				cout<<"Node deleted";
			}
			else
			{
				cout<<"Your if statements failed";
			}
		}
		else if(remove_node->right != NULL || remove_node->left != NULL)//Node has children
		{
			Node *NodeMin = NULL;
			//find min of right
			NodeMin = FindMin(remove_node->right);
			
			//Point remove node's parent to minimum of the right
			if(remove_node->p->left->d() == remove_node->d())//Which location is removed node stored in
			{
				remove_node->p->left = NodeMin;
				NodeMin->left = remove_node->left;
				cout<<remove_node->left->d()<< " Inserted to the left of "<<NodeMin->d()<<endl;
				delete remove_node;
				cout<<"Node deleted\n";
			}
			else if(remove_node->p->right->d() == remove_node->d())
			{
				remove_node->p->right = NodeMin;
				NodeMin->left = remove_node->left;
				cout<<remove_node->left->d()<< " Inserted to the left of "<<NodeMin->d()<<endl;
				delete remove_node;
				cout<<"Node deleted\n";
			}
		}
	}
}

Node *search(int value, Node *tree_root)
{
	if(value == tree_root->d())//Node found
	{
		cout<<"\nValue "<<value<<" found"<<endl;
		//return pointer to equal node
		return tree_root;
	}
	else if(value < tree_root->d() && tree_root->left != NULL)//search left node
	{
		search(value, tree_root->left);
	}
	else if(value > tree_root->d() && tree_root->right != NULL)//search right node
	{
		search(value, tree_root->right);
	}
	else
	{
		cout<<"Value "<<value<<" not found"<<endl;
		return NULL;
	}
}

Node *FindMin(Node *tree_root)
{
	Node *NTmp = tree_root;
	
	tree_root = tree_root->right;
	if(tree_root == NULL)
	{
		return NTmp;
	}
	while(tree_root != NULL)
	{
		if(NTmp->d() < tree_root->d())
		{
			tree_root = tree_root->right;
		}
		else
		{
			NTmp = tree_root->right;
		}
	}
	return NTmp;
	
}
