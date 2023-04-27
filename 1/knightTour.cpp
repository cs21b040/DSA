#include <bits/stdc++.h>
using namespace std;
int mat[8][8];
int row[8]={2,1,-1,-2,-2,-1,1,2};
int col[8]={1,2,2,1,-1,-2,-2,-1};
bool knight_tour(int r,int c,int move){
    int n=8;
	if(move==n*n) 
		return true; 
	int idxX,idxY;
	for(int k=0;k<n;k++){
		idxX=r+row[k];
		idxY=c+col[k];
		if(idxX>=0 && idxY>=0 && idxX<n && idxY<n && mat[idxX][idxY]==-1){
			mat[idxX][idxY] = move + 1; 
			if(knight_tour(idxX,idxY,move+1) == 1) return true;
			else mat[idxX][idxY] = -1;
		}
	}
	return false;
}
int main() {
    int n=8;
	memset(mat,-1,sizeof(mat));
	mat[0][0] = 1;
	if(knight_tour(0,0,1)){
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n;j++)
                cout<<mat[i][j]<<"  ";
            cout<<endl;
        }
	}
	else 
        cout<<"not possible"<<endl;
	return 0;
}