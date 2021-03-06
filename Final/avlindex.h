//Kyle Kolodziej
//12/8/19
#ifndef AVLINDEX_H
#define AVLINDEX_H
#include "index.h"
#include "avl.h"
#include "indexword.h"
#include <iostream>

using namespace std;

class AVLIndex: public Index {
private:
    AVL<IndexWord> avlTree;
    int opinionCount;
    double wordCount;

public:
    AVLIndex();
      //default constructor
    ~AVLIndex();
      //destructor
    void insert(const IndexWord &x);
      //give insert definition for avl
    void print();
      //give print definition for avl
    bool contains(const IndexWord &x);
    const IndexWord& find(const IndexWord & x);
      //give contains definition for avl
    //bool contains(const string & x);
    void save(ostream&);
    void getStats();
    void setStats(int numOpinions, double numWords);
    AVL<IndexWord> returnAVLTree();
};

#endif // AVLINDEX_H
