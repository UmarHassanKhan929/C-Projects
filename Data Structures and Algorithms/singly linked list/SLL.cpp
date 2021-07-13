
#include <iostream>
using namespace std;

class NodeClass{
    public:
        int data; //part of node to hold data
        NodeClass *next; //part of node to hold address of next node
};

class SingleLinkedList{
    public:
        NodeClass *start; //holding address of start node
        NodeClass *last;  //holding address of last node
        NodeClass *currLoc; //holding address of current location
        NodeClass *predLoc; //holding address of predecessor of cuurent loc node

    SingleLinkedList(){ //creating a singly linked list (constructor)
        start = NULL;
        currLoc = NULL;
        predLoc = NULL;
    }

    bool IsEmpty(){// checks whether the list is empty or not. Returns true if empty and false otherwise
        return start == NULL;
    } 

    void InsertAtFront(int value){ // takes input from a user and inserts it at the front of a list    
        NodeClass *newNode = new NodeClass();
        newNode->data = value; //storing value in newNOde
        if(IsEmpty()){ //if empty, last is newnode
            last = newNode; 
        }
        else{ //list not empty, newnode next gets start address 
            newNode->next = start;
        }
        start = newNode; //start is newnode
    }

    void InsertAtEnd(int value){ // takes input from a user and inserts it at the tail end of a list
        NodeClass *newNode = new NodeClass();
        newNode -> data = value; //storing value
        if(IsEmpty()){ //if list is empty, start node gets nn address
            start = newNode;
        }
        else{ //if not empty, last node next ptr stores nn address.
            last -> next = newNode;
        }
        last = newNode; //last ptr has nn address
    } 

    void PrintList(){ //print the contents of list
        cout<<"bout to print list.."<<endl;
        NodeClass *temp = new NodeClass(); //storing current node in temp ptr
        if(!IsEmpty()){
            cout<<"Printing list"<<endl;
            int i = 1;
            temp = start; //initialize the temp
            while(temp != NULL){ //looping till temp is not null
                cout <<" Node: "<<i<<": "<<temp -> data<<" "<<endl;
                temp = temp -> next;
                ++i;
            }
        }
        else{
            cout<<"list is empty bruh..";
        }
    }

    void SearchLoc(int value){ //to search logical position of value to be inserted or deleted
        currLoc = start; //initializing with start
        predLoc = NULL; //predecessor of start is null
        if(IsEmpty()){ //if list is empty, remains same as initialized terms
            return;
        }
        while(currLoc != NULL && currLoc->data < value){ //if current location if not empty and current loc data is lower than that of given value, increment the locations of currloc and predloc
            predLoc = currLoc;
            currLoc=currLoc->next;
        }
        if(currLoc != NULL && currLoc->data != value){ //if cuurent loc has an adress and its data value is not same as given value, means current location is not found 
            currLoc = NULL;
        }
    }

    void InsertSorted(int value){ //logically puts value in the its order, no duplication allowed
        SearchLoc(value); //updates currLoc and predLoc to get logical position
        cout<<"inserting "<<value<<" at appropriate location."<<endl;
        if(currLoc != NULL){ //if currLoc is not null, means value already exists in list
            cout<<value<<" already exists hence khali wali"<<endl;
        }
        else{ // if currLoc is null, then..
            
            if(predLoc == NULL){ //if predloc and currLoc both null, means position is found and list is empty so value will be added to front of list 
                InsertAtFront(value);
            }
            else{ //if currLoc is NULL and predLoc is not NULL, then..
                if(predLoc == last){ //if predLoc has last node address, value will be inserted to the end
                    InsertAtEnd(value);
                }
                else{ //if somewhere in between list and logical position is found
                    NodeClass *newNode = new NodeClass();
                    newNode -> data = value;
                    newNode -> next = predLoc -> next;
                    predLoc -> next = newNode;
                }
            }
        }
    }


