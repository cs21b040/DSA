#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
using namespace std;
int max(int a,int b){
    if(a>b) return a;
    return b;
}
class Node {
    public:
    int val;
    double lval,rval;
    double x;
    Node* lchild;
    Node* rchild;
    int maxLeft;
    int height;
    Node(int xy,double y){
        val=xy;
        this->x=y;
        lval=rval=0;
        this->maxLeft=0;
        this->lchild=NULL;
        this->rchild=NULL;
    }
    Node(){
        lval=rval=0;
        this->lchild=NULL;
        this->rchild=NULL;
    }
};
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
    (*x)->rval=rc->lval;
    (*x)= rc;
    (*x)->maxLeft=max((*x)->lchild->val,(*x)->lchild->maxLeft);
    (*x)->rchild->maxLeft=max((*x)->rchild->val,(*x)->rchild->maxLeft);
    (*x)->lval=(*x)->lchild->lval+(*x)->lchild->rval+(*x)->lchild->x;
    (*x)->lchild->height= computeHeight((*x)->lchild);
    (*x)->height= computeHeight(*x);
}
void rightRotate(Node** x){
    if(*x==NULL) return;
    Node* lc= (*x)->lchild;
    Node* xlr= lc->rchild;
    lc->rchild= (*x);
    (*x)->lchild= xlr;
    (*x)->lchild->lval=lc->rval;
    (*x)= lc;
    (*x)->maxLeft=max((*x)->lchild->val,(*x)->lchild->maxLeft);
    (*x)->rchild->maxLeft=max((*x)->rchild->val,(*x)->rchild->maxLeft);
    (*x)->rval=(*x)->rchild->rval+(*x)->rchild->lval+(*x)->rchild->x;
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
Node* createNode(int val,double pro){
    Node* m= new Node(val,pro);
    m->rchild=NULL;
    m->lchild=NULL;
    m->height=0;
    return m;
}
Node* insert(int val,double pro, Node** node){
    if((*node)==NULL){
        (*node)= createNode(val,pro);
        return (*node);
    }
    else if((*node)->val > val){
        (*node)->lval+=pro;
        (*node)->maxLeft=max((*node)->maxLeft,val);
        (*node)->lchild=insert(val,pro,&((*node)->lchild));
    }
    else if((*node)->val < val){
        (*node)->rval+=pro;
        (*node)->rchild=insert(val,pro,&((*node)->rchild));
    }
    if(node!=NULL) (*node)->height= computeHeight(*node);
    fix(node);
    return (*node);
}
void printTree(Node* node){
    if(node==NULL) return;
    cout<<node->val<<" "<<node->x<<" "<<node->lval<<" "<<node->rval<<" "<<node->maxLeft<<endl;
    printTree(node->lchild);
    printTree(node->rchild);
}
int minRight=INT_MAX;
double ans;
void RightMin(Node* node){
    if(node==NULL) return ;
    else{
        if(minRight>node->val){
            ans=node->x;
            minRight=node->val;
        }
        RightMin(node->lchild);
        RightMin(node->rchild);
    }
}
void refresh(){
    minRight=INT_MAX;double ans=0;
}
int select(Node* node,double alpha){
    refresh();
    if(node==NULL) return 0;
    double k=node->lval;
    RightMin(node->rchild);
    double temp=ans;
    // cout<<minRight<<" "<<temp<<endl;
    // cout<<k<<" "<<maxLeft<<" "<<temp<<endl;
    // if(k<=alpha){
    //     if(k+node->x>alpha) return maxLeft;
    //     else if(k+node->x+temp>=alpha) return node->val;
    //     else return select(node->rchild,alpha-k-node->x);
    // }
    cout<<"main "<<alpha<<" "<<k<<" "<<temp<<" "<<node->x<<endl;
    cout<<(round(k*100)<=round(alpha*100))<<" "<<(round(k*100)+round(node->x*100)>round(alpha*100))<<" "<<(round(k*100)+round(node->x*100)+round(temp*100)>round(alpha*100))<<endl;
    if(round(k*100)<=round(alpha*100)){
        if(round(k*100)+round(node->x*100)>round(alpha*100)) return (node)->maxLeft;
        else if(round(k*100)+round(node->x*100)+round(temp*100)>round(alpha*100)) return node->val;
        else return select(node->rchild,alpha-k-node->x);
    }
    return select(node->lchild,alpha);
}
int main(){
    int n;
    cin>>n;
    vector<pair<int,double>> v(n);
    Node* node=new Node();
    node=NULL;
    for(int i=0; i<n; i++){
        cin>>v[i].first>>v[i].second;
        node= insert(v[i].first,v[i].second,&node);
    }
    printTree(node);
    double alpha;
    cin>>alpha;
    cout<<select(node,alpha)<<endl;
    return 0;
}