#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int partition(vector<int> &v, int low, int high){
    int i= low-1;
    int pivot= v[high];
    for(int j=low; j<high; j++){
        if(v[j]<pivot){
            i++;
            swap(v[i],v[j]);
        }
    }
    swap(v[high],v[i+1]);
    return i+1;
}
int quickSelect(vector<int> &v, int low, int high, int k){
    if(k>v.size()) return -1;
    int p= partition(v,low,high);
    if(p==k-1) return v[p];
    if(p>k-1) return quickSelect(v,low,p-1,k);
    return quickSelect(v,p+1,high, k);
}
int main(){
    int n;cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++) cin>>v[i];
    int k;cin>>k;
    cout<<quickSelect(v,0,n-1,k)<<endl;
    // sort(v.begin(),v.end());
    // cout<<v[k-1]<<endl;
return 0;
}