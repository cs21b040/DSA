#include<vector>
#include<iostream>
using namespace std;
#define pi pair<int,float>
int partition(vector<pi> &arr, int low, int high){
    int pivot= arr[high].first;
    int i=low-1;
    for(int j=low; j<high; j++){
        if(arr[j].first<pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}

void quickSort(vector<pi> &arr, int low, int high){
    if(low<high){
        int k= partition(arr,low,high);
        quickSort(arr,low,k-1);
        quickSort(arr,k+1, high);
    }
    
}