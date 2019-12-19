//Kyle Kolodziej
//Updated 12/8/19
#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>
#include <iostream>
using namespace std;

class Document
{
public:
    Document();
    ~Document();
    Document(string & i, string & t, string &u, string & p); //Constructing with the id as a param
    string& getDocID();
    int getDocCount();
    void increaseCount();
    void printDocument();
    string& getTitle();
    string& getURL();
    Document& operator=(const Document &input);
    void addHTML(string &);
    void printHTML();
    string & getPreview();
    void printPreview();
    void printQueryDoc();

private:
    int count;
    string documentID;
    string title;
    string url;
    string preview;
    //any other info from doc?
};

#endif // DOCUMENT_H
