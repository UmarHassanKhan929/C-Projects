int Partition(int arr[],int l,int r,int pivot){
    while(l<=r){
        while(arr[l]<pivot){
            l++;
        }
        while(arr[r]>pivot){
            r--;
        }
        if(l<=r){
            swap(arr[l],arr[r]);
            l++;
            r--;
        }
    }
    return l;

}
void QuickSort(int arr[],int l,int r){
   
    if(l<r){
        int pivot = arr[l];
        int index = Partition(arr,l,r,pivot);
        QuickSort(arr,l,index-1);
        QuickSort(arr,index,r);
        county++;
    }
}
