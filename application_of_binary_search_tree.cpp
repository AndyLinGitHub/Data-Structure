#include <iostream>
#include <utility>
using namespace std;

template <class K, class E> class BinarySearchTree; //forward declaration, K:key E:element

template <class T> class TreeNode{
    template <class K, class E>
    friend class BinarySearchTree;
public:
    TreeNode(T t){
        data = t;
        leftchild = 0;
        rightchild = 0;
    }
private:
    T data;
    TreeNode <T> *leftchild;
    TreeNode <T> *rightchild;
};

template <class K, class E> class BinarySearchTree{
public:
    BinarySearchTree(){
        root = 0;
    }
    pair<K, E>* Get(const K& k);
    pair<K, E>* Get(TreeNode<pair<K,E>> *p, const K& k);
    void InsertTreeNode(const K& k, const E& e);
    void DeleteTreeNode(const K& k);
    void Print(TreeNode<pair<K, E>> *tempPtr, int n);
    void Print(int n){
        Print(root, n);
    };

private:
    TreeNode <pair<K, E>> *root;
};

template <class K, class E>
pair<K, E>* BinarySearchTree<K, E> ::Get(const K &k) {
    return Get(root, k);
}

template <class K, class E>
pair<K, E>* BinarySearchTree<K, E> ::Get(TreeNode <pair<K,E>> *p, const K &k){
    if (!p) return NULL;
    if (k < p -> data.first) return Get(p -> leftchild, k);
    if (k > p -> data.first) return Get(p -> rightchild, k);
    return &(p -> data);
}

template <class K, class E>
void BinarySearchTree<K, E> ::InsertTreeNode(const K &k, const E &e) {
    pair<K, E> tempPair(k, e);
    TreeNode <pair<K,E>> *tempPtr = root;
    if (!root) root = new TreeNode<pair<K, E>>(tempPair);
    else{
        while (true){
            if (k < tempPtr -> data.first) {
                if (tempPtr -> leftchild == 0) {
                    tempPtr -> leftchild = new TreeNode<pair<K, E>>(tempPair);
                    break;
                }
                else tempPtr = tempPtr -> leftchild;
            }
            else if (k > tempPtr -> data.first) {
                if (tempPtr -> rightchild == 0) {
                    tempPtr -> rightchild = new TreeNode<pair<K, E>>(tempPair);
                    break;
                }
                else tempPtr = tempPtr -> rightchild;
            }
            else return;
        }

    }

}

template <class K, class E>
void BinarySearchTree<K, E> ::DeleteTreeNode(const K &k) {
    if(Get(k)) {
        TreeNode <pair<K,E>> *tempPtr = root;
        TreeNode <pair<K,E>> *CurrentNode = root;
        int side = 0; //1 = left   2 = right
        while (true){
            if (k < CurrentNode -> data.first) {
                tempPtr = CurrentNode;
                CurrentNode = CurrentNode -> leftchild;
                side = 1;
            }
            else if (k > CurrentNode -> data.first) {
                tempPtr = CurrentNode;
                CurrentNode = CurrentNode -> rightchild;
                side = 2;
            }
            else {
                if (CurrentNode -> leftchild == 0 && CurrentNode -> rightchild == 0) {
                    delete CurrentNode;
                    if (side == 0) root = 0;
                    if (side == 1) tempPtr -> leftchild = 0;
                    if (side == 2) tempPtr -> rightchild = 0;
                    break;
                }
                else if (CurrentNode -> leftchild == 0 && CurrentNode -> rightchild != 0){
                    if (side == 1) tempPtr -> leftchild = CurrentNode -> rightchild;
                    if (side == 2) tempPtr -> rightchild = CurrentNode -> rightchild;
                    if (side == 0) root = CurrentNode -> rightchild;
                    delete CurrentNode;
                    break;
                }
                else if (CurrentNode -> leftchild != 0 && CurrentNode -> rightchild == 0){
                    if (side == 1) tempPtr -> leftchild = CurrentNode -> leftchild;
                    if (side == 2) tempPtr -> rightchild = CurrentNode -> leftchild;
                    if (side == 0) root = CurrentNode -> leftchild;
                    delete CurrentNode;
                    break;
                }
                else if (CurrentNode -> leftchild != 0 && CurrentNode -> rightchild != 0){
                    if (CurrentNode -> rightchild -> leftchild == 0){
                            CurrentNode -> rightchild -> leftchild =  CurrentNode -> leftchild;
                            if (side == 1) tempPtr -> leftchild = CurrentNode -> rightchild;
                            if (side == 2) tempPtr -> rightchild = CurrentNode -> rightchild;
                            delete CurrentNode;
                            break;
                    }
                    else {
                        CurrentNode = CurrentNode -> rightchild;
                        while(true){
                            if (CurrentNode -> leftchild == 0) break;
                            CurrentNode = CurrentNode -> leftchild;
                        }
                        if (side == 1) {
                            CurrentNode -> leftchild = tempPtr -> leftchild -> leftchild;
                            tempPtr -> leftchild = CurrentNode;
                            delete tempPtr -> leftchild;
                            break;
                        }
                        if (side == 2) {
                            CurrentNode -> leftchild = tempPtr -> rightchild -> leftchild;
                            tempPtr -> rightchild = CurrentNode;
                            delete tempPtr -> rightchild;
                            break;
                        }
                        if  (side == 0) {
                            CurrentNode -> leftchild = tempPtr -> leftchild;
                            root = CurrentNode;
                            break;
                        }
                    }
                }
            }
        }
    }
}

template <class K, class E>
void BinarySearchTree<K, E> ::Print(TreeNode<pair<K, E>> *tempPtr, int n){
    if (!tempPtr) return;
    switch (n){
        case 1:
            Print(tempPtr->leftchild, 1);
            cout << tempPtr->data.first << " ";
            Print(tempPtr->rightchild, 1);
            break;
        case 2:
            Print(tempPtr->leftchild, 2);
            if (tempPtr -> leftchild != 0) cout << tempPtr -> leftchild -> data .first << " ";
            else cout << 0 << " ";
            Print(tempPtr->rightchild, 2);
            break;
        case 3:
            Print(tempPtr->leftchild, 3);
            if (tempPtr -> rightchild != 0) cout << tempPtr -> rightchild -> data .first << " ";
            else cout << 0 << " ";
            Print(tempPtr->rightchild, 3);
            break;
        default:
            ;

    }
}

int main(){
    BinarySearchTree<int, int> BST;
    int e;
    while (true) {
        cin >> e;
        if (e == -1) break;
        if (BST.Get(e)) BST.DeleteTreeNode(e);
        else BST.InsertTreeNode(e, e);
    }
    cout << "node: ";
    BST.Print(1);
    cout << endl;
    cout << "left: ";
    BST.Print(2);
    cout << endl;
    cout << "right: ";
    BST.Print(3);
    return 0;
}
