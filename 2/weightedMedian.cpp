#include <bits/stdc++.h>
using namespace std;
int parent(int x){
    if (x & 2 == 0){
        return (x / 2) - 1;
    }
    else{
        return x / 2;
    }
}

void minHeapifydownwards(vector<pair<int, int>> &a, int x){
    int small = x;
    int lc = (2 * x) + 1;
    int rc = (2 * x) + 2;
    if (lc < a.size() && a[lc].first < a[small].first){
        small = lc;
    }
    if (rc < a.size() && a[rc].first < a[small].first){
        small = rc;
    }
    if (small != x){
        swap(a[small], a[x]);
        minHeapifydownwards(a, small);
    }
}
void maxHeapifydownwards(vector<pair<int, int>> &a, int x){
    int large = x;
    int lc = (2 * x) + 1;
    int rc = (2 * x) + 2;
    if (lc < a.size() && a[lc].first > a[large].first){
        large = lc;
    }
    if (rc < a.size() && a[rc].first > a[large].first){
        large = rc;
    }
    if (large != x){
        swap(a[large], a[x]);
        maxHeapifydownwards(a, large);
    }
}
void minHeapifyupwards(vector<pair<int, int>> &a, int x){
    int k = x;
    if (a[parent(x)].first > a[x].first){
        k = parent(x);
    }
    if (k != x){
        swap(a[k], a[x]);
        minHeapifyupwards(a, k);
    }
}

void maxHeapifyupwards(vector<pair<int, int>> &a, int x){
    int k = x;
    if (a[parent(x)].first < a[x].first){
        k = parent(x);
    }
    if (k != x){
        swap(a[k], a[x]);
        maxHeapifyupwards(a, k);
    }
}
void deleteRootmaxHeap(vector<pair<int, int>> &a, int n){
    int lastElement = a[n - 1].first;
    a[0].first = lastElement;
    a[0].second = a[n - 1].second;
    a.pop_back();
    n = n - 1;
    maxHeapifydownwards(a, 0);
}
void deleteRootminHeap(vector<pair<int, int>> &a, int n){
    int lastElement = a[n - 1].first;
    a[0].first = lastElement;
    a[0].second = a[n - 1].second;
    a.pop_back();
    n = n - 1;

    minHeapifydownwards(a, 0);
}
int main(){
    vector<pair<int, int>> minHeap;
    vector<pair<int, int>> maxHeap;
    double k, w;
    double s1 = 0, s2 = 0, t = 0;
    double cmin = 0;
    double cmax = 0;
    cin >> k;
    cin >> w;
    minHeap.push_back({k, w});
    s1 = w;
    cmin++;
    while (k != -1 && w != -1){
        cin >> k >> w;
        if (k > minHeap[0].first){
            s1 = s1 + w;
            t = s2 + s1;
            minHeap.push_back({k, w});
            cmin++;
            minHeapifyupwards(minHeap, cmin - 1);
            while (2 * (s2 + minHeap[0].second) <= t){
                s2 = s2 + minHeap[0].second;
                s1 = s1 - minHeap[0].second;
                maxHeap.push_back(make_pair(minHeap[0].first, minHeap[0].second));
                cmax++;
                cmin--;
                maxHeapifyupwards(maxHeap, cmax - 1);
                deleteRootminHeap(minHeap, minHeap.size());
            }
        }
        else{
            maxHeap.push_back(make_pair(k, w));
            cmax++;
            s2 = s2 + w;
            t = s2 + s1;
            maxHeapifyupwards(maxHeap, cmax - 1);
            while (((2 * s2) / t) > 1){
                s2 = s2 - maxHeap[0].second;
                s1 = s1 + maxHeap[0].second;
                minHeap.push_back(make_pair(maxHeap[0].first, maxHeap[0].second));
                cmin++;
                cmax--;
                minHeapifyupwards(minHeap, cmin - 1);
                deleteRootmaxHeap(maxHeap, maxHeap.size());
                if (s2 == 0)
                {
                    break;
                }
            }
        }
        if (maxHeap.size() != 0){
            cout << "median :" << maxHeap[0].first << endl;
        }
    }
}