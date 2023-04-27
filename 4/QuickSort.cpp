#include<vector>
#include<iostream>
using namespace std;
int partition(vector<int> &arr, int low, int high){
    int pivot= arr[high];
    int i=low-1;
    for(int j=low; j<high; j++){
        if(arr[j]<pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}

void quickSort(vector<int> &arr, int low, int high){
    if(low<high){
        int k= partition(arr,low,high);
        quickSort(arr,low,k-1);
        quickSort(arr,k+1, high);
    }
    
}