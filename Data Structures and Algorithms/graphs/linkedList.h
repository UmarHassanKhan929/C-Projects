#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>
using namespace std;

enum COLOR{
    white,gray,black
};

template<typename T>
class NodeClass{
public:
    T label; //part of node to hold data
    NodeClass *next; //part of node to hold address of next node
    int weight;
    COLOR c;
    int distance;
    NodeClass *pred;

};
template<typename T>
class SingleLinkedList{
public:
    NodeClass<T> *start; //holding address of start node
    NodeClass<T> *last;  //holding address of last node
    NodeClass<T> *currLoc; //holding address of current location
    NodeClass<T> *predLoc; //holding address of predecessor of cuurent loc node

    SingleLinkedList(){ //creating a singly linked list (constructor)
        start = NULL;
        currLoc = NULL;
        predLoc = NULL;
    }

    bool IsEmpty(){// checks whether the list is empty or not. Returns true if empty and false otherwise
        return start == NULL;
    }


    void InsertAtEnd(T value,int w){ // takes input from a user and inserts it at the tail end of a list
        NodeClass<T> *newNode = new NodeClass<T>();
        newNode -> label = value; //storing value
        newNode->weight = w;
        if(IsEmpty()){ //if list is empty, start node gets nn address
            start = newNode;
        }
        else{ //if not empty, last node next ptr stores nn address.
            last -> next = newNode;
        }
        last = newNode; //last ptr has nn address
    }

    void PrintList(){ //print the contents of list
       // cout<<"bout to print list.."<<endl;
        NodeClass<T> *temp = new NodeClass<T>(); //storing current node in temp ptr
        if(!IsEmpty()){
            //cout<<"Printing list"<<endl;
            //int i = 1;
            temp = start; //initialize the temp
            while(temp != NULL){ //looping till temp is not null
                cout <<" -> "<<"("<<temp -> label<<":"<<temp->weight<<")";
                temp = temp -> next;
               // ++i;
            }
        }
        else{
            cout<<"NULL";
        }
    }
#endif //LINKEDLIST_H
