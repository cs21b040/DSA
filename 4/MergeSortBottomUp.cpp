#include<iostream>
#include<vector>
using namespace std;
void merge(vector<int> v, int low, int mid, int high){
    int i=low,j=mid+1,k=0;
    int b[high-low+1];
    while(i<=mid && j<=high){
        if(v[i]<v[j]){
            b[k]=v[i];
            i++; k++;
        }
        else {
            b[k]=v[j];
            j++; k++;
        }
    }
    while(i<=mid){
        b[k]=v[i];
        i++; k++;
    }
    while(j<=high){
        b[k]=v[j];
        j++; k++;
    }

    for(int it=0; it<high-low+1; it++){
        v[low+it]=b[it];
    }
}

void mergeSort(vector<int> v, int n){
    int size=1;
    while(size<=n){
        for(int i=0; i<n; i+=2*size){
            int end=min(n-1,i+2*size-1);
            int mid=min(i+size-1,n-1);
            if(mid>=end) break;
            merge(v,i,mid,end);
        }
        size=size*2;
    }
}
int main(){
    int n;
    cin>>n;
    vector<int>v(n);
    for(int i=0; i<n; i++){
        cin>>v[i];
    }    
    mergeSort(v,n);
    for(int i=0; i<n; i++){
        cout<<v[i]<<" ";
    }
    
    return 0;
}