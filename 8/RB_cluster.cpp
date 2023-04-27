#include <iostream>
#include <queue>
#include <cstdlib>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;
struct point{
    int x;
    int y;
};
enum COLOR{
    RED,
    BLACK
};

class Node{
public:
    point pt;
    COLOR color;
    Node *left, *right, *parent;
    Node(int x, int y){
        parent = left = right = NULL;
        color = RED;
        this->pt.x = x;
        this->pt.y = y;
    }
    Node *uncle(){
        if (parent == NULL or parent->parent == NULL)
            return NULL;
        if (parent->isOnLeft())
            return parent->parent->right;
        else
            return parent->parent->left;
    }
    bool isOnLeft() { return this == parent->left; }
    Node *sibling(){
        if (parent == NULL)
            return NULL;
        if (isOnLeft())
            return parent->right;
        return parent->left;
    }
    void moveDown(Node *nParent){
        if (parent != NULL){
            if (isOnLeft()){
                parent->left = nParent;
            }
            else{
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }
    bool hasRedChild(){
        return (left != NULL && left->color == RED) |(right != NULL && right->color == RED);
    }
};

class RBTree{
    Node *root;
    void leftRotate(Node *x){
        Node *nParent = x->right;
        if (x == root)
            root = nParent;
        x->moveDown(nParent);
        x->right = nParent->left;
        if (nParent->left != NULL)
            nParent->left->parent = x;
        nParent->left = x;
    }

    void rightRotate(Node *x){
        Node *nParent = x->left;
        if (x == root)
            root = nParent;

        x->moveDown(nParent);
        x->left = nParent->right;
        if (nParent->right != NULL)
            nParent->right->parent = x;
        nParent->right = x;
    }

    void swapColors(Node *x1, Node *x2){
        COLOR temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(Node *u, Node *v){
        point temppt = u->pt;
        u->pt = v->pt;
        v->pt = temppt;
    }

    void fixRedRed(Node *x){
        if (x == root){
            x->color = BLACK;
            return;
        }
        Node *parent = x->parent, *grandparent = parent->parent,
             *uncle = x->uncle();

        if (parent->color != BLACK){
            if (uncle != NULL && uncle->color == RED){
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                fixRedRed(grandparent);
            }
            else{
                // Else perform LR, LL, RL, RR
                if (parent->isOnLeft()){
                    if (x->isOnLeft()){
                        // for left right
                        swapColors(parent, grandparent);
                    }
                    else{
                        leftRotate(parent);
                        swapColors(x, grandparent);
                    }
                    // for left left and left right
                    rightRotate(grandparent);
                }
                else{
                    if (x->isOnLeft()){
                        // for right left
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    }
                    else{
                        swapColors(parent, grandparent);
                    }
                    // for right right and right left
                    leftRotate(grandparent);
                }
            }
        }
    }

    // find node that do not have a left child in the subtree of the given node
    Node *successor(Node *x){
        Node *temp = x;
        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    // find node that replaces a deleted node in BST
    Node *BSTreplace(Node *x){
        // when node have 2 children
        if (x->left != NULL and x->right != NULL)
            return successor(x->right);

        // when leaf
        if (x->left == NULL and x->right == NULL)
            return NULL;

        // when single child
        if (x->left != NULL)
            return x->left;
        else
            return x->right;
    }

    // deletes the given node
    void deleteNode(Node *v){
        Node *u = BSTreplace(v);
        // True when u and v are both black
        bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
        Node *parent = v->parent;
        if (u == NULL){
            // u is NULL therefore v is leaf
            if (v == root){
                // v is root, making root null
                root = NULL;
            }
            else{
                if (uvBlack){
                    // u and v both black
                    // v is leaf, fix double black at v
                    fixDoubleBlack(v);
                }
                else{
                    // u or v is red
                    if (v->sibling() != NULL)
                        // sibling is not null, make it red"
                        v->sibling()->color = RED;
                }

                // delete v from the tree
                if (v->isOnLeft()){
                    parent->left = NULL;
                }
                else{
                    parent->right = NULL;
                }
            }
            delete v;
            return;
        }
        if (v->left == NULL or v->right == NULL)
        {
            // v has 1 child
            if (v == root){
                // v is root, assign the value of u to v, and delete u
                v->pt.x = u->pt.x;
                v->pt.y == u->pt.y;
                v->left = v->right = NULL;
                delete u;
            }
            else{
                // Detach v from tree and move u up
                if (v->isOnLeft()){
                    parent->left = u;
                }
                else{
                    parent->right = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack){
                    // u and v both black, fix double black at u
                    fixDoubleBlack(u);
                }
                else{
                    // u or v red, color u black
                    u->color = BLACK;
                }
            }
            return;
        }
        // v has 2 children, swap values with successor and recurse
        swapValues(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack(Node *x){
        if (x == root)
            // Reached root
            return;

        Node *sibling = x->sibling(), *parent = x->parent;
        if (sibling == NULL){
            // No sibiling, double black pushed up
            fixDoubleBlack(parent);
        }
        else{
            if (sibling->color == RED){
                // Sibling red
                parent->color = RED;
                sibling->color = BLACK;
                if (sibling->isOnLeft()){
                    // left case
                    rightRotate(parent);
                }
                else{
                    // right case
                    leftRotate(parent);
                }
                fixDoubleBlack(x);
            }
            else{
                // Sibling black
                if (sibling->hasRedChild()){
                    // at least 1 red children
                    if (sibling->left != NULL and sibling->left->color == RED){
                        if (sibling->isOnLeft()){
                            // left left
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        }
                        else{
                            // right left
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    }
                    else{
                        if (sibling->isOnLeft()){
                            // left right
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        }
                        else{
                            // right right
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = BLACK;
                }
                else{
                    // 2 black children
                    sibling->color = RED;
                    if (parent->color == BLACK)
                        fixDoubleBlack(parent);
                    else
                        parent->color = BLACK;
                }
            }
        }
    }
    // prints level order for given node
    void levelOrder(Node *x){
        if (x == NULL)
            return;
        queue<Node *> q;
        Node *curr;
        q.push(x);
        while (!q.empty()){
            curr = q.front();
            q.pop();
            cout << curr->pt.x << " " << curr->pt.y << endl;
            if (curr->left != NULL)
                q.push(curr->left);
            if (curr->right != NULL)
                q.push(curr->right);
        }
    }

public:
    RBTree() { root = NULL; }
    Node *getRoot() { return root; }
    Node *search(int x, int y){
        Node *temp = root;
        while (temp != NULL){
            if (x < temp->pt.x){
                if (temp->left == NULL)
                    break;
                else
                    temp = temp->left;
            }
            else if (x == temp->pt.x and y == temp->pt.y){
                break;
            }
            else{
                if (temp->right == NULL)
                    break;
                else
                    temp = temp->right;
            }
        }
        return temp;
    }
    void insert(int x, int y){
        Node *newNode = new Node(x, y);
        if (root == NULL){
            // simply insert value at root of block clor
            newNode->color = BLACK;
            root = newNode;
        }
        else{
            Node *temp = search(x, y);
            if (temp->pt.x == x and temp->pt.y == y){
                // return if value already exists
                return;
            }
            newNode->parent = temp;
            if (x < temp->pt.x)
                temp->left = newNode;
            else
                temp->right = newNode;
            // fix red red voilaton if exists
            fixRedRed(newNode);
        }
    }

    void deleteByVal(int x, int y){
        if (root == NULL)
            return;
        Node *v = search(x, y), *u;
        deleteNode(v);
    }
    // void printLevelOrder(){
    //     cout << "Level order: " << endl;
    //     if (root == NULL)
    //         cout << "Tree is empty" << endl;
    //     else
    //         levelOrder(root);
    //     cout << endl;
    // }
    void inorder(Node *x){
        if (x == NULL)
            return;
        inorder(x->left);
        cout << x->pt.x << " " << x->pt.y << endl;
        inorder(x->right);
    }
    void printInOrder(){
        cout << "Inorder: " << endl;
        if (root == NULL)
            cout << "Tree is empty" << endl;
        else
            inorder(root);
        cout << endl;
    }
};
void inorder(Node *x){
    if (x == NULL)
        return;
    inorder(x->left);
    cout << x->pt.x << " " << x->pt.y << endl;
    inorder(x->right);
}
void printInOrderoutsideclass(Node *root){
    cout << "Inorder: " << endl;
    if (root == NULL)
        cout << "Tree is empty" << endl;
    else
        inorder(root);
    cout << endl;
}
double distance(int x, int y, double cx, double cy){
    double dx = cx - x;
    double dy = cy - y;
    return sqrt(dx * dx + dy * dy);
}
struct Cluster{
    RBTree tree;
    int sumx;
    int sumy;
    int Ele;
    Cluster(){}
    Cluster(int x,int y){
        sumx=x;sumy=y;
    }
};
double minimum(double x, double y){
    return min(x,y);
}