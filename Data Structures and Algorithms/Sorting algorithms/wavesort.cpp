#include <bits/stdc++.h>
using namespace std;


//sort array in wave pattern
void wavesort(int a[], int n){
	for (int i = 1; i < n; i+=2)
	{
		if (a[i]>a[i-1])
		{
			swap(a,i,i-1);
		}

		if (a[i]>a[i+1] && i<=n-2)
		{
			swap(a,i,i+1);
		}
	}
}