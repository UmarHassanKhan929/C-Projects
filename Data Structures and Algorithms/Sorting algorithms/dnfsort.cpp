//0,1,2 sort
#include <bits/stdc++.h>
using namespace std;


 void dnfSort(int a[],int n){
 	int low=0,mid=0,high=n-1;

 	while(mid<=high){
 		if (a[m]==0)
 		{
 			swap(a,low,mid);
 			low++;
 			mid++;
 		}else if(a[m]==1){
 			mid++;
 		}else{
 			swap(a,mid,high);
 			high--;
 		}
 	}
 }

 int main(int argc, char const *argv[])
 {
 	int a[9]={0,1,2,1,0,2,2,1,0};
 	dnfSort(a,0,9);

 	for (int i = 0; i < 9; ++i)
 	{
 		cout<<a[i]<<" ";
 	}
 	return 0;
 }