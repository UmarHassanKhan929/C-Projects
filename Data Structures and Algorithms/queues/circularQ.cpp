template<typename T>
class CircularQueue{ //circular queue

    T queue[MAX];
    int NumOfElements,front,rear;

public:
    CircularQueue(){ //constructor
        front=0;
        NumOfElements=0;
        rear=MAX-1;
    }

    bool IsEmpty(){ //check if empty
        return (NumOfElements==0?true:false);
    }
    bool IsFull(){ //check if full
        return (NumOfElements==MAX?true:false);
    }
    void Enqueue(T element){ //insert from the rear, auto adjusting aswell
        if(IsFull()){ //if full, cant enqueue
            cout<<"queue is full cant enter more elements"<<endl;
        }else{ //if not full
            rear++;
            if(rear==MAX){ //if rear is greater than last index of array, and array not full, then adjusting
                rear=0;
            }
            queue[rear]=element;
            NumOfElements++;
        }
    }
    T Dequeue(){ //remove the front element
        T element;
        if(IsEmpty()){ //if empty, gucci gang
            cout<<"queue is empty, cant deleto...."<<endl;
            return -1;
        }else{ //removing, stuff and managing
            element=queue[front];
            front++;
            if(front==MAX){
                front=0;
            }
            NumOfElements--;
        }
        return element;
    }
    T StalkFirst(){ //seek the front
        if(IsEmpty()){
            cout<<"cant stalk..."<<endl;
        }else{
            return queue[front];
        }
    }
    void ClearQueue(){ //clearing queue
        front=0;
        NumOfElements=0;
        rear=MAX-1;
    }

};
