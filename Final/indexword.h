//Kyle Kolodziej
//Updated 12/8

#ifndef INDEXWORD_H
#define INDEXWORD_H

#include "document.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class IndexWord
{
public:
    IndexWord();
    IndexWord(string & t);
    IndexWord(Document & documentObj);
    void addDocHTML(string &, int);
    IndexWord(string & a, string & b, string &t, string &u, string &p); //a is the word and b is the doc id
    ~IndexWord();
    void setIndexWord(string&);
      //sets word object
    string& getIndexWord();
    vector<Document>& getDocVect();
    int getWordVal();
    IndexWord& operator=(const IndexWord & input);
    bool operator==(const IndexWord & input);
    bool operator==(const string & input);
    bool operator<(const IndexWord & input);
    bool operator<(const string & input);
    bool operator>(const IndexWord & input);
    bool operator>(const string & input);
    bool alreadyContainsID(const string & passingID);
    bool alreadyContainsID(IndexWord & input);
    IndexWord operator+(const IndexWord & input);
    void addDocObj(Document & addingDoc);
    Document & getDocObject(int index);
    void printIndexWord();
    friend std::ostream& operator << (std::ostream&, IndexWord&);
    void sortByCount();
    void printTopThree();
    void sortByDocID();
    int getIndexWordSize();
    void getDocPreviewAt(int index);
    int getTotalFreq();



private:
    string word;
    vector<Document> docVect;
    int totalFreq;
};

#endif // INDEXWORD_H
