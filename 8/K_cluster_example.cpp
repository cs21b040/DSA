#include"RB_cluster.cpp"
int main(){
    int k = 3;
    int n;cin>>n;
    vector<pair<pair<int, int>, int>> vtr(n);
    for(int i=0;i<n;i++){
        int x,y;cin>>x>>y;
        vtr[i]={{x,y},-1};
    }
    vector<Cluster> cluster(k);
    vector<pair<double, double>> centroids(k);
    for (int i = 0; i < k; i++){
        centroids[i] = {vtr[i].first.first, vtr[i].first.second};
        //  cout<<" i "<<i<<" "<<centroids[i].first<<" "<<centroids[i].second<<endl;
        cluster[i].sumx = 0;
        cluster[i].sumy = 0;
        cluster[i].Ele = 0;
    }
    for (int i = 0; i < vtr.size(); i++){
        vector<double> distancevtr(k);
        int minint = INT_MAX;
        double mini = minint;
        for (int j = 0; j < k; j++){
            // cout<< vtr[i].first.first<<" "<<vtr[i].first.second<<" "<<centroids[i].first<<" "<<centroids[i].second<<endl;
            distancevtr[j] = distance(vtr[i].first.first, vtr[i].first.second, centroids[j].first, centroids[j].second);
            mini = minimum(distancevtr[j], mini);
        }
        //  cout<<"distance vtr"<<endl;
        //   for(auto x:distancevtr){
        //       cout<<x<<" ";
        //     cout<<endl;
        // cout<<"mini "<<mini<<endl;
        int minidx = 0;
        for (int j = 0; j < k; j++){
            if (mini == distancevtr[j]){
                minidx = j;
                break;
            }
        }
        // so the point belongs to jth cluster;
        cluster[minidx].tree.insert(vtr[i].first.first, vtr[i].first.second);
        cluster[minidx].Ele++;
        cluster[minidx].sumx += vtr[i].first.first;
        cluster[minidx].sumy += vtr[i].first.second;
        // changing the cluster of point
        vtr[i].second = minidx;
    }
    // updating the centroids
    for (int i = 0; i < k; i++){
        if (cluster[i].Ele != 0){ 
        // cout<<cluster[i].sumx<<" "<<cluster[i].Ele<<endl;
            centroids[i].first = (cluster[i].sumx) / (float)cluster[i].Ele;
            // cout<<centroids[i].first<<endl;
            centroids[i].second = (cluster[i].sumy) / (float)cluster[i].Ele;
        }
    }
    //  for(auto x:centroids)
        // cout<<x.first<<" "<<x.second<<endl
    while (true){
        vector<pair<double, double>> begi = centroids;
        for (int i = 0; i < vtr.size(); i++){
            vector<double> distancevtr(k);
            int minint = INT_MAX;
            double mini = minint;
            for (int j = 0; j < k; j++){
                // cout<< vtr[i].first.first<<" "<<vtr[i].first.second<<" "<<centroids[i].first<<" "<<centroids[i].second<<endl;
                distancevtr[j] = distance(vtr[i].first.first, vtr[i].first.second, centroids[j].first, centroids[j].second);
                mini = minimum(distancevtr[j], mini);
            }
            // for(auto x:distancevtr){cout<<x<<" ";}cout<<endl;
            int minidx = 0;
            for (int j = 0; j < k; j++){
                if (mini == distancevtr[j]){
                    minidx = j;
                }
            }
            // so the point belongs to jth cluster;
            int previousclusterofpoint = vtr[i].second;
            if (minidx != previousclusterofpoint){
                cluster[previousclusterofpoint].tree.deleteByVal(vtr[i].first.first, vtr[i].first.second);
                // decrementing no of elment in that cluster
                cluster[previousclusterofpoint].Ele--;
                // changing the sumx and sumy
                cluster[previousclusterofpoint].sumx -= vtr[i].first.first;
                cluster[previousclusterofpoint].sumy -= vtr[i].first.second;
                cluster[minidx].tree.insert(vtr[i].first.first, vtr[i].first.second);
                cluster[minidx].Ele++;
                cluster[minidx].sumx += vtr[i].first.first;
                cluster[minidx].sumy += vtr[i].first.second;
            }
            // changing the cluster of point
            vtr[i].second = minidx;
        }
        // updating the centroids
        for (int i = 0; i < k; i++){
            if (cluster[i].Ele != 0){
                // cout<<cluster[i].sumx<<" "<<cluster[i].Ele<<endl;
                centroids[i].first = (cluster[i].sumx) / (float)cluster[i].Ele;
                // cout<<centroids[i].first<<endl;
                centroids[i].second = (cluster[i].sumy) / (float)cluster[i].Ele;
            }
        }
        if (begi == centroids){
            break;
        }
    }
    for (int i = 0; i < k; i++){
        cout << "cluster :" << i + 1 << endl;
        printInOrderoutsideclass(cluster[i].tree.getRoot());
    }

    return 0;
}