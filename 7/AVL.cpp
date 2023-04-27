#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class line {
    public:
    pair<int,int> p;
    pair<int,int> end;
    bool leftEnd;
    bool horizontal;
    line(){}
    line(pair<int,int>p, pair<int,int>end, bool leftEnd, bool horizontal){
        this->p= p;
        this->end= end;
        this->leftEnd= leftEnd;
        this->horizontal= horizontal;
    }
};

class Node {
    public:
    line l;
    Node* lchild;
    Node* rchild;
    int height;
};

Node* createNode(line l){
    Node* m= new Node();
    m->l=l;
    m->rchild=NULL;
    m->lchild=NULL;
    m->height=0;
    return m;
}

int computeHeight(Node* node){
    int h1=0,h2=0;
    if(node->rchild!=NULL) h1= node->rchild->height;
    if(node->lchild!=NULL) h2= node->lchild->height;
    return (max(h1,h2))+1;
}

int balanceFactor(Node* node){
    int h1=0,h2=0;
    if(node->rchild!=NULL) h1= node->rchild->height;
    if(node->lchild!=NULL) h2= node->lchild->height;

    return h1-h2;
}

void leftRotate(Node** x){
    if(*x==NULL) return;
    Node* rc= (*x)->rchild;
    Node* xrl= rc->lchild;
    rc->lchild= (*x);
    (*x)->rchild= xrl;
    (*x)= rc;
    (*x)->lchild->height= computeHeight((*x)->lchild);
    (*x)->height= computeHeight(*x);
}

void rightRotate(Node** x){
    if(*x==NULL) return;
    Node* lc= (*x)->lchild;
    Node* xlr= lc->rchild;
    lc->rchild= (*x);
    (*x)->lchild= xlr;
    (*x)= lc;
    (*x)->rchild->height= computeHeight((*x)->rchild);
    (*x)->height= computeHeight(*x);
}

void fix(Node** node){
    if(*node==NULL) return;
    int bf= balanceFactor(*node);
    if(bf==2){
        int bfc= 0;
        if((*node)->rchild !=NULL) balanceFactor((*node)->rchild);
        if(bfc>=0) leftRotate(node);
        else {
            rightRotate(&((*node)->rchild));
            leftRotate(node);
        }
    }
    else if(bf==-2){
        int bfc= 0;
        if((*node)->lchild !=NULL) balanceFactor((*node)->lchild);
        if(bfc<=0) rightRotate(node);
        else {
            leftRotate(&((*node)->lchild));
            rightRotate(node);
        }
    }
}

void insert(line x, Node** node){
    if((*node)==NULL){
        (*node)= createNode(x);
        return;
    }
    else if((*node)->l.p.second > x.p.second){
        insert(x, &((*node)->lchild));
    }
    else {
        insert(x, &((*node)->rchild));
    }
    if(node!=NULL) (*node)->height= computeHeight(*node);
    fix(node);
}

void deleteNode(line x, Node** node){
    if(x.p.second < (*node)->l.p.second) deleteNode(x, &((*node)->lchild));
    else if(x.p.second > (*node)->l.p.second) deleteNode(x, &((*node)->rchild));
    else {
        if((*node)->lchild== NULL && (*node)->rchild== NULL){
            delete(*node);
            (*node)= NULL;
        }
        else if((*node)->lchild!= NULL && (*node)->rchild== NULL){
            Node* temp= (*node);
            (*node)= (*node)->lchild;
            delete(temp);
        }
        else if((*node)->rchild!= NULL && (*node)->lchild== NULL){
            Node* temp= (*node);
            (*node)= (*node)->rchild;
            delete(temp);
        }
        else {
            Node** temp= &((*node)->rchild);
            while((*temp)->lchild !=NULL){
                temp= &((*temp)->lchild);
            }
            (*node)->l= (*temp)->l;
            (*temp)->l= x;
            deleteNode(x,temp);
        }
    }
    fix(node);
}


Node* findBST(pair<int,int> p, Node* node){
    if(node==NULL){
        return NULL;
    }
    if(node->l.p== p){
        return node;
    }
    else if(node->l.p.second > p.second){
        return findBST(p, node->lchild);
    }
    else return findBST(p, node->rchild);
}

void inorderTraversal(int x1, int y1, int y2, Node* node, vector<pair<int,int>> &p){
    if(node==NULL) return;
    if(node->l.p.second > y1) inorderTraversal(x1,y1,y2,node->lchild,p);
    else return;
    p.push_back({x1, node->l.p.second});
    if(node->l.p.second < y2) inorderTraversal(x1,y1,y2,node->rchild,p);
    else return;
}

class Compare {
    public:
    bool operator()(line a, line b){
        if(a.p.first == b.p.first){
            return (a.p.second > b.p.second);
        }
        return (a.p.first > b.p.first);
    }
};

int main(){
    int n;
    cin>>n;
    vector<pair<int,int>> ans;
    priority_queue<line, vector<line>, Compare> q; 
    while(n--){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        q.push(line({x1,y1},{x2,y2},x1<x2,y1==y2));
        q.push(line({x2,y2},{x1,y1},x2<x1,y1==y2));
    }

    Node* node= NULL; 
    int f= q.size();
    while(f>0){
        line l= q.top();
        if(l.horizontal){
            if(l.leftEnd){
                insert(l,&node);
            }
            else {
                Node* temp= findBST(l.end,node);
                if(temp!=NULL) {
                    deleteNode(temp->l,&node);
                }
            }
        }
        else {
            q.pop();
            f--;
            inorderTraversal(l.p.first,l.p.second, l.end.second, node, ans);
        }

        q.pop();
        f--;
    }
    for(int i=0; i<ans.size(); i++){
        cout<<"X "<<ans[i].first<<" Y "<<ans[i].second<<endl;
    }
    return 0;
}