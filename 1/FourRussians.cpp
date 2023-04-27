#include<bits/stdc++.h>
using namespace std;
int LSB(int n){
    int q=0;
    bool z=n&1;
    while(!z){
        q++;n/=2;z=n&1;
    }
    return q;
}
void createTable(vector<vector<vector<bool>>>&v,vector<vector<bool>>a,int b,int n){
    int size=pow(2,b);
    int RevIdx=0;
    for(int i=0;i<v.size();i++){
        vector<vector<bool>>x(size,vector<bool>(n,0));
        vector<bool>y(n,0);
        RevIdx+=v.size();
        for(int j=1;j<size;j++){
            int q=LSB(j);
            int p=j&(~(1<<q));
            y.clear();
            int idx=RevIdx;
                for(int k=0;k<n;k++){
                    y.push_back(x[p][k]|a[k][idx-q-1]);
                }
            if(j&(j-1)==0) idx--;
            x[j]=y;
        }
        v[i]=x;
    }
}
int main(){
    int n;cin>>n;
    int size=ceil(log2(n));
    int x=ceil((double)n/size);
    int y=pow(2,size);
    vector<vector<bool>>a,b,c;
    vector<vector<vector<bool>>>t(x,vector<vector<bool>>(y,vector<bool>(n,0)));
    for(int i=0;i<n;i++){
        vector<bool>v;
        for(int j=0;j<n;j++){
            bool z;cin>>z;v.push_back(z);
        }
        a.push_back(v);
    }
    for(int i=0;i<n;i++){
        vector<bool>v;
        for(int j=0;j<n;j++){
            bool z;cin>>z;v.push_back(z);
        }
        b.push_back(v);
    }
    createTable(t,a,size,n);
    for(int i=0;i<n;i++){
        vector<int>v;vector<bool>z(n,0);
        int ans=0,temp=x,d=y/2;
        for(int j=0;j<n;j++){
            ans+=d*b[j][i];
            d/=2;temp--;
            if(temp==0 || j==n-1){
                v.push_back(ans);
                ans=0;d=y/2;temp=x;
            }
        }
        for(int k=0;k<n;k++){
            bool p=false;int table=0;
            for(auto in:v){
                p|=t[table++][in][k];
                if(p==true){
                    z[k]=true;
                    break;
                }
            }
        }
        c.push_back(z);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<c[j][i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}