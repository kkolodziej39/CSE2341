#ifndef AVLNODE_H
#define AVLNODE_H
#include <iostream>
#include <string>
#include "indexword.h"

using namespace std;

template <typename T>
class AVLNode {
public:
   template <class U> friend class AVL;


   AVLNode(const T& theElement, AVLNode<T>* lt, AVLNode<T>* rt, int h = 0) : element(theElement), left(lt), right(rt), height(h) {}
   AVLNode(const T& theElement, int index, AVLNode<T>* lt, AVLNode<T>* rt, int h = 0) : element(theElement), indexNum(index), left(lt), right(rt), height(h) {}

private:
   IndexWord element;
   T indexNum;
   AVLNode<T> * left;
   AVLNode<T> * right;
   int height;
};

#endif // AVLNODE_H
