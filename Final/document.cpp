//Kyle Kolodziej
//Updated 12/8

#include "document.h"

Document::Document()
{
    count = 1;
}

Document::~Document()
{

}

Document::Document(string & i, string & t, string&u, string & p)
{
    count = 1;
    title = t;
    documentID = i;
    url =u;
    preview = p;
}

Document& Document::operator=(const Document &input)
{
    count = input.count;
    documentID = input.documentID;
    title = input.title;
    url = input.url;
    preview = input.preview;
    return *this;
}

string & Document::getURL()
{
    return url;
}

string& Document::getDocID()
{
    return documentID;
}

int Document::getDocCount()
{
    return count;
}

void Document::increaseCount()
{
    count++;
}

string& Document::getTitle()
{
    return title;
}

void Document::printDocument()
{
    //cout << "Document ID is: " << documentID << endl << ", Count is: " << count << ", Document title is: " << title << ", URL is: " << url << endl << endl;
    //cout << "Document ID is: " << getDocID() << endl;
    cout << "Count is: " << count << endl;
    //cout << "Count is (2): " << getDocCount() << endl;
    cout << "Document title is: " << title << endl;
    cout << "Link to Document: " << url << endl;
   // cout << "Preview:" << endl;
    //cout << htmlText;
   // string temp = htmlText.substr(0, 200);
    //cout << preview  << endl << endl;

}

void Document::printQueryDoc()
{
    cout << "Document title is: " << title << endl;
    cout << "Link to Document: " << url << endl;
    //cout << "Preview:" << endl;
    //cout << htmlText;
   // string temp = htmlText.substr(0, 200);
    //cout << preview  << endl << endl;
}

string & Document::getPreview()
{
    return preview;
}

void Document::addHTML(string & x)
{
    preview =x;
}

void Document::printPreview()
{
    cout << "Preview: " << endl << endl;
    cout << preview << endl << endl;
}
