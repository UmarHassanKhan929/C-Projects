/*
	created by 
	
	Umar Hassan Khan
	288929
	BSCS 9B

	DSA LAB-3 part A doubly linked list


*/
#include <iostream>
using namespace std;

class NodeClass{
public:
	int data; //to hold data
	NodeClass *next; //hold next ptr field address
	NodeClass *prev; //hold prev ptr field adrress
};

class DoubleLinkedList{
public:
	NodeClass *start; //start ptr of double linked list
	NodeClass *last; //last ptr of the double linked list
	NodeClass *currLoc; //to track current location
	NodeClass *predLoc; //to track location of prev ptr to the current ptr

	DoubleLinkedList(){ //connstructor of the double linked list
		start = NULL, last = NULL, currLoc = NULL, predLoc = NULL;
	}

	bool isEmpty(){ //to check if the list empty
		return last == NULL;
	}

	void InsertAtFront(int value){
		NodeClass *newNode = new NodeClass(); //creating new node
		newNode->data = value; //entring data in node
		cout << "Inserting " << value << " in the front of list" << endl;

		if (isEmpty()){ //if list is empty, update both start and last
			start = newNode;
			last = newNode;
		}
		else{ //if list not empty, add in the front
			newNode->next = start;    
			start->prev = newNode;
			start = newNode;
		}
	}

	void InsertAtEnd(int value){ //function to add value in end
		NodeClass *newNode = new NodeClass(); //creating new node
		newNode->data = value; //entring data in node
		cout << "Inserting " << value << " in the end of list" << endl;
		if (isEmpty()){ //if list is empty, update both start and last
			start = newNode;
			last = newNode;
		}
		else{ //if list not empty
			last->next = newNode;
			newNode->prev = last;
			last = newNode;
		}
	}

	void PrintList(){
		cout << "bout to print list...." << endl;
		NodeClass *temp = new NodeClass();
		if (!isEmpty()){
			cout << "Printing list now.." << endl;
			int i = 1;
			temp = start;
			while (temp!=NULL){
				cout << " Node: " << i << ": " << temp->data << endl;
				temp = temp->next;
				++i;
			}
		}
		else{
			cout << "List is empty bruhh........";
		}
	}

	void Search(int value){ // to search logical position of value
		currLoc = start;
		predLoc = NULL;

		//suppose we are searching in sorted list
		while (currLoc != NULL && currLoc->data < value){
			predLoc = currLoc;
			currLoc = currLoc->next;
		}

		//if value not found in list
		if (currLoc != NULL && currLoc->data != value){
			currLoc = NULL;
		}
	}

	void InsertSorted(int value){ //to insert value at its logical position
		Search(value);
		if (currLoc != NULL){ //if value already exist
			cout << "Value already exist, hence no bueno.. Adios."<<endl;
		}
		else{ //if currloc is null, meaning value not exist and its logical position found
			
			if (predLoc == NULL){ // currloc and predloc is both null, hence first node
				InsertAtFront(value);
			}
			else{ // if not the fist  node
				if (predLoc == last){// if last node
					InsertAtEnd(value);
				}
				else{ //if somewhere in between
					cout << "putting "<<value<< " at its logical positon" << endl;

					NodeClass *newNode = new NodeClass();
					newNode->data = value;
					newNode->next = predLoc->next;
					newNode->prev = predLoc;
					predLoc->next->prev = newNode;
					predLoc->next = newNode;

				}
			}
		}
	}

	void DeleteFront(){ //deletes the front node of list 
		if (isEmpty()){
			cout << "sorry bruv, list is empty" << endl;
		}
		else{
			cout << "Deleting first node" << endl;
			NodeClass *temp = start;
			start = start->next;
			start->prev = NULL;
			delete temp;
		}

	}

	void DeleteLast(){ //deletes the last node of list 
		if (isEmpty()){
			cout << "sorry bruv, list is empty" << endl;
		}
		else{
			cout << "Deleting last node" << endl;
			NodeClass *temp = last;
			last = last -> prev;
			last -> next = NULL;
			delete temp;
		}
	}

