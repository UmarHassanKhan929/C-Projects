void SwapNums(int&a,int&b){
    int temp;
    temp = a;
    a=b;
    b=temp;
}
void SelectionSort(int arr[],int n){
    int current,currmin,min;
    for(current=0;current<n-1;current++){
        min=current;
        for(currmin=current+1;currmin<n;currmin++){
            if(arr[currmin]<arr[min]){
                min=currmin;

            }
        }
        SwapNums(arr[min],arr[current]);

    }
}
