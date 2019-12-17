//David Hoffman
//last revision: 12/5/19
//Kyle Kolodziej revising 12/8/19

#ifndef QUERY_H
#define QUERY_H
#include "index.h"
#include <iostream>
#include <vector>

using namespace std;

class Query {
private:
    vector<string> userSearch;
    Index * queryIndex;
    vector<int> docCount;
    vector<int> sortedDocCount;
public:
    Query(Index* input);
      //default constructor
    void readQuery();
      //reads in query
    void parseQuery(string &);
      //parses query
    void chooseSearch();
      //finds out if its an and/or search
    void andSearch();
      //runs search with and boolean operator
    void orSearch();
      //runs search with boolean operator
    void seperateWords(string&, size_t&);
      //breaks up multi-word search and stores words in userSearch vector
    void getStats();
      //returns search statistics
    void getResults(vector<string>&docID);
    void sortCount(vector<string>&);
    void regSearch();
};

#endif // QUERY_H
