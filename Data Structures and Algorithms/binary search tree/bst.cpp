#include <iostream>
using namespace std;

template<typename T>
class BST_Node{
public:
	T data; 
	BST_Node<T> *leftChild;
	BST_Node<T> *rightChild;
};

template<typename T>
class BinarySearchTree{
public:
	BST_Node<T> *root;
	BST_Node<T> *loc;
	BST_Node<T> *ploc;

	int leavesCount=0;
	int leftChildNodes=0;
	int rightChildNodes=0;
	int doubleChildrenNodes=0;

	bool IsEmpty(){
		return root==NULL;
	}

	BinarySearchTree(){
		root=NULL;
		loc=NULL;
		ploc=NULL;
	}
	//search for logical position wihtout duplication
	void Search(T value){
		loc=root;
		ploc=NULL;

		while(loc!=NULL && loc->data != value){
			if(value < loc->data){ //less than for non duplication
				ploc=loc;
				loc=loc->leftChild;
			}else{
				ploc=loc;
				loc=loc->rightChild;
			}
		}
	}
	
	void InsertWithoutDuplication(T value){
		Search(value);
		//if loc == NULL means value not found
		if(loc==NULL){
			BST_Node<T> *newNode = new BST_Node<T>();
			newNode->data=value;
			if(ploc!=NULL){ //if ploc not null then values can be inserted
				if(value < ploc->data){
					ploc->leftChild=newNode;
				}else{
					ploc->rightChild=newNode;
				}
			}
			else{//if not empty list
				root = newNode;
			}
		}else{ //loc is found hence duplication
			cout<<"Duplication not allowed"<<endl;
		}
	} 

	void InsertWithDuplication(T value){
		BST_Node<T> *newNode = new BST_Node<T>();
		newNode->data = value;
		//if list is not empty
		if(!IsEmpty()){
			ploc=NULL;
			loc=root;

			while(loc!=NULL){
				if(value<=loc->data){
					ploc=loc;
					loc=loc->leftChild;
				}else{
					ploc=loc;
					loc=loc->rightChild;
				}
			}
			if(value<=ploc->data){
				ploc->leftChild=newNode;
			}else{
				ploc->rightChild=newNode;
			}

		}else{//if list is empty
			root = newNode;
		}
	}

	void PreOrderTraversal(BST_Node<T> *treeNode){
		if(treeNode!=NULL){
			cout<<treeNode->data<<" ";
			PreOrderTraversal(treeNode->leftChild);
			PreOrderTraversal(treeNode->rightChild);
		}
	}
	void InOrderTraversal(BST_Node<T> *treeNode){
		if(treeNode!=NULL){
			InOrderTraversal(treeNode->leftChild);
			cout<<treeNode->data<<" ";
			InOrderTraversal(treeNode->rightChild);
		}
	}
	void ReverseInOrderTraversal(BST_Node<T> *treeNode){
		if(treeNode!=NULL){
			ReverseInOrderTraversal(treeNode->rightChild);
			cout<<treeNode->data<<" ";
			ReverseInOrderTraversal(treeNode->leftChild);
			
		}
	}
	void PostOrderTraversal(BST_Node<T> *treeNode){
		if(treeNode!=NULL){
			PostOrderTraversal(treeNode->leftChild);
			PostOrderTraversal(treeNode->rightChild);
			cout<<treeNode->data<<" ";
		}
	}

	void PrintSmallestValue(BST_Node<T> *treeNode){
		while(treeNode->leftChild!=NULL){
			treeNode=treeNode->leftChild;
		}
		cout<<"Smallest value is "<<treeNode->data<<endl;

	}
	void PrintLargestValue(BST_Node<T> *treeNode){
		while(treeNode->rightChild!=NULL){
			treeNode=treeNode->rightChild;
		}
		cout<<"Largest value is "<<treeNode->data<<endl;
	}

	int HeightOfTree(BST_Node<T> *treeNode){
		if(treeNode == NULL){
            return -1;
        }else{
            return 1+max(HeightOfTree(treeNode->leftChild),HeightOfTree(treeNode->rightChild));
        }
	}
    int DepthOfAllNodes(BST_Node<T> *treeNode,int depthCount){
    	if(treeNode!=NULL){
    		//int d=1+depthCount;
    		cout<<"Node: "<<treeNode->data<<" has depth "<<depthCount<<endl;
    		int depthLeftNode = DepthOfAllNodes(treeNode->leftChild,1+depthCount);
    		int depthRightNode = DepthOfAllNodes(treeNode->rightChild,1+depthCount);
    		return max(depthLeftNode,depthRightNode);
    	}else{
    		return depthCount-1;
    	}
    }
    int DepthOfNode(BST_Node<T> *treeNode,int depthCount,T cmp){
    	if(treeNode!=NULL){
			if(treeNode->data == cmp){
    			return depthCount;
    		}else{
    			int depthLeftNode = DepthOfNode(treeNode->leftChild,1+depthCount,cmp);
    			int depthRightNode = DepthOfNode(treeNode->rightChild,1+depthCount,cmp);
    		}
    	}
    	
    }

