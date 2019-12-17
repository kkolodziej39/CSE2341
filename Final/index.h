//David Hoffman
//last revision: 12/7/19
//Kyle Kolodziej: 12/8/19

#ifndef INDEX_H
#define INDEX_H
#include "indexword.h"
#include <iostream>
#include <string>

using namespace std;

class Index {
public:
    //Index() {}
      //default constructor
    virtual ~Index() = default;
    virtual void insert(const IndexWord &x) = 0;
      //store data in hash table or avl tree
   // virtual bool contains(const T &x) = 0;
    virtual void print() = 0;
      //prints index
    virtual bool contains(const IndexWord &x) = 0;
      //checks if a variable x is in the index
      virtual IndexWord& find(IndexWord & x) =0;
    //virtual bool isEmpty() const;
      //checks if index is empty
    //virtual void makeEmpty() = 0;
      //clears the index

   // virtual void print(T* t) = 0;
      //prints index
   // virtual void save(ofstream&) = 0;

    //virtual void save(ofstream&) = 0;
      //saves index to local disk

private:
    string s;
    int docID;
    int docFreq;
    Index* root;
};

#endif // INDEX_H
