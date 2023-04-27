#include <vector>
#include<iostream>
using namespace std;
typedef long long ll;
#define int ll
pair<int,int> stablePartition(vector<int>& arr, int left, int right, int pivot) {

    int lowerCount = 0;
    int upperCount = 0;
    for (int i=left;i<=right;i++) {
        if (arr[i]<pivot) {
            lowerCount++;
        }
        else{
            upperCount++;
        }
    }
    vector<int> temp(right - left + 1);
    int lowerIndex = 0;
    int upperIndex = lowerCount;
    for (int i=left;i<=right;i++) {
        if (arr[i] < pivot) {
            temp[lowerIndex++] = arr[i];
        }
        else{
            temp[upperIndex++] = arr[i];
        }
    }
    for (int i=0;i<temp.size();i++) {
        arr[left + i] = temp[i];
    }
    return {lowerCount,upperCount};
}

void stableQuickSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivot = arr[left];
        pair<int,int> p=stablePartition(arr, left, right, pivot);
        int lowerCount=p.first, upperCount=p.second;
        stableQuickSort(arr, left, left + lowerCount - 1);
        stableQuickSort(arr, left + lowerCount, right);
    }
}
int32_t main(){
    int n;cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++)
        cin>>v[i];
    stableQuickSort(v,0,n-1);
    for(int i=0;i<n;i++)
        cout<<v[i]<<" ";
    return 0;
}