    void Delete(int value){  //tp delete value in list
        if(IsEmpty()){ //if list if empty, cant delete
            cout<<"list is already empty";
            return;
        }
        else{ //if list not empty
            cout<<"searching for "<<value<<endl;
            SearchLoc(value); //search for value
            if(currLoc != NULL){ //if value found
                if(predLoc == NULL){ //first node
                    if(currLoc == last){ //if only single node in whole list
                        start = NULL;
                        last = NULL;
                    }
                    else{ //if multiple nodes in a list
                        start = start -> next;
                    }
                    delete currLoc;
                }
                else{ //not the first node
                    if(currLoc == last){ //if last node
                        last = predLoc;
                    }
                    //updating and deleting
                    predLoc -> next = currLoc -> next;
                    delete currLoc;
                }
            }
            else{ //if value not found, then this is executed
                cout<<"value not found, deletion not possible.."<<endl;
            }
        }
        cout<<value<<" is deleted from list "<<endl; 
    }


    void DestroyList(){ //delete all the list
    cout<<"destroying list"<<endl;
        while(start != NULL){ //while list is not empty
            NodeClass *tempNode = start; //create a node ,same address as start/current
            start = start -> next; //jump to next node
            delete tempNode; //delete current node
        }
        last = NULL;
    }

    void RecursiveCall(NodeClass *nextN){  //function used in reverse print list
        if(nextN -> next == NULL){ //condition for recursion exit
            cout<<"Printing list in reverse "<<endl;
            cout<<" Node : "<<nextN -> data<<endl;
            return;
        }
        RecursiveCall(nextN -> next); //recursion
        cout<<" Node : "<<nextN -> data<<endl; //unstacking and printing
    }

    void PrintListInReverse(){ //prints the contents of list in reverse
        if(IsEmpty()){ //if empty, ignore
            cout<<"List is already empty"<<endl;
        }
        else{ //if not empty
            currLoc = start; //initialize with start 
            RecursiveCall(currLoc);  //function call
        } 
    }

    void DeleteOddValues(){ //function to delete odd values from list
        if(IsEmpty()){ //if empty, ignore
            cout<<"The list is empty.. bruhhhh"<<endl;
        }
        else{ //if not empty
            currLoc = start;
            predLoc = NULL;
            NodeClass *temp = new NodeClass();
            while(currLoc !=  NULL){
                if(!((currLoc -> data)%2 == 0)){
                    cout<<"deleting odd value "<<currLoc->data<<endl;
                    temp = currLoc;
                    currLoc = currLoc -> next;
                    if(predLoc == NULL){ //first node
                        if(currLoc == last){ //if only single node in whole list
                            start = NULL;
                            last = NULL;
                        }
                        else{ //if multiple nodes in a list
                            start = currLoc;
                        }
                    }
                    else{ //not the first node
                        if(currLoc == last){ //if last node
                            last = predLoc;
                        }
                        //updating and deleting
                        predLoc -> next = currLoc;
                    }
                    delete temp;
                }
                else{
                    cout<<"not odd value, hence skip "<<currLoc->data<<endl;
                    predLoc = currLoc;
                    currLoc = currLoc -> next; 
                }
            }
        }
    }

    void ReverseList(){ //function to reverse the linked list
        if(IsEmpty()){ //if list empty, ignore
            cout<<"List is empty bruhh, cant swing  de nodey nodes.."<<endl;
        }
        else{ //if list not empty
            currLoc = start; //current at start
            predLoc = NULL; //predecessor at null
            NodeClass *nextN = new NodeClass(); //nextN node placed next to current   
            while(currLoc != NULL){ //while current location is not null
                nextN = currLoc -> next; //nextN points to currents next
                currLoc -> next = predLoc; //currents next points to previous( hence revers the link)
                predLoc = currLoc; //previous is the current
                currLoc = nextN; //current is at same position at nextN node
            }
            start = predLoc; //ending node will be the first
        }
        cout<<"Reversing the current list"<<endl;       
    }

