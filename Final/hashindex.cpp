//David Hoffman
//Kyle Kolodziej revised 12/8/19

#include "hashindex.h"
#include <iostream>

using namespace std;

HashIndex::HashIndex()
{

}

HashIndex::~HashIndex()
{

}

void HashIndex::insert(const IndexWord& x) {
    //IndexWord temp = x;
    //int index = temp.getWordVal();
    //string temp2 = temp.getIndexWord();
    cout << "in index insert" << endl;
    hashTable.insertHash(x);
    //hashTable.insertNode(index, temp);
}

void HashIndex::print() {
    hashTable.display();
}

bool HashIndex::contains(const IndexWord &x) {
   // return hashTable.contains(x);
}

IndexWord& HashIndex::find(IndexWord &x)
{
    //return hashTable.find
}

//class provides hash definitions for abstract index classes
