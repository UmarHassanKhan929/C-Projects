void SwapNums(int&a,int&b){
    int temp;
    temp = a;
    a=b;
    b=temp;
}
void ShortBubbleSort(int arr[],int n){
    bool swap=false;
    for(int i=0;i<n;i++){
        swap=false;
        for(int ii=0;ii<n;ii++){
            if(arr[ii+1]<arr[ii]){
                SwapNums(arr[ii+1],arr[ii]);
                swap=true;
            }
        }
        if(!swap){
            return;
        }
    }
}