    void InvertBinaryTree(BST_Node<T> *treeNode){
    	if(treeNode!=NULL){
    		BST_Node<T> *leftChild = treeNode->leftChild;
    		BST_Node<T> *rightChild = treeNode->rightChild;
    		treeNode->leftChild=rightChild;
    		treeNode->rightChild=leftChild;
    		InvertBinaryTree(treeNode->leftChild);
    		InvertBinaryTree(treeNode->rightChild);
    	}
    }

    void DeleteNode(T value){
    	Search(value);
		cout<<"Deleting "<<value<<endl;
    	if(loc!=NULL){
    		//deleting leaf node

    		if(loc->leftChild==NULL && loc->rightChild==NULL){
    			
				if(ploc==NULL){
    				root=NULL;
    			}else if(ploc->leftChild==loc){
    				ploc->leftChild=NULL;
    			}else{
    				ploc->rightChild=NULL;
    			}
    			delete loc;
				return;
    		}

    		//deleting a node with only one sub tree
    		//from left sub tree
    		if(loc->leftChild!=NULL && loc->rightChild==NULL){
    			if(ploc==NULL){
    				root = loc->leftChild;
					loc->leftChild=NULL;
    			}else if(loc==ploc->leftChild){
    				ploc->leftChild=loc->leftChild;
					loc->leftChild=NULL;
    			}else{
					ploc->rightChild=loc->leftChild;
					loc->leftChild=NULL;
				}
    			delete loc;
				return;
    		}

    		//deleting a node with only one sub tree
    		//from right sub tree
    		if(loc->leftChild==NULL && loc->rightChild!=NULL){
    			if(ploc==NULL){
    				root = loc->rightChild;
					loc->rightChild=NULL;
    			}else if(loc==ploc->leftChild){
    				ploc->leftChild=loc->rightChild;
					loc->rightChild=NULL;
				}else{
					ploc->rightChild=loc->rightChild;
					loc->rightChild=NULL;
				}
    			delete loc;
				return;
    		}

    		//deleting a node with 2 children
    		if(loc->leftChild!=NULL && loc->rightChild!=NULL){

    			BST_Node<T> *ploc2=loc;
    			BST_Node<T> *loc2=loc->leftChild;

    			//finding predecessor of loc
    			while(loc2!=NULL && loc2->rightChild!=NULL){
    				ploc2=loc2;
    				loc2=loc2->rightChild;
    			}

    			//bringing replacement node on its new postion
    			if(loc->leftChild==loc2){
    				loc->leftChild=loc2->leftChild;
    			}else if(loc2->leftChild!=NULL){
    				ploc2->rightChild=loc2->leftChild;
    			}else{
    				ploc2->rightChild=NULL;
    			}

    			//updating links of replacement node
    			loc2->leftChild=loc->leftChild;
    			loc2->rightChild=loc->rightChild;

    			if(ploc==NULL){
    				root=loc2;
    			}else if(ploc->rightChild==loc){
    				ploc->rightChild=loc2;
    			}else{
    				ploc->leftChild=loc2;
    			}

    			delete loc;
				return;

    		}

    	}else{
    		cout<<"Value doesnt exists.."<<endl;
    	}

    }

    void DestroyTree(BST_Node<T> *treeNode){
    	if(treeNode!=NULL){
    		DestroyTree(treeNode->leftChild);
    		DestroyTree(treeNode->rightChild);
    		delete treeNode;
    	}
    	root = NULL;
    }

    void PrintLeafNodes(BST_Node<T> *treeNode){
    	if(treeNode!=NULL){
			if(treeNode->leftChild==NULL && treeNode->rightChild==NULL){
    			cout<<"Leaf node has data "<<treeNode->data<<endl;
    		}else{
    			PrintLeafNodes(treeNode->leftChild);
    			PrintLeafNodes(treeNode->rightChild);	
    		}
    	}
    }

