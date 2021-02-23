
//static list using array

#include <iostream>
using namespace std;

const int sizeEnd = 50; //array size fixed

struct staticArrayList{
    int ll = 0; //current size of list is zero
    int array[sizeEnd]; //creating array of fix size
                                                     
    bool isEmpty(){  //checks if list is empty
        return ll==0;
    }

    bool isFull(){  //checks is list is full
        return ll==sizeEnd;
    }

    void CreateRoom(int pos){ //create room for element to be inserted in list, while shifting rightmost elements to array to the right + 1 place in array

        if(pos >= 1 && pos <= ll+1){

            int newIndex = pos-1;
            int lastIndex = ll-1;

            for(int index=lastIndex; index >= newIndex; index--){
                array[index+1]=array[index];
            }
        }
        else{
            cout<<"out of range...";
        }
    } 

    void insertAtposition(int value, int pos){ //puts at index/ given pos
        
        if (!isFull() && (pos >= 1) && (pos <= ll+1)){
            CreateRoom(pos);
            array[pos-1] = value;
            ll++;
        }
        else{
            cout<<"List is full.. sorry bruh";
        }
    
    }

    void insertSorted(int value){ //logically puts at its sorted position
        if (isFull()){
            cout << "List is full, sorry!!";
        }
        else{
            int tempPos;
            for (int i = 1; i <= ll; i++){
                if(value > array[i-1]){
                    tempPos=i;
                }
                else{
                    tempPos=1;
                }   
            }
            CreateRoom(tempPos);
            array[tempPos] = value;
            ll++;
        }
    }

    void printList(){ //print the list elements
        for (int i = 0; i < ll; i++){
            cout << array[i]<<endl;
        }
    }

    void FillGap(int pos){ //when u need to delete an element, u pass its position, and its removed and other elements shifts one place back
        if(pos >= 1 && pos < ll){
            int remIndex = pos-1;
            int lastIndex = ll-1;

            for(int index = remIndex; index < lastIndex; index++){
                array[index] = array[index+1];
            }
        }
        else{
            cout<<"out of range bruh..";
        }
    }

    void DeleteValue(int value){ //delete the value and fills the gap
        if (isEmpty()){
            cout << "theres NADA is list, enjoi...";
        }
        else{
            for (int i = 0; i < ll; i++){
                int temp = 0;
                if (array[i] == value){
                    temp = i+1;
                    FillGap(temp);
                    ll--;
                }
                break;
            }
        }
    }

    void DeleteValueAtPosition(int pos) { // deletes a value if a user enters a valid position (1 <= pos <= size of a list.)
        if (isEmpty()){
            cout << "theres NADA is list, enjoi...";
        }
        else{
            FillGap(pos);
            ll--;
        }
    }
        //Note: The size of a list and an array are different things.Moreover, an element a location pos in a list is stored at index pos - 1 in the array.
};

int main() {
    
}