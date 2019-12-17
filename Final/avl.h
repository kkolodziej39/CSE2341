//David Hoffman
//last revision 12/3/19
//Kyle Kolodziej revised 12/8

#ifndef AVL_H
#define AVL_H
#include "avlnode.h"
#include "index.h"
#include "indexword.h"
#include <iostream>

using namespace std;

template <typename T>
class AVL {
private:
    AVLNode<T>* root;
    int numElements = 0;

public:
    AVL() : root(nullptr) {}
      //default contructor
   /* AVL(const AVL<T> &rhs) : root(nullptr) {
        *this = root;
    }  //copy constructor*/
    /* AVL(const AVL<T> &rhs) : root(nullptr) {
        *this = root;
    }  //copy constructor */
    ~AVL();
      //destructor

    const T& findMin() const;
    AVLNode<T>* findMin(AVLNode<T>*) const;
      //finds the smallest element in the tree
    AVLNode<T>* findMax(AVLNode<T>* t) const;
    const T& findMax() const;
      //finds the biggest element in the tree
    bool contains(const T &x, AVLNode<T>* t) const;
    //bool contains(const T &x, AVLNode<IndexWord>* t) const;
    bool contains(const T &x) const;
      //returns true if the element is in the tree
    bool isEmpty() const;
      //returns true if the tree is empty
    void makeEmpty(AVLNode<T>* &t);
    void makeEmpty();
      //makes the tree logically empty
    void insert(const T &x);
    void insert(const T &x, AVLNode<T>* &t);
      //inserts elements into the tree
    void rotateWithLeftChild(AVLNode<T>* &x);
    void rotateWithRightChild(AVLNode<T>* &x);
    void doubleWithLeftChild(AVLNode<T>* &x);
    void doubleWithRightChild(AVLNode<T>* &x);
    T& findWord(IndexWord&, AVLNode<T>* &x);
    T& findWord(string&);
    T& findWord(IndexWord &);
    int height(AVLNode<T>* t) const;
      //returns height
    int max(int lhs, int rhs) const;
      //returns max
    int getNumElements();
      //returns the number of elements in the tree
    void save(ostream&, AVLNode<T>* &t);
      //saves tree to local disk
    AVLNode<T>* clone(AVLNode<T> *t) const;
      //clones avl tree
    const AVL& operator= (const AVL&);
      //overloaded equals operator
    void print() const;
    void printTree(AVLNode<T>* t) const;
      //prints the tree
};

template <typename T>
AVL<T>::~AVL() {
    makeEmpty();
}

template <typename T>
AVLNode<T>* AVL<T>::clone(AVLNode<T>* t) const {
    if(t == nullptr) {
        return nullptr;
    }

    else {
        return new AVLNode<T>(t->element, clone(t->left), clone(t->right), t->height);
    }
}

template <typename T>
const T& AVL<T>::findMin() const {
    if(isEmpty()) {
        return 0;
    }
    
    return findMin(root)->element;
}

template <typename T>
AVLNode<T>* AVL<T>:: findMin(AVLNode<T>* t) const {
    if(t == nullptr) {
        return nullptr;
    }
    else if(t->left == nullptr) {
        return t;
    }

    return findMin(t->left);
}

template <typename T>
AVLNode<T>* AVL<T>::findMax(AVLNode<T>* t) const {
    if(t != nullptr) {
        while(t->right != nullptr) {
            t = t->right;
        }
    }

    return t;
}

template <typename T>
bool AVL<T>::contains(const T &x) const {
    return contains(x, root);
}
/*
template <typename T>
bool AVL<T>::contains(const T &x, AVLNode<IndexWord>* t) const {
    if(t == nullptr) {
        return false;
    }  //returns false if tree is empty

    else if(x < t->element.getIndexWord()) {
        return contains(x, t->left);
    }

    else if(t->element.getIndexWord() < x) {
        return contains(x, t->right);
    }

    else {
        return true;
    }
}
*/
template <typename T>
bool AVL<T>::contains(const T &x, AVLNode<T>* t) const {
    if(t == nullptr) {
        return false;
    }  //returns false if tree is empty

    else if(t->element > x) {
        return contains(x, t->left);
    }

    else if(t->element < x) {
        return contains(x, t->right);
    }

    else {
        return true;
    }
}

