#include<iostream>
#include<queue>
using namespace std;
class Node {
    public:
    struct data {
        string c;
        unsigned int ncount;
    } data;
    
    Node* right;
    Node* left;
    Node(){
        data.c="";
        data.ncount=0;
        right=left=NULL;
    }
    Node(string c,int count, Node* l, Node* r){
        data.c=c;
        data.ncount=count;
        left=l;
        right=r;
    }
};
struct acount{
    unsigned int count;
};
class Compare {
    public:
    bool operator()(Node* a, Node* b){
        if(a->data.c.length() < b->data.c.length()) return false;
        if(a->data.c.length() == b->data.c.length()) {
            if(a->data.ncount < b->data.ncount) return true;
            else if(a->data.ncount == b->data.ncount){
                return a->data.c[0] < b->data.c[0];
            }
            return false;
        }
        return false;
    }
};
class codeMap {
    public:
    long code;
    int bits;
};

Node* buildTree(priority_queue<Node*, vector<Node*>, Compare> &q){
    while(q.size()>1){
        Node* x1= q.top();
        q.pop();
        Node* x2= q.top();
        q.pop();
        q.push(new Node(x1->data.c+x2->data.c,x1->data.ncount + x2->data.ncount, x1, x2));
    }
    return q.top();
}
void printTree(Node* t){
    if(t==NULL){
        return;
    }
    cout<<t->data.c<<"->"<<t->data.ncount<<endl;
    printTree(t->left);
    printTree(t->right);
}
void createCodeTable(Node* t, codeMap *cmap, long ch, unsigned int size){
    if(t->left== NULL && t->right==NULL){
        if(t->data.c[0]==' '){
            cmap[26].code= ch;
            cmap[26].bits= size;
        }
        else {
            cmap[t->data.c[0]-'a'].code=ch;
            cmap[t->data.c[0]-'a'].bits=size;
        }
    }
    ch=(ch<<1);
    if(t->left!=NULL) createCodeTable(t->left, cmap, ch, size+1);
    if(t->right!=NULL) createCodeTable(t->right, cmap, (ch|1), size+1);
}
int main(){
    acount alphac[27];
    priority_queue<Node*, vector<Node*>, Compare> q;
    for(int i=0; i<27; i++){
        alphac[i].count=0;
    }
    FILE* fp= fopen("one.txt","r");
    if(fp==NULL) return 0;
     while(!feof(fp)){
        char c= fgetc(fp);
        if(c==' ') {
            (alphac[26]).count++;
        }
        else {
            (alphac[c-'a']).count++;
        }
    }
    for(int i=0; i<27; i++){
        string s= "";
        s+=('a'+i);
        if(alphac[i].count!=0)q.push(new Node(s,alphac[i].count, NULL,NULL));
    }
    // for(int i=0;i<27;i++){
    //     if(alphac[i].count!=0)cout<<char('a'+i)<<" "<<alphac[i].count<<endl;
    // }
    while(q.size()>1){
        Node* x1=NULL,*x2=NULL;
        x1= q.top();
        q.pop();
        x2= q.top();
        q.pop();
        q.push(new Node(x1->data.c+x2->data.c,x1->data.ncount + x2->data.ncount, x1, x2));
    }
    Node* t= q.top();
    fseek(fp,0,SEEK_SET);
    codeMap *cmap=new codeMap[27];
    long c=0;
    createCodeTable(t,cmap,c,0);
    for(int i=0;i<27;i++){
        if(alphac[i].count!=0) cout<<char(i+'a')<<" "<<cmap[i].code<<" "<<cmap[i].bits<<endl;
    }
    //printTree(t);
    FILE* fp2= fopen("output.txt","wb");
    // fwrite(alphac, sizeof(int), 27, fp2);
    unsigned int cw=0;
    fseek(fp,0,SEEK_SET);
    int sl=0;
    bool b=true;
    while(!feof(fp)){
        char c= fgetc(fp);
        int rembits=64-sl;
        if(rembits>=cmap[c-'a'].bits){
            cw= (cmap[c-'a'].code<<sl)|cw;
            sl= sl+cmap[c-'a'].bits;
        }
        else if(rembits>0){
            cw= (cmap[c-'a'].code<<sl)&cw;
            fwrite(&cw, sizeof(long), 1, fp2);
            cw=cmap[c-'a'].code>>(cmap[c-'a'].bits-rembits);
            sl= sl+cmap[c-'a'].bits-rembits;
        }
        else{
            fwrite(&cw, sizeof(long), 1, fp2);
            cw=0;
            sl=0;
        }
    }

return 0;
}