    void GroupEvenOdd(){ //fucntion used to group even and odd numbers
        NodeClass *temp = new NodeClass();
        NodeClass *lastOrig = last; //pointer to store original list last element
        currLoc = start;
        predLoc = NULL;
        if(IsEmpty()){ //to check if list is empty
            cout<<"list is empty"<<endl;
        }
        else{ //if list is not empty
            while(currLoc != lastOrig){
                if(!((currLoc->data)%2==0)){
                    cout<<"odd found, hence shift to end "<<currLoc->data<<endl;
                    temp = currLoc; //if value found, store it in temp
                    currLoc = currLoc -> next; //propogate to next
                    if(predLoc == NULL){ //first node
                        start = currLoc;
                    }
                    else{ //not the first node
                        predLoc -> next = currLoc;
                    }
                    temp->next = NULL;
                    last -> next = temp;
                    last = temp;
                }
                else{
                    cout<<"not odd value, hence skip "<<currLoc->data<<endl; 
                    predLoc = currLoc;
                    currLoc = currLoc -> next;
                }   
            }
        }
    }
    
    void SwapNodes(int n1, int n2){ //function to swap 2 values at different nodes
        predLoc=NULL,currLoc=start; //to track n1 location
        NodeClass *predLoc2=NULL,*currLoc2=start,*temp=NULL; //to track n2 location and temp ptr
        if(start == NULL){ //to check if list is empty
            cout<<"list is empty"<<endl;
            return;
        }
        if(n1==n2){ //to check if numbers entered are same
            cout<<"both numbers entered are same"<<endl;
            return;
        }
        while(currLoc != NULL && currLoc->data != n1){ //track n1 location
            predLoc = currLoc;
            currLoc = currLoc->next;
        }
        while(currLoc2 != NULL && currLoc2->data != n2){ //track n2 location
            predLoc2 = currLoc2;
            currLoc2 = currLoc2->next;
        }
        if (currLoc==NULL || currLoc2==NULL){
			cout << "value/s not found" << endl;
			return;
		}
        else if(currLoc!=NULL && currLoc2!=NULL){ //if data values are not null

            if(currLoc->next==NULL){ //if last node
                last = currLoc2;
            }
            if(predLoc!=NULL){ //if not first node, then adjust links
                predLoc->next=currLoc2;
            }
            else{ //if first node
                start = currLoc2;
            }

            if(currLoc2->next==NULL){ //if last node
                last = currLoc;
            }
            if(predLoc2!=NULL){ //if not first node
                predLoc2->next=currLoc;
            }
            else{ //if first node
                start = currLoc;
            }

        }
        //swapping nodes next ptr field with temp pointer
        temp = currLoc->next;
        currLoc->next = currLoc2->next;
        currLoc2->next=temp;
    }
	
	NodeClass* ReverseKNodes(NodeClass* &start, int k){
		NodeClass* prev=NULL;
		NodeClass* current=start;
		NodeClass* next;
		int count=0;
		
		while(current!=NULL && count<k){
			next=current->next;
			current->next=prev;
			prev=current;
			current=next;
			count++;
		}
		
		if(next!=NULL){
			start->next = ReverseKNodes(next,k);
		}
		
		return prev;
	}
};

int main(void){
    SingleLinkedList ssl;
    ssl.InsertSorted(1);
    ssl.InsertAtEnd(75);
    ssl.InsertAtEnd(98);
    ssl.InsertAtEnd(54);
    ssl.InsertAtEnd(23);
    ssl.InsertAtEnd(97);
    ssl.InsertAtEnd(69);
    ssl.InsertAtEnd(50);
    ssl.PrintList();
    ssl.SwapNodes(1,50);
    ssl.PrintList();
    ssl.InsertAtEnd(11);
    ssl.PrintList();

}
