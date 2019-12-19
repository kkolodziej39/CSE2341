/* Creator of file: Kyle Kolodziej
 * Last updated: December 18th, 2019
 *
 * DESCRIPTION OF AVL:
 *
 * Writing a templated wrapper class for AVL
 * Friend class of AVLNode.h
 * AVLNode is also written using templated parameters
 * Each node is a word from the
 * Nodes are compared to each other by the integer value of the word
 */

#ifndef AVL_H
#define AVL_H
#include "avlnode.h"
#include "index.h"
#include "indexword.h"
#include <iostream>

using namespace std;

template <typename T>
class AVL{
private:
    AVLNode<T>* root;
    double numElements = 0;
    /* Could use an int for numElements
     * Opted for the use of type double as
     * Dividing variable for statistical measure
     * And thought was going to be used with another integer
     */

public:
    AVL() : root(nullptr) {} //Default constructor
    ~AVL(); //Destructor
    const T& findMin() const;
    AVLNode<T>* findMin(AVLNode<T>*) const; //Return pointer to smallest element in tree. Used for recursive call
    AVLNode<T>* findMax(AVLNode<T>* t) const; //Return pointer to largest element in tree. Used for recursive call
    const T& findMax() const; //Return object of biggest element in the tree
    bool contains(const T &x, AVLNode<T>* t) const; //Check if the tree contains X (parameter). Used for recursive call
    bool contains(const T &x) const; //Returns true if element is in tree. Check if the tree contains X (parameter)
    bool isEmpty() const; //Return true if the tree is empty, false otherwise
    void makeEmpty(AVLNode<T>* &t); //Used for recursive function call in making the avl tree empty
    void makeEmpty(); //Called in destructor to remove all nodes from tree
    void insert(const T &x); //Inserting an element into the tree
    void insert(const T &x, AVLNode<T>* &t); //Insert element into tree with recursive function call
    void rotateWithLeftChild(AVLNode<T>* &x); //Called when AVL Tree becomes unbalanced. Unbalanced element's left child causing height difference > 1
    void rotateWithRightChild(AVLNode<T>* &x); //Called when AVL Tree becomes unbalanced. Unbalanced element's right child causing height difference > 1
    void doubleWithLeftChild(AVLNode<T>* &x); //Called when AVL Tree becomes unbalanced. Unbalanced element's left child (and right/left) causing height difference > 1
    void doubleWithRightChild(AVLNode<T>* &x); //Called when AVL Tree becomes unbalanced. Unbalanced element's right child (and right/left) causing height difference > 1
    int height(AVLNode<T>* t) const; //Get height of node
    int max(int lhs, int rhs) const; //Determine if left or right is greater
    double getNumElements(); //Return total number of elements (# of unique words) in tree
    void save(ostream&); //Used to save a persistent index to an Output File
    void saveTree(ostream & out, AVLNode<T>* t) const; //Used to save a persistent index to an Output File (local disk)
    AVLNode<T>* clone(AVLNode<T> *t) const; //? Making copy of node or whole tree?
    void print() const; //Printing the tree's elements using Preorder Traversal
    void printTree(AVLNode<T>* t) const;  //Printing the tree's elements using Preorder Traversal
    const T & getElement(AVLNode<T> * p); //Return the element at a specific node
    const AVL<T> & operator=(const AVL<T> & rhs); //Overloading the assignment operator
    const T & find(const T & x); //Finding element passed in as a parameter
    AVLNode<T>* find(const T & x, AVLNode<T> * t); //Used for recursive call of finding an element in tree
};

template <typename T>
AVL<T>::~AVL()
{
    makeEmpty();
}

template <typename T>
double AVL<T>::getNumElements()
{
    return numElements;
}

template <typename T>
void AVL<T>::save(ostream & out)
{
    saveTree(out, root);
}

template <typename T>
void AVL<T>::saveTree(ostream & out, AVLNode<T>* t) const {
    /* Print total number of unique words
     * Print each word and corresponding ID's and frequency
     *
     * Note:
     * Also printing # of unique words and # of opinions
     * This is being done in Index class
     */
   // out << "Total number of unique words indexed: " << numElements << endl;

    if(t != nullptr)
    {
        saveTree(out, t->left);
        out << t->element << endl;
        saveTree(out, t->right);
    }
}

template <typename T>
AVLNode<T>* AVL<T>::clone(AVLNode<T>* t) const {
    if(t == nullptr)
    {
        return nullptr;
    }

    else
    {
        return new AVLNode<T>(t->element, clone(t->left), clone(t->right), t->height);
    }
}

template <typename T>
const T & AVL<T>::getElement(AVLNode<T> *p)
{
    if(p == nullptr)
    {
        throw "Element is null!";

    }
    else {
        return p->element;
    }
}

template <typename T>
const T& AVL<T>::findMin() const {
    if(isEmpty())
    {
        //Throws an error if the AVL Tree is empty
        throw "Error! AVL Tree is empty!";
    }
    return getElement(findMin(root));
}

template <typename T>
const T& AVL<T>::findMax() const {
    if(isEmpty())
    {
        //Throws an error if the AVL Tree is empty
        throw "Error! AVL Tree is empty!";
    }

    return getElement(findMax(root));
}

