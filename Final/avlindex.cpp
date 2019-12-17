//David Hoffman

//Kyle Kolodziej revised 12/8/19

#include "avlindex.h"
#include <iostream>

using namespace std;

AVLIndex::AVLIndex()
{

}

AVLIndex::~AVLIndex() {
    avlTree.makeEmpty();
      //makes the tree logically empty
    // avlTree.~AVL();
      //frees up memory
}

void AVLIndex::insert(const IndexWord& x) {
    avlTree.insert(x);
}

void AVLIndex::print() {
    avlTree.print();
}

IndexWord& AVLIndex::find(IndexWord &x)
{
   return avlTree.findWord(x);
}

AVL<IndexWord> & AVLIndex::returnAVLTree()
{
    return avlTree;
}

bool AVLIndex::contains(const IndexWord &x) {
    return avlTree.contains(x);
}

/*bool AVLIndex::contains(const string &x)
{
    return avlTree.contains(x);
}*/

//class provides avl definitions for abstract index classes
