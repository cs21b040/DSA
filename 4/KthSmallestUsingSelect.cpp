#include<iostream>
#include"QuickSort.cpp"
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;
void sortV(vector<int>&v){
    quickSort(v,0,v.size()-1);
}
int medianOfMedian(vector<int>v){
    while(v.size()%5!=0) v.push_back(INT_MAX);
    if(v.size()<=5){
        sortV(v);
        return v[2];
    }
    vector<int>temp;
    vector<int>medians;
    for(int i=0;i<v.size();i++){
        temp.push_back(v[i]);
        if((i+1)%5==0) {
            sortV(temp);
            medians.push_back(temp[2]);
            temp.clear();
        }
    }
    return medianOfMedian(medians);
}
int partition2(vector<int> &arr, int low, int high){
    int i= low-1;
    int pivot= medianOfMedian(vector<int>(arr.begin()+low, arr.begin()+high+1));
    if(pivot==INT_MAX) pivot= arr[high];
    int pivIn=0;
    for(int j=low; j<=high; j++){
        if(arr[j]<pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    for(int i=low; i<=high; i++){
        if(arr[i]==pivot){
            pivIn= i;
            break;
        }
    }
    swap(arr[pivIn],arr[i+1]);
    return i+1;
}

int select(vector<int> &arr, int low, int high, int k){
    int p= partition2(arr,low,high);
    if(p==k-1) return arr[p];
    if(p>k-1) return select(arr,low,p-1,k);
    return select(arr,p+1,high, k);
}
int main(){
    int n;cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++) cin>>v[i];
    int k;cin>>k;
    if(k>n) {
        cout<<"Invalid Input";
        return 0;
    }
    else{
    cout<<select(v,0,n-1,k)<<endl;
    }
    // sort(v.begin(),v.end());  //for testing
    // cout<<v[k-1];
return 0;
}