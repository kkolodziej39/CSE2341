//David Hoffman and Kyle Kolodziej
//12/8/19
#ifndef HASHINDEX_H
#define HASHINDEX_H
#include "index.h"
#include "hash.h"
#include "indexword.h"
#include <iostream>
//#include <unordered_map>

using namespace std;

class HashIndex: public Index {
private:
    Hash<int, IndexWord> hashTable;

public:
    HashIndex();
      //default constructor
    ~HashIndex();
      //destructor
    void insert(const IndexWord &x);
      //give insert definition for hash
    void print();
      //give print definition for hash
    bool contains(const IndexWord &x);
      //give contains definition for hash
    IndexWord& find(IndexWord & x);
};

#endif // HASHINDEX_H
