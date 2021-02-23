
//Dynamic list implementation using arrays:
#include <iostream>
using namespace std;

struct DynamicArrayList{
    
    const int size = 5; //initial size of array
    int dall=0; //list size/llength
    int *pArray = new int [size]; //pointer pointing to heap of memory

    bool isEmpty(){ //to check if list is empty or not
        return dall == 0;
    }

    bool isFull(){ //to check wether list is full or not
        return dall == (sizeof(pArray)/sizeof(pArray[0]));
    }

    void printList(){ //print the contemts of list
        
        for (int i = 0; i < dall; i++){
            cout << pArray[i] <<endl;
        }
    }

    void CreateRoom(int pos){ //to create space to insert element, if pos index os greater than list length and list is full then expand by dynamic expansion function

        if(pos >= 1 && pos <= dall+1 && !isFull()){

            int newIndex = pos-1;
            int lastIndex = dall-1;

            for(int index=lastIndex; index >= newIndex; index--){
                pArray[index+1] = pArray[index];
            }
        }
        else if (pos > dall && isFull()){ 
            DynamicExpansion();
        }
        else{
            cout<<"index cant be negative..";
        }
    } 

    void FillGap(int pos){ //if element is deleted, to overwrite its place

        if(pos >= 1 && pos < dall){
            int remIndex = pos-1;
            int lastIndex = dall-1;

            for(int index = remIndex; index < lastIndex; index++){
                pArray[index] = pArray[index+1];
            }
        }

        else{
            cout<<"why did this happen???";
        }
    }

    void insertAtposition(int value, int position){ //insert the element at the desired position, looks for place, if list is full then expanded array is made my dynamic expansion

        if (!isFull() && (position >= 1) && (position <= dall+1)){
            CreateRoom(position);
            pArray[position-1] = value;
            dall++;
        }

        else if (isFull()){
            DynamicExpansion();
            CreateRoom(position);
            pArray[position-1] = value;
            dall++;
        }
    }

    void insertSorted(int value){ //checks the appropriate place by comparing values and place it to expected place

        if (isFull()){
            DynamicExpansion();
            pArray[dall] = value;
            dall++;
        }
        else{
            int tempPos;
            for (int i = 1; i <= dall; i++){
                if(value > pArray[i-1]){
                    tempPos=i;
                }
                else{
                    tempPos=1;
                }   
            }
            CreateRoom(tempPos);
            pArray[tempPos] = value;
            dall++;
        }
    }

    void DeleteValue(int value){ //deletes the desired value, and deletes redundent memory(if greater than 50% left)

        int sizeOfArray = sizeof(pArray)/sizeof(pArray[0]);

        if(isEmpty){
            cout<<"list is empty.. nothing to delete here";
        }

        else if( (!isEmpty) && dall >= 1){

            for (int i = 0; i < dall; i++){
                int temp = 0;
                if (pArray[i] == value){
                    temp = i+1;
                    FillGap(temp);
                    dall--;

                    if(dall < sizeOfArray/2){
                        DynamicReduction();
                    }
                }
                break;
            }
        }
        
    }

    void DeleteValueAtPosition(int pos){ // deletes a value if a user enters a valid position (1 <= pos <= size of a list)

        int sizeOfArray = sizeof(pArray)/sizeof(pArray[0]);

        if(isEmpty){
            cout<<"list is empty.. nothing to delete here";
        }
        
        else if( (!isEmpty) && dall >= 1){
            FillGap(pos);
            dall--;
            
            if(dall < sizeOfArray/2){
                DynamicReduction();
            }
        }
    }

    void DynamicExpansion(){ //Increases size of the array when the list becomes full.
        
        int *oldArray = pArray;
        int sizeOfOldArray = sizeof(pArray)/sizeof(pArray[0]);
        pArray = new int[2*sizeOfOldArray];
        
        for(int i = 0; i < sizeOfOldArray; i++){
            pArray[i] = oldArray[i];
        }

        delete [] oldArray;

    }

    void DynamicReduction(){  //decreases size of the array when the size of a list becomes less than 50% after deletion operation
        int *oldArray = pArray;
        int sizeOfOldArray = sizeof(pArray)/sizeof(pArray[0]);
        pArray = new int[sizeOfOldArray/2];
        
        for(int i = 0; i < sizeOfOldArray; i++){
            pArray[i] = oldArray[i];
        }

        delete [] oldArray;
    }
    
};


int main(void){
    
}