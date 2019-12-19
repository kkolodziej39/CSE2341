/* Creator of file: Kyle Kolodziej
 * Last updated: December 18th, 2019
 *
 * DESCRIPTION OF QUERY:
 *
 *
 */

#ifndef QUERY_H
#define QUERY_H
#include "index.h"
#include <iostream>
#include <vector>

using namespace std;

class Query {
private:
    vector<string> userSearch;
    vector<string> wordsPreStem;
    Index * queryIndex;
    vector<string> idFirst;
    vector<string> idSec;
    vector<IndexWord> indexVect;
    vector<IndexWord> finalIndexVect;
    vector<Document> docVect;
    vector<Document> finalDocVect;
    vector<string> compareVect;
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
    void getStats();
      //returns search statistics
    void regSearch();
    void clearVars();
    void newSearch();
    void notSearch();
    void orNotSearch(int nIndex);
    void andNotSearch(int nIndex);
    void previewPrompt(IndexWord &);
    IndexWord makeIndexWordObj(vector<Document> &docVect);
};

#endif // QUERY_H
