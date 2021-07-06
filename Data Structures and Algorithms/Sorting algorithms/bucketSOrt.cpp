#include <bits/stdc++.h>
#include <vector>
using namespace std;


//only for floating point numbers

void bucketSort(float a[],int n){
	vector<float> buckets[n];
	//adding in buckets
	for (int i = 0; i < n; ++i)
	{
		int indexBucket = n*a[i];
		buckets[indexBucket].push_back(a[i]);
	}

	//sorting buckets
	for (int i = 0; i < n; ++i)
	{
		sort(buckets[i].begin(),buckets[i].end());
	}

	//concat all buckets 
	int index=0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < buckets[i].size(); ++j)
		{
			a[index]=buckets[i][j];
			index++;
		}
	}
}