template <typename T>
AVLNode<T>* AVL<T>:: findMin(AVLNode<T>* t) const {
    if(t == nullptr)
    {
        //If no elements, just returns parameter t
        return t;
    }

    while(t->left != nullptr)
    {
        //Keep decrementing to the left until there are no
        //More elements to the left (the min)
        t = t->left;
    }
    return t;
}

template <typename T>
AVLNode<T>* AVL<T>::findMax(AVLNode<T>* t) const {
    if(t == nullptr)
    {
        return t;
    }

    while(t->right != nullptr)
    {
        //Keep decrementing to the right until there are no
        //More elements to the right (the max)
        t = t->right;
    }
    return t;
}

template <typename T>
bool AVL<T>::contains(const T &x) const {
    return contains(x, root);
}

template <typename T>
bool AVL<T>::contains(const T &x, AVLNode<T>* t) const {
    if(t == nullptr) //Returns false if tree is empty
    {
        return false;
    }
    else if(t->element > x) //T > x so need to go to the left of T
    {
        return contains(x, t->left);
    }
    else if(t->element < x) //T < x so need to go to the right of T
    {
        return contains(x, t->right);
    }
    else  //T = X, return true
    {
        return true;
    }
}

template <typename T>
bool AVL<T>::isEmpty() const {
    return root == nullptr;
}

template <typename T>
void AVL<T>::makeEmpty()
{ //Delete the elements and set private date member to 0
    makeEmpty(root);
    numElements = 0;
}

template <typename T>
void AVL<T>::makeEmpty(AVLNode<T>* &t)
{
    if(t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template <typename T>
void AVL<T>::insert(const T &x)
{
    insert(x, root);
}

template <typename T>
void AVL<T>::insert(const T &x, AVLNode<T>* &t)
{
    if(t == nullptr)  //If tree is empty
    {
        t = new AVLNode<T>(x,nullptr,nullptr);
        numElements++;
    }
    else if(t->element > x) //Need to go the left of T as T > X
    {
        insert(x, t->left);
        if(height(t->left) - height(t->right) == 2) //Check if node is balanced
        {
            if(t->left->element > x)
            {
                rotateWithLeftChild(t);
                numElements++;
            }
            else
            {
                doubleWithLeftChild(t);
                numElements++;
            }  //case 2
        }
    }
    else if(t->element < x)
    {
        insert(x, t->right);
        if(height(t->right) - height(t->left) == 2) {
            if(t->right->element < x) {
                rotateWithRightChild(t);
                numElements++;
            }  //case 4

            else {
                doubleWithRightChild(t);
                numElements++;
            }  //case 3
        }
    }
    else {//Duplicate
       t->element = t->element + x;
    }

    t->height = max(height(t->left), height(t->right)) + 1;
}

template <typename T>
void AVL<T>::rotateWithLeftChild(AVLNode<T>* &k2) {
    AVLNode<T>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(height(k2->left), height(k2->right) ) + 1;
    k1->height = max(height(k1->left), k2->height ) + 1;
    k2 = k1;
}

template <typename T>
void AVL<T>::rotateWithRightChild(AVLNode<T>* &k1){
    AVLNode<T>* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height ) + 1;
    k1 = k2;
}

template <typename T>
void AVL<T>::doubleWithLeftChild(AVLNode<T>* &k3){
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <typename T>
void AVL<T>::doubleWithRightChild(AVLNode<T>* &k3){
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

template <typename T>
int AVL<T>::height(AVLNode<T>* t) const { //Returns -1 if no height, else returns the height
    if(t == nullptr)
    {
        return -1;
    }

    else {
        return t->height;
    }
}

template <typename T>
int AVL<T>::max(int lhs, int rhs) const {
    return lhs > rhs ? lhs : rhs; //if lhs> rhs, returns lhs. Else returns rhs
}

template <typename T>
const T & AVL<T>::find(const T & x)
{
    return getElement(find(x, root));
}

template <typename T>
const AVL<T>& AVL<T>::operator=(const AVL<T>& rhs) {
    if(this != &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
    }

    return *this;
}

template <typename T>
void AVL<T>::print() const {
    cout << "----------PRINTING AVL TREE----------" << endl << endl;
    if(isEmpty())
    {
        cout << "The tree is Empty" << endl;
    }
    else
    {
        printTree(root);
    }
}

template <typename T>
void AVL<T>::printTree(AVLNode<T>* t) const { //Preorder traversal printing of AVL Tree
    if(t != nullptr)
    {
        printTree(t->left);
        cout << t->element << endl; //Make sure to override the ostream << operator of element type
        printTree(t->right);
    }
}

template <typename T>
AVLNode<T>* AVL<T>::find(const T & x, AVLNode<T> * t)
{
    while(t!= nullptr)
    {
        if(t->element>x)
        {
            t = t->left;
        }
        else if(t->element < x)
        {
            t = t->right;
        }
        else {
            return  t;
        }
    }

    throw "Element doesn't exist in tree!"; //If no match throwing this message
}

#endif // AVL_H