    void DeleteLeafNodes(BST_Node<T> *parent,BST_Node<T> *treeNode){
    	if(treeNode!=NULL){
			if(treeNode->leftChild==NULL && treeNode->rightChild==NULL){
				if(parent!=NULL){
					if(parent->leftChild==treeNode){
						parent->leftChild=NULL;
					}else if(parent->rightChild==treeNode){
						parent->rightChild=NULL;
					}
				}else{
					root = NULL;
				}
				delete treeNode;

    		}else{
    			DeleteLeafNodes(treeNode,treeNode->leftChild);
    			DeleteLeafNodes(treeNode,treeNode->rightChild);	
			}
    	}
    }

    
    void CountNodes(BST_Node<T> *treeNode){
		if(treeNode!=NULL){
			if(treeNode->leftChild==NULL && treeNode->rightChild==NULL){
				++leavesCount;
    		}
			if(treeNode->leftChild!=NULL && treeNode->rightChild==NULL){
				++leftChildNodes;
    		}
			if(treeNode->leftChild==NULL && treeNode->rightChild!=NULL){
				++rightChildNodes;
    		}
			if(treeNode->leftChild!=NULL && treeNode->rightChild!=NULL){
				++doubleChildrenNodes;
    		}
    		CountNodes(treeNode->leftChild);
    		CountNodes(treeNode->rightChild);	
    	}
    }

   void CountNodesAndStuff(){
	    cout<<"Counting stuff.."<<endl;
		leavesCount=0;
		leftChildNodes=0;
		rightChildNodes=0;
		doubleChildrenNodes=0;
		CountNodes(root);
		cout<<"Leaf nodes : "<<leavesCount<<", left subtree nodes: "<<leftChildNodes<<", right subtree nodes: "<<rightChildNodes<<", Double children nodes: "<<doubleChildrenNodes<<endl;
	}

	void DeleteLeftSubTreeNode(BST_Node<T> *treeNode,BST_Node<T> *parent){
		
		if(treeNode!=NULL){	
			
			if(treeNode->leftChild != NULL && treeNode->rightChild == NULL){
				loc=treeNode;
				treeNode=loc->leftChild;
				if(parent==NULL){
					root=loc->leftChild;
				}else if(loc==parent->leftChild){
					parent->leftChild=loc->leftChild;
				}else{
					parent->rightChild=loc->leftChild;
				}
				delete loc;
				DeleteLeftSubTreeNode(treeNode,parent);
				
			}else{
	
			DeleteLeftSubTreeNode(treeNode->leftChild,treeNode);
    		DeleteLeftSubTreeNode(treeNode->rightChild,treeNode);
						
			}

		}

	}
};

int main(void){
	BinarySearchTree<int> tree;	
	tree.InsertWithDuplication(12);
	tree.InsertWithDuplication(1);
	tree.InsertWithDuplication(0);
	tree.InsertWithDuplication(-1);
	tree.InsertWithDuplication(-2);
	//tree.InsertWithDuplication(5);
	//tree.InsertWithDuplication(14);
	// tree.InsertWithDuplication('j');
	// tree.InsertWithDuplication('c');
	// tree.InsertWithDuplication('b');	
	// tree.InsertWithDuplication('d');
	// //tree.InsertWithDuplication('f');
	
	
	cout<<"Is tree empty ? ";
	tree.IsEmpty()?cout<<"Yems tis empty.\n":cout<<"Nopsy tis filled\n";
	
	cout<<"Reverse InOrder traversal "<<endl;
	tree.ReverseInOrderTraversal(tree.root);
	cout<<endl;
	
	cout<<"In order traversal"<<endl;
	tree.InOrderTraversal(tree.root);
	
	cout<<"\nPre order traversal"<<endl;
	tree.PreOrderTraversal(tree.root);
	
	cout<<"\nPost order traversal"<<endl;
	tree.PostOrderTraversal(tree.root);
	cout<<endl;
	
	cout<<endl;
	tree.PrintSmallestValue(tree.root);
	
	cout<<endl;
	tree.PrintLargestValue(tree.root);
    
	cout<<endl;
    
	cout<<"Height of tree is: "<<tree.HeightOfTree(tree.root)<<endl;
    
	cout<<"Depth of tree is: "<<tree.DepthOfAllNodes(tree.root,0)<<endl;


    cout<<"displaying leaf nodes"<<endl;
    tree.PrintLeafNodes(tree.root);

	// //task 4 in lab partB
	// tree.CountNodesAndStuff();
    
	// cout<<"deleting leaf nodes"<<endl;
    // tree.DeleteLeafNodes(NULL,tree.root);

    // cout<<"\nDeleting a node"<<endl;
    // tree.DeleteNode('c');

	cout<<"Deleting left sub tree only node"<<endl;
	tree.DeleteLeftSubTreeNode(tree.root,NULL);

	//tree.InsertWithDuplication(3);
	
	cout<<"\nPost order traversal"<<endl;
	tree.PostOrderTraversal(tree.root);
	cout<<endl;	

	cout<<"Is tree empty ? ";
	tree.IsEmpty()?cout<<"Yems tis empty.\n":cout<<"Nopsy tis filled\n";
	

}