template <typename T>
bool AVL<T>::isEmpty() const {
    return root == nullptr;
}

template <typename T>
void AVL<T>::makeEmpty() {
    makeEmpty(root);
}

template <typename T>
void AVL<T>::makeEmpty(AVLNode<T>* &t) {
    if(t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template <typename T>
void AVL<T>::insert(const T &x) {
    insert(x, root);
}

template <typename T>
void AVL<T>::insert(const T &x, AVLNode<T>* &t) {
    //cout << "Inserting..." << endl;
    if(t == nullptr) {
        //cout << "Node is empty" << endl;
        t = new AVLNode<T>(x,nullptr,nullptr);
        numElements++;
    }  //checks if node is empty

    else if(t->element > x) {
        insert(x, t->left);
        if(height(t->left) - height(t->right) == 2) {
            if(t->left->element > x) {
                rotateWithLeftChild(t);
            }  //case 1

            else {
                doubleWithLeftChild(t);
            }  //case 2
        }
    }
        else if(t->element < x) {
            //cout << "Node inserting is greater than" << endl;
            insert(x, t->right);
            if(height(t->right) - height(t->left) == 2) {
                if(t->right->element < x) {
                    rotateWithRightChild(t);
                }  //case 4

                else {
                    doubleWithRightChild(t);
                }  //case 3
            }
        }

        else {
           // cout << "In final else..." << endl;
            t->element = t->element + x;
        }

        t->height = max(height(t->left), height(t->right) + 1);
}

template <typename T>
void AVL<T>::rotateWithLeftChild(AVLNode<T>* &k2) {
    AVLNode<T>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template <typename T>
void AVL<T>::rotateWithRightChild(AVLNode<T>* &k2) {
    AVLNode<T>* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template <typename T>
void AVL<T>::doubleWithLeftChild(AVLNode<T>* &k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <typename T>
void AVL<T>::doubleWithRightChild(AVLNode<T>* &k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

template <typename T>
int AVL<T>::height(AVLNode<T>* t) const {
    if(t == nullptr) {
        return -1;
    }  //return -1 if null

    else {
        return t->height;
    }  //returns height if its not null
}

template <typename T>
int AVL<T>::max(int lhs, int rhs) const {
    return lhs > rhs ? lhs : rhs;
}

template <typename T>
T& AVL<T>::findWord(IndexWord& word) {
    return findWord(word, root);
}

template <typename T>
T& AVL<T>::findWord(IndexWord& word, AVLNode<T>* &t) {
    if(t == nullptr) {
        cout << "tree is empty" << endl;
    }  //returns false if tree is empty

    else if(t->element > word ) {
        return findWord(word, t->left);
    }

    else if(t->element < word) {
        return findWord(word, t->right);
    }

    else {
        return t->element;
    }
}

template <typename T>
int AVL<T>::getNumElements() {
    return numElements;
}

template <typename T>
const AVL<T>& AVL<T>::operator=(const AVL<T>& rhs) {
    if(this != &rhs) {
        makeEmpty();
        root = clone(rhs.root);
    }

    return *this;
}

template <typename T>
void AVL<T>::print() const {
    if(isEmpty()) {
        cout << "The tree is Empty" << endl;
    }

    else {
        printTree(root);
    }
}

template <typename T>
void AVL<T>::printTree(AVLNode<T>* t) const {
    if(t != nullptr) {
        printTree(t->left);
        cout << t->element << endl;
        printTree(t->right);
    }
}

#endif // AVL_H
