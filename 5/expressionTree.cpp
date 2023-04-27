#include <iostream>
#include<stack>
using namespace std;
int pref(char c){
    if(c=='+' || c=='-') return 1;
    else if(c=='*' || c=='/') return 2;
    if(c==')') return 0;
    return 3;
}
class Node{
    public:
    char c;
    Node* left,*right;
    Node(char c){
        this->c=c;
        this->left=NULL;
        this->right=NULL;
    }
    Node(){
        this->left=NULL;
        this->right=NULL;
    }
};
void printTree(Node* root, string indent, bool last) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "└─";
            indent += "  ";
        } 
        else {
            cout << "├─";
            indent += "| ";
        }
        cout << root->c << endl;
        printTree(root->left, indent, root->right == nullptr);
        printTree(root->right, indent, true);
    }
}
class Tree{
    public:
    string s;
    stack<Node*>sb,num;
    Tree(string s){
        this->s=s;
    }
    void createTree(){
        for(int i=0;i<s.length();i++){
            Node* node=new Node(s[i]);
            if(s[i]>='0' && s[i]<='9'){
                num.push(node);
            }
            else if(s[i]=='('){
                sb.push(node);
            }
            else if(sb.size()==0){
                sb.push(node);
            }
            else if(pref(s[i])>pref(sb.top()->c)){
                sb.push(node);
            }
            else{
                fix();
                if(s[i]!=')') sb.push(node);
            }
        }
        fix();
    }
    void fix(){
        while(!sb.empty() && !num.empty()){
            Node* u= sb.top();
            if(sb.top()->c=='('){
                sb.pop();
                break;
            }
            sb.pop();
            if(num.size()>=1) u->right= (num.top());
            num.pop();
            if(num.size()>=1) u->left= (num.top());
            num.pop();
            num.push(u);
        }
    }
};

int main() {
    string s;
    getline(cin>>ws,s);
    Tree t(s);
    t.createTree();
    printTree(t.num.top(),"",true);
	return 0;
}