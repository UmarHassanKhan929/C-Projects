#include <iostream>
#include <deque>
#include <bits/stdc++.h>
using namespace std;



int main()
{
    
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);

    for(auto &i: arr)
        cin >> i;

    
    // sliding window maximum , NlogN solution
    multiset<int, greater<int>> s;
    vector<int> ans;

    for(int i = 0; i < k; i++)
        s.insert(arr[i]);

    ans.push_back(*s.begin());

    for(int i = k; i < n; i++)
    {
        s.erase(s.find(arr[i-k]));
        s.insert(arr[i]);
        ans.push_back(*s.begin());
    }

    for(auto i: ans)
        cout << i << " ";

    



    // sliding window maximum , N solution
    deque<int> dq;
    vector<int> ans;

    for(int i=0; i<k;i++){
        while(!dq.empty() && arr[i]>=arr[dq.back()])
            dq.pop_back();
        dq.push_back(i);
    }
    ans.push_back(arr[dq.front()]);
    for(int i=k;i<n;i++){
        if(dq.front() == i-k)
            dq.pop_front();
        while(!dq.empty() && arr[i]>=arr[dq.back()])
            dq.pop_back();
        dq.push_back(i);
        ans.push_back(arr[dq.front()]);
    }

    for(auto i: ans)
        cout << i << " ";
}