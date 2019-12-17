//Kyle Kolodziej
//Updated 12/8
#include "indexword.h"

IndexWord::IndexWord()
{
    word = "NO STRING INPUT";
}

IndexWord::IndexWord(string & t)
{
    word = t;
}

int IndexWord::getWordVal()
{
    int val = atoi(word.c_str());
    return val;
}

IndexWord::~IndexWord()
{
    //Destructor
}

IndexWord::IndexWord(string &a, string & b, string &t, string&u)
{
    //a is the word and b is the doc id
    word = a;
    Document docObj(b, t, u);
    docVect.push_back(docObj);
}

vector<Document>& IndexWord::getDocVect() {
    return docVect;
}

string& IndexWord::getIndexWord()
{
    return word;
}

void IndexWord::setIndexWord(string &x) {
    word = x;
}

IndexWord& IndexWord::operator=(const IndexWord &input) //In case assignment operator is called and needed elsewhere
{

   word = input.word;
   docVect = input.docVect;
   return *this;
}

bool IndexWord::operator==(const IndexWord &input)
{

    IndexWord temp = input;
    if(word == input.word)
    {
        return true;
        //return true; //If strings and vects are the same, the two objects are the same
    }

    return false;
}

bool IndexWord::operator==(const string &input)
{

    if(word == input)
    {
        return true;
        //return true; //If strings and vects are the same, the two objects are the same
    }

    return false;
}

bool IndexWord::operator<(const IndexWord &input)
{
    if(word < input.word) //Comparing the strings
    {
        return true;
    }
    return false;
}

bool IndexWord::operator>(const IndexWord &input)
{
    if(word > input.word) //Comparing the strings
    {
        return true;
    }
    return false;
}

bool IndexWord::operator<(const string &input)
{
    if(word < input) //Comparing the strings
    {
        return true;
    }
    return false;
}


bool IndexWord::operator>(const string &input)
{
    if(word > input) //Comparing the strings
    {
        return true;
    }
    return false;
}

bool IndexWord::alreadyContainsID(const string & passingID) //Taking the id as a parameter
{
    //Function returns true if docID of input is the same as the current IndexWord obj
    for(int i = 0; i < docVect.size(); i++)
    {
        if(passingID == docVect[i].getDocID())
        {
            return true;
        }
    }
    return false;
}

bool IndexWord::alreadyContainsID(IndexWord& passingID) //Taking IndexWord as a param this time, should only have one document
{
    //Function returns true if docID of input is the same as the current IndexWord obj
    for(int i = 0; i < docVect.size(); i++)
    {
        if(passingID.docVect[0].getDocID() == docVect[i].getDocID())
        {
            return true;
        }
    }
    return false;
}

IndexWord IndexWord::operator+(const IndexWord &input)
{
    IndexWord newObj = input;
    if(alreadyContainsID(newObj))
    {
        string inputID = newObj.docVect[0].getDocID();
        //int addingCount = newObj.docVect[0].getDocCount();
        for(int i = 0; i < docVect.size(); i ++)
        {
            if(inputID == docVect[i].getDocID())
            {
                docVect[i].increaseCount();
                return *this;
            }
        }
    }
    else {
        Document newDocObj(newObj.docVect[0].getDocID(), newObj.docVect[0].getTitle(), newObj.docVect[0].getURL());
        docVect.push_back(newDocObj);
        return *this;
    }
}

void IndexWord::addDocHTML(string &x, int index)
{
    docVect[index].addHTML(x);
}

void IndexWord::printIndexWord()
{
    //cout << "Word is: " << getIndexWord() << endl;
   // cout << "Word is (2): " << word << endl;
    //cout << "Entering doc vect for word (" << word << ")" << endl;
    for(int i = 0; i < docVect.size(); i ++)
    {
        docVect[i].printDocument();
    }


}

std::ostream& operator << (std::ostream&p, IndexWord&a)
{
    p << "Word is: " << a.word << endl;
    p << "Doc vect contains..." << endl;
    for(int i = 0; i < a.docVect.size(); i ++)
    {
        p << "Case: " << a.docVect[i].getTitle() << endl;
        p << "ID: " << a.docVect[i].getDocID() << " (count: " << a.docVect[i].getDocCount() << ")" << endl;
        p << "URL: " << a.docVect[i].getURL() << endl;
    }

    return p;
}

void IndexWord::sortByCount()
{
    //Source for Bubble Sort code is https://www.geeksforgeeks.org/bubble-sort/
    int i, j;
    bool swapped;
    for (i = 0; i < this->docVect.size()-1; i++)
    {
      swapped = false;
      for (j = 0; j < this->docVect.size()-i-1; j++)
      {
         if (this->docVect[j].getDocCount() > this->docVect[j+1].getDocCount())
         {
            Document temp = this->docVect[j];
            this->docVect[j] = this->docVect[j+1];
            this->docVect[j+1] = temp;
            swapped = true;
         }
      }
      // IF no two elements were swapped by inner loop, then break
      if (swapped == false)
         break;
    }
}

Document& IndexWord::getDocObject(int index)
{
    if(index > docVect.size())
    {
        throw "Invalid index error! No document object exists at that spot!";
    }
    else {
        return docVect[index];
    }
}




