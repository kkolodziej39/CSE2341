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

const IndexWord &HashIndex::find(const IndexWord &x)
{
    //return hashTable.find
}

void HashIndex::save(ostream & out)
{
    //avlTree.save(out);
}

void HashIndex::getStats()
{
    /*double avgWordOpinion = wordCount/opinionCount;
    cout << "Total number of unique words indexed: " << avlTree.getNumElements() << endl;
    cout << "Number of opinions indexed: " << avlTree.getNumOpinions() << endl;
    cout << "Average number of words indexed per opinion: ";
    printf("%.2f\n", avgWordOpinion);
    //cout << "Top 50 most frequent words: " << endl;*/
}

void HashIndex::setStats(int numOpinions, double numWords)
{
    //opinionCount = numOpinions;
    //wordCount = numWords;
}



//class provides hash definitions for abstract index classes
