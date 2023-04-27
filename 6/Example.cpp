#include"implement.cpp"
int main(){
    BST b;
    vector<int>in={2,3,4,5,6,7};
    vector<int>post={3,2,4,6,7,5};
    b.insert(in,post);
    b.inOrder();
    cout<<endl;
    b.deleteInBST(5);
    b.inOrder();
    cout<<endl;
    cout<<"is it a BST ? "<<b.isBST()<<endl;
    cout<<"height"<<b.height()<<endl;
    cout<<"diameter"<<b.diameter()<<endl;
    cout<<"Kth smallest"<<b.KthSmallest(3)<<endl;
    cout<<"successor"<<b.successor(6)<<endl;
    cout<<"predecessor"<<b.predecessor(6)<<endl;
    cout<<"LCA"<<b.LeastCommonAncestor(2,7)->val<<endl;
    return 0;
}