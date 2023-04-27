#include<iostream>
#include<vector>
using namespace std;
int parent(int x){
    return (x-1)/2;
}
int rchild(int x){
    return (2*x)+2;
}
int lchild(int x){
    return (2*x)+1;
}
void Heapify(int x, vector<int>&v){
    int m=x;
    if(rchild(x)<v.size() && v[m]>v[rchild(x)]){
        m= rchild(x);
    }
    if(lchild(x)<v.size() && v[m]>v[lchild(x)]){
        m= lchild(x);
    }
    if(x!=m){
        swap(v[x],v[m]);
        Heapify(m,v);
    }
}
int extractRoot(vector<int>&v){
    if(v.size()==0) return -1;
    int root=v[0];
    v[0]=v[v.size()-1];
    v.pop_back();
    for(int i=0;i<v.size()/2;i++) Heapify(i,v);
    return root;
}
int kthSmallest(vector<int>&v, int k){
    int min;
    for(int i=0;i<k;i++){
        min=extractRoot(v);
        if(min==-1) return -1;
        cout<<endl;
    }
    return min;
}
int main(){
    int n;cin>>n;
    vector<int>v;
    for(int i=0;i<n;i++) {
        int a;
        cin>>a;
        v.push_back(a);
    }
    for(int i=0;i<v.size()/2;i++) Heapify(i,v);
    int k;cin>>k;
    cout<<kthSmallest(v,k)<<endl;
return 0;
}