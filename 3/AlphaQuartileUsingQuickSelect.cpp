#include<iostream>
#include<vector>
#include<climits>
#include"QuickSort.cpp"
using namespace std;
float round(float var){
    float val = (int)(var * 100 + .5);
    return (float)val / 100;
}
int partition2(vector<pi> &v, int low, int high){
    int i= low-1;
    int pivot= v[high].first;
    int pivIn=0;
    for(int j=low; j<=high; j++){
        if(v[j].first<pivot){
            i++;
            swap(v[i],v[j]);
        }
    }
    for(int i=low; i<=high; i++){
        if(v[i].first==pivot){
            pivIn= i;
            break;
        }
    }
    swap(v[pivIn],v[i+1]);
    return i+1;
}
int select(vector<pair<int,float>> &v, int low, int high, float alpha){
    if(alpha==1){
        int t=v[low].first,tIdx=low;
        for(int i=low; i<high; i++){
            if(v[i].first>t){
                t=v[i].first;
                tIdx=i;
            }
        }
        return tIdx;
    }
    int k= partition2(v,low,high);
    float s=0;
    for(int i=low; i<k; i++){
        s+= v[i].second;
    }
    int minVal= v[k+1].first,minIdx=k+1;
    for(int i=k+1; i<=high; i++){
        if(v[i].first<minVal){
            minVal=v[i].first;
            minIdx=i;
        }
    }
    float temp= s + v[k].second + v[minIdx].second;
    if(s<=alpha){
        int t=round(v[k].second+s)*10000;
        if(int(t)>int(round(alpha)*10000)){
            int maxVal= v[low].first,maxIdx=low;
            for(int i=low; i<k; i++){
                if(v[i].first>maxVal){
                    maxVal=v[i].first;
                    maxIdx=i;
                }
            }
            return maxIdx;
        }
        else if(int(round(temp)*10000) > int(round(alpha)*10000)){
            return k;
        }
        else return select(v,k+1,high,alpha-s-v[k].second);
    }
    return select(v,0,k-1,alpha);
}

int main(){

    int n;
    cin>>n;
    vector<pair<int,float>> v(n);
    for(int i=0; i<n; i++){
        cin>>v[i].first>>v[i].second;
    }
    float alpha=0;
    cin>>alpha;
    while(alpha<1){
        int ans= select(v,0,n-1,alpha);
        alpha+=0.05;
        cout<<alpha<<" "<<v[ans].first<<endl;
    }
    return 0;
}