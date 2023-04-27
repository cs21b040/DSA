#include<iostream>
#include<vector>
using namespace std;
class Node{
    public:
    int val;
    Node* left,*right;
    Node(int val){
        this->val=val;
        this->left=NULL;
        this->right=NULL;
    }
};
class BST{
    Node* head;
    public:
    void inOrder();//done
    void inOrder(Node* node);//done
    void postOrder();//done
    void postOrder(Node* node);//done
    void preOrder();//done
    void preOrder(Node* node);//done
    void levelOrder();
    void insert(vector<int>inorder,vector<int>post);//done
    Node* insert(int &i,vector<int>&inorder,vector<int>&post,int left,int right);//done
    Node* search(int val);//done
    Node* search(int val,Node* head);//done
    bool isBST();//done
    bool isBST(Node* head);//done
    int height();//done
    int height(Node* head);//done
    Node* LeastCommonAncestor(int p,int q);//done
    Node* LeastCommonAncestor(Node* head,int p,int q);//done
    int diameter(Node* head);//done
    int diameter();//done
    int KthSmallest(int k);//done
    Node* KthSmallest(Node* head,int k,int &val);//done
    int successor(int x);//done
    int successor(int x, Node* root, Node* lastLeft);//done
    int predecessor(int x);//done
    int predecessor(int x, Node* root, Node* lastRight);//done
    void deleteInBST(int x);//done
    void deleteInBST(int x,Node** root);//done
};