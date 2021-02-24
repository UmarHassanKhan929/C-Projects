//
// stacks implementation using linked list
//

#include <iostream>
using namespace std;

template <typename T>
class NodeClass{
    public:
        T data; //part of node to hold data
        NodeClass *next; //part of node to hold address of next node
};

template <typename T>
class Stack{
    public:
        NodeClass<T> *first; //holding address of start node

    Stack(){
        first = NULL;
    }

    bool IsEmpty(){
        return first == NULL;
    }

    void Push(T x){ //push element on top of stack
        NodeClass<T> *newNode = new NodeClass<T>();
        newNode->data=x;
        if(IsEmpty()){
            first = newNode;
        }
        else{
            newNode->next=first;
            first=newNode;
        }
    }

    T Pop(){ //remove element from top
        int x=0;
        NodeClass<T> *temp;
        if(IsEmpty()){
            cout<<"stack empty, cant pop"<<endl;
        }
        else{
            temp=first;
            x=first->data;
            first=first->next;
            delete temp;
            return x;
        }
        return 0;
    }
    T Peek(){ //see the top element without removing it
        if(IsEmpty()){
            cout<<"stack empty, cant peek"<<endl;
        }
        else{
            return first->data;
        }
        return 0;
    }

};
int main(void){
    Stack<char> ss;
    ss.Push('a');
    ss.Push('b');
    ss.Push('c');
    char x=ss.Pop();
    cout<<x<<endl;
    cout<<ss.Peek()<<endl;
}