//David Hoffman
//last revision: 12/7/19

#include "query.h"
#include "docparse.h"
#include "stemfunctionality.h"
#include "user.h"
#include "document.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

Query::Query(Index * input) {
      //default constructor
    queryIndex = input;
}

void Query::readQuery() {
    string search;

    cout << "----------SEARCH QUERY----------" << endl;
    cout << "Rules of search:" << endl;
    cout << "1. Multi-word searches must be prefixed with a boolean operator (AND,OR)" << endl;
    cout << "2. No query can have both AND and  OR" << endl;
    cout << "3. Search terms may be preceded with a NOT operator" << endl;
    cout << "Enter search: ";
    cin >> search;
      //prints menu and stores user search in a string
    cout << "search term is" << search << endl;
    userSearch.push_back(search);
    cout << "size is: " << userSearch.size() << endl;
    for(int i = 0; i < userSearch.size(); i++)
    {
        cout << "vect element: " << userSearch[i] << endl;
    }
    cout << endl;
    regSearch();
    //chooseSearch();
    //parseQuery(search);
}

void Query::parseQuery(string &search) {
    DocParse parse;
      //used to call docParser functions
    StemFunctionality stem;
      //used to call stemming functions

    size_t found = search.find(" ");
      //checks if multi-word search

    if(found != string::npos) {
        seperateWords(search, found);
    }  //if it is a multi-word search

    for(int i = 0; i < userSearch.size(); i++) {
        parse.upperToLower(userSearch[i]);
          //makes search words all lowercase
        stem.stemWord(userSearch[i]);
        cout << userSearch[i] << endl;
          //stems all search words
    }  //stems each word in the vector and gets rid of stop words

    chooseSearch();
      //runs search based on different boolean operator
}

void Query::seperateWords(string& search, size_t& currPos) {
    bool isEnd = false;

    string temp = search.substr(0, currPos);
      //first word in search is stored in temp
    string restWord = search.substr(currPos+1);
      //stores the rest of the search

    userSearch.push_back(temp);
      //add word to userSearch vector

    while(isEnd == false && restWord.size() >= 1) {
        size_t found = restWord.find(" ");
          //checks if there are more words left in the search

        if(found != string::npos) {
            temp = restWord.substr(0, found);
              //next word is stored in temp
            restWord = restWord.substr(found+1);
              //stores rest of search

            userSearch.push_back(temp);
              //add word to userSearch vector
        }  //if there are more words in the search

        else {
            isEnd = true;
        }  //if there aren't anymore words in the search
    }
}


void Query::chooseSearch() {
    if(userSearch.size() < 2)
    {
        regSearch();
    }
    for(int i = 0; i < userSearch.size(); i++) {
        if(userSearch[i] == "or") {
            orSearch();
        }  //runs orSearch if "or" is found
        else if(userSearch[i] == "and")
        {
            andSearch();
        }

        else {
            regSearch();
        }  //runs andSearch if "or" isn't found
    }
}

void Query::regSearch()
{
    //queryIndex->print();
    //cout << "in reg search funct" << endl;
    //queryIndex->print();
    for(int i = 0; i < userSearch.size(); i++)
    {
        //cout << "in loop" << endl;
        string tempInput = userSearch[i];
        //cout << "user input is: " << tempInput << endl;
        IndexWord tempIndexWord(tempInput);
        if(queryIndex->contains(tempIndexWord))
        {
           // cout << "in contains loop" << endl;
            cout << "----------RETURNING RESULTS FOR : " << tempInput << "----------" << endl;
            IndexWord indexObj2 = queryIndex->find(tempIndexWord);
           indexObj2.printIndexWord();
        }
    }
}
void Query::andSearch() {
  vector<vector<Document>> docInfo;
  vector<string> docUnions;
  vector<string>::iterator it;

  for(int i = 0; i < userSearch.size(); i++)
  {
      if(userSearch[i] == "not") {
          break;
      }

      string tempInput = userSearch[i];
      IndexWord tempIndexWord(tempInput);
      if(queryIndex->contains(tempIndexWord))
      {
          IndexWord indexObj2 = queryIndex->find(tempIndexWord);
          vector<Document> temp2 = indexObj2.getDocVect();
          docInfo.push_back(temp2);
      }
  }
   for(int z =0; z < docInfo.size(); z++)
   {
       //Document printingDoc = docInfo[z];
   }
  for(int i = 1; i < docInfo.size() -1; i++) {
      vector<Document> temp = docInfo[i-1];
      vector<Document> temp1 = docInfo[i];
      vector<string> temp2;
      vector<string> temp3;
      vector<string> temp4;

      for(int i = 0; i< docInfo.size(); i++) {
          temp3[i] = temp[i].getDocID();
          temp4[i] = temp1[i].getDocID();
      }

      it = set_intersection(temp3.begin(), temp3.end(), temp4.begin(), temp4.end(), temp2.begin());

      for(int j = 0; j < temp2.size(); j++) {
          if(count(docUnions.begin(), docUnions.end(), temp2[i])) {
                //does nothing if docID is already in vector
          }

          else {
              docUnions.push_back(temp2[i]);
          }
      }
   }

   sortCount(docUnions);
   getResults(docUnions);
}

