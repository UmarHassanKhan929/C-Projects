#include <iostream>
#include <cmath>
using namespace std;

#define MAX 32
class BinaryHeap{

public:

    int index;
    int heapSize;
    int numbers[MAX]={0};

    BinaryHeap(){
        index=1;
        heapSize=0;
        //numbers[MAX-1]={0};
    }

    int getLeftChildIndex(int node){
        return (2*node);
    }
    int getRightChildIndex(int node){
        return ((2*node)+1);
    }
    int getParentIndex(int node){
        return (node/2);
    }




    bool IsEmpty(){
        return heapSize==0;
    }

    bool IsFull(){
        return heapSize==MAX;
    }

    void Insert(int value){
        if(!IsFull()){
            numbers[index]=value;
            ++heapSize;
            BuildMaxHeap(numbers,heapSize);
            ++index;

        }else{
            cout<<"Heap is full"<<endl;
        }
    }

    void MaxHeapify(int arr[],int i, int n){
        int leftIndex = getLeftChildIndex(i);
        int rightIndex = getRightChildIndex(i);
        int largest=i;

        if(leftIndex<=n && arr[leftIndex]>arr[i]){
            largest=leftIndex;
        }

        if(rightIndex<=n && arr[rightIndex]>arr[largest]){
            largest=rightIndex;
        }

        if(largest!=i){
            swap(arr[i],arr[largest]);
            MaxHeapify(arr,largest,n);
        }
         return;
    }

    int FindMax(){
        return numbers[1];
    }

    int DeleteMax(int arr[]){
        if(IsEmpty()){
            return 0;
        }else{
            int max = numbers[1];
            numbers[1] = numbers[heapSize];
            numbers[heapSize]=max;
            heapSize--;
            MaxHeapify(arr,1,heapSize);
            return max;
        }
    }

    int Size(){
        return heapSize;
    }

    void BuildMaxHeap(int arr[],int n){
        for(int i = getParentIndex(n);i>=1;i--){
            MaxHeapify(arr,i,n);
        }
    }

    void PrintHeapElements(){
        for(int i=1;i<=heapSize;i++){
            cout<<numbers[i]<<" ";
        }
    }

    void HeapSort(int arr[]) {
        int tempSize = heapSize;
        BuildMaxHeap(arr,tempSize);

        for (int i = heapSize; i >= 2; i--) {
            swap(arr[i], arr[1]);
            heapSize -= 1;
            MaxHeapify(arr, 1,heapSize);
        }
        heapSize = tempSize;
    }


};

int main(){
    BinaryHeap bh;
    bh.Insert(5);
    bh.Insert(6);
    bh.Insert(10);
    bh.Insert(12);
    bh.Insert(8);
    bh.Insert(3);
    bh.Insert(16);
    //cout<<bh.Size()<<endl;
    cout<<"\n"<<bh.FindMax()<<endl;
    bh.PrintHeapElements();
    cout<<endl;

    bh.HeapSort(bh.numbers);
    bh.PrintHeapElements();
    cout<<endl;

}
