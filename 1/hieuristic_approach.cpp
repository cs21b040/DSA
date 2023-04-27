#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
#define n 8
int row[n]={2,1,-1,-2,-2,-1,1,2};
int col[n]={1,2,2,1,-1,-2,-2,-1};
bool isValid(int mat[n][n], int idxX, int idxY){
    return ( mat[idxX][idxY]==-1 && idxX>=0 && idxX<n && idxY>=0 && idxY<n );
}
void solve(int mat[n][n], int idxX, int idxY){
    stack<pair<int,int>> s;
    stack<int> mCount;
    int val=0;
    int newX, newY,count=1;
    vector<pair<int,int>>v;
    bool c=true;
    while(count<64){
        for(int i=val;i<8;i++){
            if(isValid(mat, idxX+row[i], idxY+col[i])){
                newX=idxX+row[i];
                newY=idxY+col[i];
                int count=0;
                for(int i=0;i<8;i++){
                    if(isValid(mat, newX+row[i], newY+col[i])){
                        count++;
                    }
                }
            v.push_back({count,i});
            }
        }
        if(v.empty()!=true){
        sort(v.begin(), v.end());
        mat[idxX+row[v[0].second]][idxY+col[v[0].second]]=count;
        count++;
        s.push(make_pair(idxX,idxY));
        mCount.push(v[0].second);         
        idxX+=row[v[0].second];
        idxY+=col[v[0].second];
        v.clear();
        val=0;
        }
        else{
            mat[idxX][idxY] = -1;
            idxX=s.top().first;
            idxY=s.top().second;    
            val=mCount.top()+1;
            s.pop();
            mCount.pop();
        }
    }
}
int main(){
    int idxX=0, idxY=0,mat[n][n];
    memset(mat,-1,sizeof(mat));
    mat[idxX][idxY] = 0;
    solve(mat, idxX, idxY);
    for(int row=0; row<n; row++){
        for(int col=0; col<n; col++){
            cout<<mat[row][col]<<" ";
        }
        cout<<endl;
    }
}