/* Creator of file: Kyle Kolodziej
 * Last updated: December 18th, 2019
 *
 * DESCRIPTION OF INDEX:
 *
 * Index is the parent class to both AVLIndex and HashIndex
 * Index is a purely virtual function, containing only abstract methods
 * Class User will prompt the user to select which data structure they
 * Want to load the parsed data iinto (Hash Table or AVL Tree)
 *
 */

#ifndef INDEX_H
#define INDEX_H
#include "indexword.h"
#include <iostream>
#include <string>

using namespace std;

class Index {
public:
    virtual ~Index() = default;
    virtual void insert(const IndexWord &x) = 0;
    virtual void print() = 0;
    virtual bool contains(const IndexWord &x) = 0;
    virtual const IndexWord& find(const IndexWord & x) =0;
    virtual void save(ostream&) = 0;
    virtual void setStats(int numOpinions, double numWords) =0;
    virtual void getStats() =0;

private:
    //Do i need these?
    //Get top 50 words function?
    string s;
    int docID;
    int docFreq;
    Index* root;
};

#endif // INDEX_H
