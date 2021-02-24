
#include <iostream>
using namespace std;
#define MAX 10 //size of queue

template<typename T>
class LinearQueue{ //linear queue
    T queue[MAX]; //queue box
    int NumOfElements=0,front,rear; //some variables for tracking
public:
    LinearQueue(){ //constructor
        rear = -1;
        front = 0;
    }

    bool IsEmpty(){ //to check if queue is empty
        return (rear<front?true:false);
    }
    bool IsFull(){ //to check if queue is full
        return((rear==MAX-1)?true:false);
    }
    void Enqueue(T element){ // to enqueue element in queue
        if(IsFull()){ //if full, no space
            cout<<"Queue is full, arigato gushaimush.."<<endl;
        }else{ //inserting at end
            queue[++rear]=element;
        }
    }
    T Dequeue(){ //removes element from front
        if(IsEmpty()){
            cout<<"nones at queue, cant do nada"<<endl;
            return -1;

        }else{ //  moves to next to fronnt
            return queue[front++];
        }
    }
    T StalkFirst(){ //see the front value
        if(IsEmpty()){
            cout<<"cant stalk... queue empty.."<<endl;
        }else{
            return queue[front];
        }
    }

    void ClearQueue(){ //emptying queue
        rear = -1;
        front = 0;
        cout<<"queue cleared.."<<endl;
    }



};
