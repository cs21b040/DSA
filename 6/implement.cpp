#include "BST.cpp"
#include<queue>
void BST::inOrder(){
    inOrder(this->head);
}
void BST::inOrder(Node* head){
    if(head==NULL) return ;
    inOrder(head->left);
    cout<<head->val<<" ";
    inOrder(head->right);
}
void BST::postOrder(){
    postOrder(this->head);
}
void BST::postOrder(Node* head){
    if(head==NULL) return ;
    postOrder(head->left);
    postOrder(head->right);
    cout<<head->val<<endl;
}
void BST::preOrder(){
    preOrder(this->head);
}
void BST::preOrder(Node* head){
    if(head==NULL) return ;
    cout<<head->val<<endl;
    preOrder(head->left);
    preOrder(head->right);
}
void BST::levelOrder(){
    queue<Node*>q;
    if(this->head!=NULL) q.push(this->head);
    while(q.size()!=0){
        Node* x=q.front();
        cout<<x->val<<" ";
        if(x->left!=NULL) q.push(x->left);
        if(x->right!=NULL) q.push(x->right);
        q.pop();
    }
}
void BST::insert(vector<int>inorder,vector<int>post){
    int val=inorder.size()-1;
    this->head=insert(val,inorder,post,0,val);
}
Node* BST::insert(int &i,vector<int>&inorder,vector<int>&post,int left,int right){
    if(left>right) return NULL;
    int x=right;
    while(post[i]!=inorder[x]){
        x--;
    }
    i--;
    Node* root=new Node(inorder[x]);
    root->right=insert(i,inorder,post,x+1,right);
    root->left=insert(i,inorder,post,left,x-1);
    return root;
}
Node* BST::search(int val){
    return search(val,this->head);
}
Node* BST::search(int val,Node* head){
    if(head->val <val){
        return search(val,head->right);
    }
    else if(head->val > val){
        return search(val,head->left);
    }
    else return head;
}
bool BST::isBST(){
    return isBST(this->head);
}
bool BST::isBST(Node* head){
    if(head==NULL) return true;
    if(head->left!=NULL && head->left->val >= head->val){
        return false;
    }
    if(head->right!=NULL && head->right->val <= head->val){
        return false;
    }
    return isBST(head->left) && isBST(head->right);
}
int BST::height(){
    return height(this->head);
}
int BST::height(Node* head){
    if(head==NULL) return 0;
    return 1+max(height(head->left),height(head->right));
}
Node* BST::LeastCommonAncestor(int p,int q){
    return LeastCommonAncestor(this->head,p,q);
}
Node* BST::LeastCommonAncestor(Node* head,int p,int q){
    if(p<= head->val && q>= head->val){
        return head;
    }
    else if(p> head->val){
        return head->right;
    }
    else return head->left;
}
int BST::diameter(){
    return diameter(this->head);
}
int BST::diameter(Node* head){
    if(head==NULL) return 0;
    int x=height(head->left)+height(head->right)+1;
    int y=diameter(head->left);
    int z=diameter(head->right);
    return max(x,max(y,z));
}
int BST::KthSmallest(int k){
    int val=0;
    return KthSmallest(this->head,k,val)->val;
}
Node* BST::KthSmallest(Node* head,int k,int &value){
    if(head == NULL){ return head;}
    Node* left = KthSmallest(head->left, k, value);
    if(left != NULL){
        return left;
    }
    value++;
    if(value == k){
        return head;
    }
    return KthSmallest(head->right, k, value);
}
int BST::predecessor(int x){
    return predecessor(x,this->head,NULL);
}
int BST::predecessor(int x, Node* root, Node* lastRight){
    if(root== NULL) return -1;;
    if(root->val < x){
        return predecessor(x,root->right, root);
    }
    else if(root->val > x){
        return predecessor(x, root->left, lastRight);
    }
    else {
        if(root->left==NULL){
            if(lastRight->val > root->val){
                return -1;
            }
            return lastRight->val;
        }
        root= root->left;
        while(root->right!=NULL){
            root= root->right;
        }
        return root->val;
    }
}
int BST::successor(int x){
    return successor(x,this->head,NULL);
}
int BST::successor(int x, Node* root, Node* lastLeft){
    if(root== NULL) return -1;;
    if(root->val < x){
        return successor(x,root->right, lastLeft);
    }
    else if(root->val > x){
        return successor(x, root->left, root);
    }
    else {
        if(root->right==NULL){
            if(lastLeft->val < root->val){
                return -1;
            }
            return lastLeft->val;
        }
        root= root->right;
        while(root->left!=NULL){
            root= root->left;
        }
        return root->val;
    }
}
void BST::deleteInBST(int x){
    deleteInBST(x,&this->head);
}
void BST::deleteInBST(int x,Node** head){
    if(*head==NULL) return;
    if((*head)->val < x){
        deleteInBST(x,&(*head)->right);
    }
    else if((*head)->val > x){
        deleteInBST(x,&(*head)->left);
    }
    else{
        if((*head)->left==NULL && (*head)->right==NULL){
            *head=NULL;
        }
        else if((*head)->left==NULL){
            *head=(*head)->right;
        }
        else if((*head)->right==NULL){
            *head=(*head)->left;
        }
        else{
            Node* temp=(*head)->right;
            while(temp->left!=NULL){
                temp=temp->left;
            }
            (*head)->val=temp->val;
            deleteInBST(temp->val,&(*head)->right);
        }
    }
}