	void Delete(int value){ //deleted the user given value
		Search(value);
		if (isEmpty()){ //if list is empty
			cout << "sorry bruv, list is empty" << endl;
		}
		else{ //if list is not empty
			if (currLoc != NULL){ //if value found 
				if (predLoc == NULL){ //if first value
					if (currLoc == last){ //if only one value i.e. first and last
						start = NULL;
						last = NULL;
						delete currLoc;
					}
					else{ //if multiple values and first to delete
						DeleteFront();
					}
				}
				else{ //not the first node
					if ( currLoc == last){ //if last value
						DeleteLast();
					}
					else{ //if somewhere in between
						predLoc->next = currLoc->next;
						currLoc->next->prev = predLoc;
						delete currLoc;
					}
				}
				cout << "value " << value << " deleted " << endl;

			}
			else{
				cout << "value not found, hence deletion not possible" << endl;
			}
		}
	}

	void DestroyList(){
		cout << "Destroying the list...  " << endl;
		
		while (start != NULL){
			NodeClass *temp = start;
			 start = start->next;
			delete temp;
		}
		last = NULL;
	}

	void ReverseList(){
		if (isEmpty()){
			cout << "sorry bruv, list empty" << endl;
		}
		else{ //if list is not empty 
			currLoc = start;
			predLoc = NULL;
			NodeClass *nextNode = new NodeClass();
			last = start;
			while (currLoc!= NULL){
				nextNode = currLoc->next;
				currLoc->next = predLoc;
				currLoc->prev = nextNode;
				predLoc = currLoc;
				currLoc = nextNode;
			}
			start = predLoc;
		}
	}

	void SwapNodes(int n1, int n2){ //function to swap 2 values at different nodes

        predLoc=NULL,currLoc=start; //to track location

        NodeClass *predLoc2=NULL,*currLoc2=start,*temp=NULL; //to track n2 location and temp ptr
        if(isEmpty()){ //to check if list is empty
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
				currLoc2->prev = predLoc;
            }
            if(predLoc==NULL){ //if first node
                start = currLoc2;
				currLoc2->prev = NULL;
            }

            if(currLoc2->next==NULL){ //if last node
                last = currLoc;
				

            }
            if(predLoc2!=NULL){ //if not first node
                predLoc2->next=currLoc;
				currLoc->prev = predLoc2;
            }
            if(predLoc2==NULL){ //if first node
                start = currLoc;
				currLoc->prev = NULL;
            }

        }
        //swapping nodes next ptr field with temp pointer
        temp = currLoc->next;
        currLoc->next = currLoc2->next;
		currLoc2->next->prev =currLoc;
        currLoc2->next=temp;
		temp-> prev = currLoc2;
		currLoc->prev=temp;
		
    }

	void GroupEvenOdd(){ //fucntion used to group even and odd numbers
        NodeClass *temp = new NodeClass();
        NodeClass *lastOrig = last; //pointer to store original list last element
        currLoc = start;
        predLoc = NULL;
        if(isEmpty()){ //to check if list is empty
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
						start -> prev = NULL;
                    }
                    else{ //not the first node
                        predLoc -> next = currLoc;
						currLoc -> prev = predLoc;
                    }
                    temp->next = NULL;
                    last -> next = temp;
					temp -> prev = last;
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

	void PrintReverseList(){
		if(isEmpty()){
			cout<<"empty list bruv";
		}
		else{
			currLoc = last;
			cout<<"printing in reverse"<<endl;
			do{
				cout<<" Node: "<<currLoc->data<<endl;
				currLoc = currLoc-> prev;
			}while(currLoc!=NULL);
			
		}
	}

};

int main(void){
	DoubleLinkedList dll;
	dll.InsertSorted(1);
	dll.InsertSorted(5);
	dll.InsertSorted(2);
	dll.InsertSorted(4);
	dll.InsertSorted(7);
	dll.InsertSorted(3);
	dll.InsertSorted(9);
    dll.InsertSorted(8);
	dll.InsertSorted(6);	
	dll.PrintList();
	
	
}

