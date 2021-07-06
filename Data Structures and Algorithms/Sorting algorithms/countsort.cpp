#include <bits/stdc++.h>
using namespace std;


void countSort(int a[], int n){
    int k=a[0];
    for (int i = 0; i < n; ++i) {
        k=max(k,a[i]);
    }

    int count[10]={0};
    for (int j = 0; j < n; ++j) {
        count[a[j]]++;
    }

    for (int l = 1; l <=k; ++l) {
        count[l]+=count[l-1];
    }

    int output[n];
    for (int m = n-1; m >= 0; --m) {
        output[--count[a[m]]]=a[m];
    }

    for (int i1 = 0; i1 < n; ++i1) {
        a[i1]=output[i1];
    }
}
int main(int argc, char const *argv[])
{
    int a[]={2,3,5,2,3,2,1,5,4,1};
    countSort(a,10);
    for (int i = 0; i < 10; ++i) {
        cout<<a[i]<<" ";
    }
    return 0;
}