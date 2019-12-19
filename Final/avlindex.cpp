//David Hoffman

//Kyle Kolodziej revised 12/8/19

#include "avlindex.h"
#include <iostream>

using namespace std;

AVLIndex::AVLIndex()
{
    wordCount = 0;
    opinionCount = 0;
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

const IndexWord& AVLIndex::find(const IndexWord &x)
{
  // return avlTree.findWord(x);
    return avlTree.find(x);
}

AVL<IndexWord> AVLIndex::returnAVLTree()
{
    return avlTree;
}

bool AVLIndex::contains(const IndexWord &x) {
    return avlTree.contains(x);
}

void AVLIndex::save(ostream & out)
{
    out << "Total number of unique words indexed: " << avlTree.getNumElements() << endl << endl;
    avlTree.save(out);
}

void AVLIndex::getStats()
{
    double avgWordOpinion = wordCount/opinionCount;
    cout << "Total number of unique words indexed: " << avlTree.getNumElements() << endl;
    cout << "Number of opinions indexed: " << opinionCount << endl;
    cout << "Average number of words indexed per opinion: ";
    printf("%.2f\n", avgWordOpinion);
    //cout << "Top 50 most frequent words: " << endl;
}

void AVLIndex::setStats(int numOpinions, double numWords)
{
    opinionCount = numOpinions;
    wordCount = numWords;
}

/*bool AVLIndex::contains(const string &x)
{
    return avlTree.contains(x);
}*/
