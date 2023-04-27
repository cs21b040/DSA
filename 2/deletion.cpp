#include <iostream>
#include <vector>
#include <algorithm>
#define max_elements 3
using namespace std;
void heapify(vector<pair<int, int> > &t, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && t[l].first > t[largest].first)
        largest = l;

    if (r < n && t[r].first > t[largest].first)
        largest = r;

    if (largest != i)
    {
        swap(t[i], t[largest]);

        heapify(t, n, largest);
    }
}
void max_heapify_upwards(vector<pair<int, int> > &t, int index)
{
    int parent = (index - 1) / 2;
    if (index > 0 && t[index].first > t[parent].first)
    {

        pair<int, int> temp = t[index];
        t[index] = t[parent];
        t[parent] = temp;
        max_heapify_upwards(t, parent);
    }
    else
    {
        return;
    }
}
void max_heapify_downwards(vector<pair<int, int> >& t, int index, int size)
{
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int largest = index;

    if (left_child < size && t[left_child].first > t[largest].first)
        largest = left_child;

    if (right_child < size && t[right_child].first > t[largest].first)
        largest = right_child;

    if (largest != index)
    {
        swap(t[index], t[largest]);
        max_heapify_downwards(t, largest, size);
    }
}

void deleteRootMin(vector<pair<int, int> > &heap, int &heapSize)
{
    if (heapSize <= 0){
        cout << "Heap is empty" << endl;
        return;
    }

    // Replace the root with the last element in the heap
    heap[0] = heap[heapSize - 1];
    heapSize--;

    // Reheapify the tree
    int i = 0;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    while (left < heapSize){
        if (heap[left].first < heap[i].first){
            smallest = left;
        }

        if (right < heapSize && heap[right].first < heap[smallest].first){
            smallest = right;
        }

        if (smallest != i){
            swap(heap[i], heap[smallest]);
            i = smallest;
            left = 2 * i + 1;
            right = 2 * i + 2;
        }
        else{
            break;
        }
    }
}

void delete_element_from_max_heap(vector<pair<int, int> > &a,int i,int n){
    int z=a[i].first;
    a[i]=a[n];
    n--;
    int parent = (i - 1) / 2;
     int l = 2 * i + 1;
    int r = 2 * i + 2;
    if(a[i].first>a[parent].first){
        max_heapify_upwards(a,i);
    }
    if(a[i].first<a[l].first|| a[i].first<a[r].first){
        max_heapify_downwards(a,i,n);
    }
}

void deleteRoot(vector<pair<int, int> > &t, int &n){
    pair<int, int> lastElement = t[n - 1];
    t[0] = lastElement;
    n = n - 1;
    heapify(t, n, 0);
}


void min_heapify_upwards(vector<pair<int, int> > &t, int index){
    int parent = (index - 1) / 2;
    if (index > 0 && t[index].first < t[parent].first){
        pair<int, int> temp = t[index];
        t[index] = t[parent];
        t[parent] = temp;
        min_heapify_upwards(t, parent);
    }
}
int main(){
    vector<pair<int, int> > H1;
    vector<pair<int, int> > H2;
    float t = 0;
    float s1 = 0, s2 = 0;
    int c1 = -1, c2 = -1;
    int x, w, k = 99;
    cin >> x;
    cin >> w;
    H2.push_back(make_pair(x, w));
    c2++;
    s2 += w;

    while (k--)
    {

        int y, z;

        cin >> y;
        cin >> z;

        if (y >= H2[0].first)
        {
            H2.push_back(make_pair(y, z));
            c2++;

            s2 += z;

            min_heapify_upwards(H2, c2);

            t = s1 + s2;

            while (s1 < 0.5 * t)
            {

                if ((s1 + H2[0].second) <= 0.5 * t)
                {
                    s1 += H2[0].second;
                    s2 = s2 - H2[0].second;
                    // H1[++c1] = H2[0];
                    H1.push_back(H2[0]);
                    c1++;

                    max_heapify_upwards(H1, c1);
                    int g = c2 + 1;
                    deleteRootMin(H2, g);
                    c2--;
                    H2.pop_back();
                }
                else
                {
                    break;
                }
            }
        }

        else
        {

            H1.push_back(make_pair(y, z));

            s1 += z;
            c1++;
            max_heapify_upwards(H1, c1);

            t = s1 + s2;
            while (s1 > 0.5 * t)
            {

                s1 -= H1[0].second;
                s2 += H1[0].second;
                // H2[++c2]=H1[0];
                H2.push_back(H1[0]);

                c2++;
                min_heapify_upwards(H2, c2);

                int o = c1 + 1;
                deleteRoot(H1, o);
                c1--;
                H1.pop_back();
            }
        }
        cout<<"weighted median is - ";
        if(c1!=-1){
        cout<<H1[0].first<<endl;
        }
        else{
            cout<<"no weighted median until now";
        }
        
    }
    int d;
        cin>>d;
        if(d==-1){
            delete_element_from_max_heap(H2,1,9);
        }

}