void BubbleSort(int[],int);
void SwapNums(int&a,int&b){
    int temp;
    temp = a;
    a=b;
    b=temp;
}

void BubbleSort(int arr[],int n){
    for(int i=0;i<n;i++){
        for(int ii=0;ii<n;ii++){
            if(arr[ii+1]<arr[ii]){
                SwapNums(arr[ii+1],arr[ii]);
            }
		}
	}
}	