void Query::orSearch() {
    vector<vector<Document>> docInfo;
    vector<string> docUnions;
    vector<string>::iterator it;

    for(int i = 0; i < userSearch.size(); i++)
    {
        if(userSearch[i] == "not") {
            break;
        }

        string tempInput = userSearch[i];
        IndexWord tempIndexWord(tempInput);
        if(queryIndex->contains(tempIndexWord))
        {
            IndexWord indexObj2 = queryIndex->find(tempIndexWord);
            vector<Document> temp2 = indexObj2.getDocVect();
            docInfo.push_back(temp2);
        }
    }

    for(int i = 1; i < docInfo.size()-1; i++) {
        vector<Document> temp = docInfo[i-1];
        vector<Document> temp1 = docInfo[i];
        vector<string> temp2;
        vector<string> temp3;
        vector<string> temp4;

        for(int i = 0; i< docInfo.size(); i++) {
            temp3[i] = temp[i].getDocID();
            temp4[i] = temp1[i].getDocID();
        }

        it = set_union(temp3.begin(), temp3.end(), temp4.begin(), temp4.end(), temp2.begin());

        for(int j = 0; j < temp2.size(); j++) {
            if(count(docUnions.begin(), docUnions.end(), temp2[i])) {
                  //does nothing if docID is already in vector
            }

            else {
                docUnions.push_back(temp2[i]);
            }
        }

    }

    sortCount(docUnions);
    getResults(docUnions);
}

void Query::getStats() {
    DocParse d;

    cout << "----------SEARCH STATS----------" << endl;
    cout << "Number of opinions indexed: " << d.getSize() << endl;
    cout << "Average number of words indexed per opinion: " << endl;
    cout << "Top 50 most frequent words: " << endl;
}
/*
void Query::sortCount(vector<int> docUnions) {
    for(int i = 0; i < docUnions.size(); i++) {

    }
}
*/
void Query::getResults(vector<string> &docID) {
    IndexWord w;
    vector<Document> d = w.getDocVect();
    vector<string> topHits;
    vector<Document> temp;

    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < docCount.size(); j++) {
            if(sortedDocCount[i] == docCount[j]) {
                topHits.push_back(docID[j]);
            }
        }
    }

    for(int i = 0; i < topHits.size(); i++) {
        for(int j = 0; j < d.size(); j++) {
            if(topHits[i] == d[j].getDocID()) {
                temp.push_back(d[j]);
            }
        }
    }

    cout << "----------SEARCH Results----------" << endl;
    for(int i = 0; i < 15; i++) {
        cout << "Result: " << i+1 << endl;
        cout << "Title: " << temp[i].getTitle() << endl;
        cout << "Url: " << temp[i].getURL() << endl;
    }
}

void Query::sortCount(vector<string> &docID) {
    IndexWord w;
    vector<Document> d = w.getDocVect();
    //vector<Document> sortedInfo;

    for(int i = 0; i < docID.size(); i++) {
        for(int j = 0; j < d.size(); i++) {
            if(d[j].getDocID() == docID[i]) {
                docCount.push_back(d[j].getDocCount());
            }
        }
    }

    sortedDocCount = docCount;

    sort(sortedDocCount.begin(), sortedDocCount.end(), greater<int> ());
}
