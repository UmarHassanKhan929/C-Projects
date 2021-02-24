/* 
    CREATED BY
    NAME:  UMAR HASSAN KHAN
    CMS: 288929
    CLASS: BSCS 9B

    DSA LAB 3 part 2  CIRCULAR  LINKED LIST

*/


#include <iostream>
using namespace std;

class NodeClass{
    public:
        int data; //part of node to hold data
        NodeClass *next; //part of node to hold address of next node
};

class CircularLinkedList{
    public:
        NodeClass *last;  //holding address of last node
        NodeClass *currLoc; //holding address of current location
        NodeClass *predLoc; //holding address of predecessor of cuurent loc node

    CircularLinkedList(){ //creating a circular linked list (constructor)
        last = NULL;
        currLoc = NULL;
        predLoc = NULL;
    }

    bool IsEmpty(){// checks whether the list is empty or not. Returns true if empty and false otherwise
        return last == NULL;
    } 

    void InsertAtFront(int value){ // takes input from a user and inserts it at the front of a list    
        NodeClass *newNode = new NodeClass();
        newNode->data = value; //storing value in newNOde
        if(IsEmpty()){ //if empty, last is newnode
            newNode->next=newNode;
            last = newNode; 
        }
        else{ //list not empty, newnode next gets start address 
            newNode->next = last->next;
            last->next = newNode;
        }
    }

    void InsertAtEnd(int value){ // takes input from a user and inserts it at the tail end of a list
        NodeClass *newNode = new NodeClass();
        newNode -> data = value; //storing value
        if(IsEmpty()){ //if list is empty, start node gets nn address
            newNode->next = newNode;
            last = newNode;
        }
        else{ //if not empty, last node next ptr stores nn address.
            newNode->next = last->next;
            last->next = newNode;
            last = newNode;
        }
    } 

    void PrintList(){ //print the contents of list
        cout<<"bout to print list.."<<endl;
        if(!IsEmpty()){
            cout<<"Printing list"<<endl;
            NodeClass *temp = last->next; //initialize the temp
            do{ //looping till temp is not next to last
                cout <<" Node: "<<temp -> data<<" "<<endl;
                temp = temp -> next;
            }while(temp != last->next);
        }
        else{
            cout<<"list is empty bruh..";
        }
    }

    void SearchLoc(int value){ //to search logical position of value to be inserted or deleted
    //supposing list is sorted
        currLoc = NULL;
        predLoc = NULL;

        if(IsEmpty()){ //if list is empty, remains same as initialized terms
            return;
        }
        currLoc = last->next; 
        predLoc = last; 
        while(currLoc != last && currLoc->data < value){ //if current location if not empty and current loc data is lower than that of given value, increment the locations of currloc and predloc
            predLoc = currLoc;
            currLoc=currLoc->next;
        }
        if(currLoc->data != value){ //if cuurent loc has an adress and its data value is not same as given value, means current location is not found 
            currLoc = NULL;
            if(value>last->data){
                predLoc=last;
            }
        }
    }

    void InsertSorted(int value){ //logically puts value in the its order, no duplication allowed
        SearchLoc(value); //updates currLoc and predLoc to get logical position
        cout<<"inserting "<<value<<" at appropriate location."<<endl;
        if(currLoc != NULL){ //if currLoc is not null, means value already exists in list
            cout<<value<<" already exists hence khali wali"<<endl;
        }
        else{ // if currLoc is null, then..
            
            if(IsEmpty()){ //if predloc and currLoc both null, means position is found and list is empty so value will be added to front of list 
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


    void Delete(int value){  //to delete value in list
        if(IsEmpty()){ //if list if empty, cant delete
            cout<<"list is already empty";
            return;
        }
        else{ //if list not empty
            cout<<"searching for "<<value<<endl;
            SearchLoc(value); //search for value
            if(currLoc != NULL){ //if value found
                if(last->next==last){
                    last = NULL;
                }else if(currLoc==last){
                    predLoc->next=last->next;
                    last=predLoc;
                }else{
                    predLoc->next=currLoc->next;
                }
                delete currLoc;
            }
            else{ //if value not found, then this is executed
                cout<<"value not found, deletion not possible.."<<endl;
            }
        }
        cout<<value<<" is deleted from list "<<endl; 
    }


    void DestroyList(){ //delete all the list
    cout<<"destroying list"<<endl;
    NodeClass *tempNode = last->next; //create a node ,same address as start/current
        while(last->next != last){ //while list is not empty
            tempNode=last->next;
            last->next=last->next->next;
            delete tempNode;
        }
        delete last;
        last = NULL;
    }

   
};

int main(void){
    CircularLinkedList csl;
    csl.InsertSorted(1);
    csl.InsertSorted(2);
    csl.InsertSorted(5);
    csl.InsertSorted(4);
    csl.InsertSorted(6);
    csl.InsertSorted(8);
    csl.InsertSorted(9);
    csl.InsertSorted(7);
    csl.PrintList();
    csl.Delete(1);
    csl.PrintList();
    csl.Delete(5);
    csl.PrintList();
    csl.Delete(9);
    csl.PrintList();
    csl.DestroyList();
    csl.PrintList();

}