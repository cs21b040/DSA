#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#define maxskiplevel 5
using namespace std;
struct node {
    int data;
    node *next[maxskiplevel + 1];
};
struct skiplist {
    node *header;
    node head;
    node tail;
    int listlevel;
    skiplist(){
        head.data = INT_MIN;
        tail.data = INT_MAX;
        header = &head;
        for (int i = 0; i <= maxskiplevel; i++){
            head.next[i] = &tail;
            tail.next[i] = NULL;
        }
        listlevel = 0;
    }
};
skiplist Insert(int datas, skiplist l){
    int i;
    node *update[maxskiplevel + 1];
    node *temp = &(l.head);

    for (int i = l.listlevel; i >= 0; i--){
        if (i == 0){
            node *currr = l.head.next[i];
        }
        while (temp->next[i] != &(l.tail) && temp->next[i]->data < datas){
            temp = temp->next[i];
        }
        if (temp->next[i] == &(l.tail) && temp == &(l.head)){
            update[i] = &(l.head);
        }
        else{
            update[i] = temp;
        }
    }
    temp = temp->next[0];
    if (temp != &l.tail && temp->data == datas){
        cout << datas <<" is already in the list" << endl;
        return l;
    }
    int nlevel;
    for (nlevel = 0; double(rand()) / RAND_MAX > 0.5 && nlevel < maxskiplevel; nlevel++){}

    if (nlevel > l.listlevel){
        for (int i = l.listlevel + 1; i <= nlevel; i++){
            update[i] = &(l.head);
            l.head.next[i] = &l.tail;
        }
        l.listlevel = nlevel;
    }
    node *nn = new node();
    nn->data = datas;
    for (int i = 0; i <= nlevel; i++){
        nn->next[i] = update[i]->next[i];
        update[i]->next[i] = nn;
    }
    return l;
}

void findelement(int data, skiplist l){
    node *temp = &(l.head);
    for (int i = l.listlevel; i >= 0; i--){
        while (temp->next[i] != &(l.tail) and temp->next[i]->data < data){
            temp = temp->next[i];
        }
    }
    temp = temp->next[0];
    if (temp != &(l.tail) and temp->data == data){
        cout << data<< " is in skiplist" << endl;
    }
    else
        cout << data<< " is not available in skiplist" << endl;
}
void Delete(int data, skiplist l){
    int i;
    node *update[maxskiplevel + 1];
    node *temp = l.header;
    for (int i = l.listlevel; i >= 0; i--){
        while (temp->next[i] != &l.tail and temp->next[i]->data < data){
            temp = temp->next[i];
        }
        update[i] = temp;
    }
    temp = temp->next[0];
    if (temp == &l.tail or !(temp->data == data)){
        cout << "element is not present" << endl;
        return;
    }
    for (i = 0; i <= l.listlevel; i++){
        if (update[i]->next[i] != temp){
            break;
        }
        update[i]->next[i] = temp->next[i];
    }
    delete (temp);
    while (l.listlevel > 0 and l.header->next[l.listlevel] == &l.tail){
        l.listlevel--;
    }
}

int main(){
    skiplist mylist;
    int n;cin>>n;
    for(int i=0;i<n;i++){
        int x;cin>>x;
        mylist = Insert(x, mylist);
    }
    findelement(111, mylist);
    findelement(5, mylist);
    Delete(5, mylist);
    findelement(5, mylist);
    return 0;
}