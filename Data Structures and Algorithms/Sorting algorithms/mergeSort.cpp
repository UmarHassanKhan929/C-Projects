//// merge sort
void MergeSort(int arr[],int f,int l);
void Merge(int arr[],int lf,int ll,int rf,int rl);


void MergeSort(int arr[],int f,int l){
    if(f<l){
        int m = ((f+l)/2);
        MergeSort(arr,f,m);
        MergeSort(arr,m+1,l);
        Merge(arr,f,m,m+1,l);
    }
}
void Merge(int arr[],int lf,int ll,int rf,int rl){
    int n1 = rf-lf;
    int n2 = rl-ll;
    int Lh[n1];
    int Rh[n2];

    for (int i = 0; i < n1; i++){
        Lh[i] = arr[lf + i];
    }
	
    for (int j = 0; j < n2; j++){
        Rh[j] = arr[rf + j];
    }
	
    //for 1,2 temp array
    int i = 0;
    int j = 0;
    int k = lf;

    while (i < n1 && j < n2) {
        if (Lh[i] <= Rh[j]) {
            arr[k] = Lh[i];
            i++;
        } else {
            arr[k] = Rh[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = Lh[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = Rh[j];
        j++;
        k++;
    }

}