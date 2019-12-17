//Kyle Kolodziej: using library from git hub
//Updated 12/8

#ifndef DOCPARSE_H
#define DOCPARSE_H
#include "stemming.h"
#include "indexword.h"
#include "avl.h"
#include "hash.h"
#include "index.h"
#include "avlindex.h"
#include "hashindex.h"
//#include <myhtml/api.h>
//#include <myhtml/api.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
class DocParse
{
public:
    DocParse();
    ~DocParse();
    void readDoc(char *argv[], int choice, Index * );
    void parseHTML(char * html);
    void printWords();
    void addStopWords();
    void removeStopWords(char * arr);
    void stemDocWordstoAVL(Index * );
    void stemDocWordstoHash(Index * );
    void upperToLower(string & );
    void sendToIndex();
    void formatTitle(string &);
    void getDates(string & arr);
    AVL<IndexWord>& getIndexTree();
    int getSize();
    bool invalidChar(char c);
    void stripUnicode(string & str);
      //returns indexTree

    vector<string> stemmedDocWords;
private:
    int size;
    //AVL<string> stopWords;
    //AVL<string> indexTree;
    //AvlTree<string> stopWords;
    //AVL<string> stopWords;
    vector<string> stopWords;
    vector<string> documentWords;
    //vector<string> stemmedDocWords;
    string docID;
    AVL<IndexWord> indexTree;
    string title;
    string url;
    string submissionDate;
    string decisionDate;
};

#endif // DOCPARSE_H
