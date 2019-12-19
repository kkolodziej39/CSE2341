/* Creator of file: Kyle Kolodziej
 * Last updated: December 18th, 2019
 *
 * DESCRIPTION OF QUERY:
 *
 *
 */

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

    cout << endl << endl<< "----------SEARCH QUERY----------" << endl;
    cout << "Rules of search:" << endl;
    cout << "1. Multi-word searches must be prefixed with a boolean operator (AND,OR)" << endl;
    cout << "2. No query can have both AND and  OR" << endl;
    cout << "3. Search terms may be preceded with a NOT operator" << endl;
    cout << "Enter search: ";
    //cin.ignore();
    getline(cin, search);
    parseQuery(search);
}

void Query::parseQuery(string &s) {
    char * word = new char[s.length() +1];
    strcpy(word, &s[0]);
    StemFunctionality stemObj;
    char * temp;
    temp = strtok(word, ".-;:,?><='()[]& \n");
    while(temp!= nullptr)
    {
        if(temp == nullptr)
        {
            continue;
        }
        string inputString = temp;
        //cout << "pre stem : " << inputString;
        wordsPreStem.push_back(inputString);
        stemObj.stemWord(inputString);
        transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower); //Make lowercase
        userSearch.push_back(inputString);
        temp = strtok(nullptr, ".-;:,?><='()[]& \n");
    }
    delete [] word;
    chooseSearch();
      //runs search based on different boolean operator
}

void Query::chooseSearch() {

    int notIndex = 0;
    int doubleSearch = -1;
    if(userSearch.size() < 2)
    {
        regSearch();
    }
    else {
        for(int i = 1; i < userSearch.size(); i ++)
        {
            if(userSearch[i] == "not" || userSearch[i] == "NOT" || userSearch[i] == "Not")
            {
                notIndex = i;
            }
        }

        if(notIndex!= 0)
        {
            for(int i = 0; i < userSearch.size(); i++)
            {
                if(userSearch[i] == "or" || userSearch[i] == "OR" || userSearch[i] == "Or" )
                {
                    doubleSearch = i;
                }
            }

            if(doubleSearch != -1)
            {
                //or and not search
                orNotSearch(notIndex);
            }
            else {
                for(int i = 0; i < userSearch.size(); i++)
                {
                    if(userSearch[i] == "and" || userSearch[i] == "AND" || userSearch[i] == "And" )
                    {
                        doubleSearch = i;
                    }
                }

                if(doubleSearch != -1)
                {
                    //and and not search
                    andNotSearch(notIndex);
                }
                else {
                   notSearch();
                }
            }
        }
        else if(userSearch[0] == "or" || userSearch[0] == "OR" || userSearch[0] == "Or" ) {
            orSearch();
        }
        else if(userSearch[0] == "and" || userSearch[0] == "AND" || userSearch[0] == "And")
        {
            andSearch();
        }
        else {
            //cout << endl << endl << "caught here" << endl;
            cout << endl << endl << "----------ERROR: Invalid Search! Try again!----------" << endl << endl;
            readQuery();
        }
    }
}

void Query::newSearch()
{
    clearVars();
    char *numSearch = new char[100];
    //int num;
    //cout << endl << "***ATTENTION: REACHED END OF SEARCH!***" << endl;
    cout << endl << endl << endl <<"----------KYLE'S SEARCH ENGINE----------" << endl;
    cout << "1.) Enter (1) for a new search" << endl;
    cout << "2.) Enter (2) to display statistics" << endl;
    cout << "3.) Enter (3) to exit" << endl;
    cout << "Choice: ";
    //cin.ignore();
    cin.getline(numSearch, 100);

    /*if(numArray[0] != '1' && numArray[0]!= '2' && numArray[0]!= '3')
    {
        while(numArray[0] != '1' && numArray[0]!= '2' && numArray[0]!= '3')
        {
            //delete [] numArray;
            //char *numArray = new char[100];
            cout << "INVALID OPTION! TRY AGAIN" << endl;
            cout << endl << "1.) Enter (1) for a new search" << endl;
            cout << "2.) Enter (2) to display statistics" << endl;
            cout << "3.) Enter (3) to exit" << endl;
            cout << "Choice: ";
            cin.getline(numArray, 100);
        }
    }*/


    if(numSearch[0] == '1')
    {
        cout << endl <<"----------ENTERING NEW SEARCH----------" << endl;
        //delete [] numArray;
        readQuery();
    }
    else if(numSearch[0] == '2'){
        cout << endl <<"----------DISPLAYING STATISTICS----------" << endl;
        //delete [] numArray;
        getStats();
        //newSearch();
    }
    else if(numSearch[0] == '3'){
        cout << endl <<"----------EXITING SEARCH ENGINE----------" << endl;
        cout << "Thank you for using the search engine!" << endl;
        cout << "Creator of search engine: Kyle Kolodziej" << endl;
        cout << "Contact information: kylekolodziejscn2018@gmail.com" << endl;
        //delete [] numArray;
        //return;
    }
    else {
        while(numSearch[0] != '1' && numSearch[0]!= '2' && numSearch[0]!= '3')
        {
            cout << endl << "in here " << endl << endl;
            //delete [] numArray;
            //char *numArray = new char[100];
            cout << "INVALID OPTION! TRY AGAIN" << endl;
            cout << endl << "1.) Enter (1) for a new search" << endl;
            cout << "2.) Enter (2) to display statistics" << endl;
            cout << "3.) Enter (3) to exit" << endl;
            cout << "Choice: ";
            //cin.ignore();
            cin.getline(numSearch, 100);
        }
    }

    delete [] numSearch;

}

void Query::regSearch()
{

    for(int i = 0; i < userSearch.size(); i++)
    {
        string tempInput = userSearch[i];
        string noStem = wordsPreStem[i];
        //cout << "user input is: " << tempInput << endl;
        IndexWord tempIndexWord(tempInput);
        if(queryIndex->contains(tempIndexWord))
        {
           // cout << "in contains loop" << endl;
            cout << endl << endl << "RETURNING RESULTS FOR: " << noStem << endl << endl;
            IndexWord indexObj2 = queryIndex->find(tempIndexWord);
            cout << indexObj2.getIndexWordSize() << " results found" << endl;
            if(indexObj2.getIndexWordSize() > 3)
            {
                cout << "Only displaying the top 3 results..." << endl;
            }
           indexObj2.printTopThree();
           previewPrompt(indexObj2);

        }
        else {
            cout << endl << endl << "ERROR: NO RESULTS FOUND!" << endl << endl;
            newSearch();
        }
    }



}

void Query::clearVars()
{
    userSearch.clear();
    wordsPreStem.clear();
    idFirst.clear();
    idSec.clear();
    indexVect.clear();
    finalDocVect.clear();
    finalIndexVect.clear();
    compareVect.clear();
    docVect.clear();
    /*vector<string> idFirst;
    vector<string> idSec;
    vector<IndexWord> indexVect;
    vector<IndexWord> finalIndexVect;
    vector<Document> docVect;
    vector<Document> finalDocVect;
    vector<string> compareVect;*/

    /*for(int i = 0; i < userSearch.size(); i++)
    {
        userSearch.pop_back();
        wordsPreStem.pop_back();
    }*/
}

void Query::andSearch() {


  string tempInput = userSearch[1];
  IndexWord tempIndexWord(tempInput);
  if(queryIndex->contains(tempIndexWord))
  {
     IndexWord indexObj2 = queryIndex->find(tempIndexWord);
     indexVect.push_back(indexObj2); //dont need
     for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
     {
         string inputId = indexObj2.getDocVect()[i].getDocID();
         idFirst.push_back(inputId);
         Document tempDoc = indexObj2.getDocVect()[i];
         docVect.push_back(tempDoc);
     }
  }
  else {
      cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
      newSearch();
  }

  for(int i = 2; i < userSearch.size(); i++)
  {
      string tempInput = userSearch[i];
      IndexWord tempIndexWord(tempInput);
      if(queryIndex->contains(tempIndexWord))
      {
         IndexWord indexObj2 = queryIndex->find(tempIndexWord);
         indexVect.push_back(indexObj2);
         for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
         {
             string inputId = indexObj2.getDocVect()[i].getDocID();
             idSec.push_back(inputId);
         }

         sort(idFirst.begin(), idFirst.end());
         sort(idSec.begin(), idSec.end());
         set_intersection(idFirst.begin(), idFirst.end(), idSec.begin(), idSec.end(), back_inserter(compareVect));
         idFirst = compareVect;
         for(int k = 0; k < docVect.size(); k ++)
         {
             string comparisonID = docVect[k].getDocID();
             if(std::find(idFirst.begin(), idFirst.end(), comparisonID) != idFirst.end())
             {
                Document tempDoc = docVect[k];
                finalDocVect.push_back(tempDoc);
             }

         }

         docVect = finalDocVect;
         finalDocVect.clear();
         compareVect.clear();
         idSec.clear();
      }
      else {
          cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
          newSearch();
      }
  }

   cout << endl << endl << endl << "RETURNING RESULTS FOR: ";
  for(int i = 1; i < wordsPreStem.size(); i++)
  {
       cout << wordsPreStem[i];
       if(i+1 <wordsPreStem.size())
       {
           cout << " and ";
       }
  }
  cout << endl;


  cout << docVect.size() << " results found" << endl;

  if(docVect.size() < 4)
  {
      //Print all the doc vectors in 3 or less
      for(int i = 0; i < docVect.size(); i ++)
      {
          cout << endl << "----------Reslt #" << i+1 << "----------" <<endl;
          docVect[i].printQueryDoc();
      }
      IndexWord previewObject = makeIndexWordObj(docVect);
      previewPrompt(previewObject);
  }

  else {
      cout << "Only displaying the top 3 results..." << endl;
      for(int i = 0; i < 3; i ++)
      {
          cout << endl << "----------Result #" << i+1 << "----------" <<endl;
          docVect[i].printQueryDoc();
      }
      IndexWord previewObject = makeIndexWordObj(docVect);
      previewPrompt(previewObject);
  }

}

void Query::orSearch() {


    string tempInput = userSearch[1];
    IndexWord tempIndexWord(tempInput);
    if(queryIndex->contains(tempIndexWord))
    {
       IndexWord indexObj2 = queryIndex->find(tempIndexWord);
       indexVect.push_back(indexObj2); //dont need
       for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
       {
           string inputId = indexObj2.getDocVect()[i].getDocID();
           idFirst.push_back(inputId);
           Document tempDoc = indexObj2.getDocVect()[i];
           docVect.push_back(tempDoc);
       }
    }
    else {
        cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
        newSearch();
    }

    for(int i = 2; i < userSearch.size(); i++)
    {
        string tempInput = userSearch[i];
        IndexWord tempIndexWord(tempInput);
        if(queryIndex->contains(tempIndexWord))
        {
           IndexWord indexObj2 = queryIndex->find(tempIndexWord);
           indexVect.push_back(indexObj2);
           for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
           {
               string inputId = indexObj2.getDocVect()[i].getDocID();
               idSec.push_back(inputId);
           }

           sort(idFirst.begin(), idFirst.end());
           sort(idSec.begin(), idSec.end());
           set_union(idFirst.begin(), idFirst.end(), idSec.begin(), idSec.end(), back_inserter(compareVect));
           idFirst = compareVect;
           for(int k = 0; k < docVect.size(); k ++)
           {
               string comparisonID = docVect[k].getDocID();
               if(std::find(idFirst.begin(), idFirst.end(), comparisonID) != idFirst.end())
               {
                  Document tempDoc = docVect[k];
                  finalDocVect.push_back(tempDoc);
               }

           }

           docVect = finalDocVect;
           finalDocVect.clear();
           compareVect.clear();
           idSec.clear();
        }
        else {
            cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
            newSearch();
        }
    }

     cout << endl << endl << endl << "RETURNING RESULTS FOR: ";
    for(int i = 1; i < wordsPreStem.size(); i++)
    {
         cout << wordsPreStem[i];
         if(i+1 <wordsPreStem.size())
         {
             cout << " or ";
         }
    }
    cout << endl;

    cout << docVect.size() << " results found" << endl;
    if(docVect.size() < 4)
    {
        //Print all the doc vectors in 3 or less
        for(int i = 0; i < docVect.size(); i ++)
        {
            cout << endl << "----------Reslt #" << i+1 << "----------" <<endl;
            docVect[i].printDocument();
        }
        IndexWord previewObject = makeIndexWordObj(docVect);
        previewPrompt(previewObject);
    }

    else {
        cout << "Only displaying the top 3 results..." << endl;
        for(int i = 0; i < 3; i ++)
        {
            cout << endl << "----------Result #" << i+1 << "----------" <<endl;
            docVect[i].printQueryDoc();
        }
        IndexWord previewObject = makeIndexWordObj(docVect);
        previewPrompt(previewObject);
    }
}

void Query::notSearch()
{

    string tempInput = userSearch[0];
    IndexWord tempIndexWord(tempInput);
    if(queryIndex->contains(tempIndexWord))
    {
       IndexWord indexObj2 = queryIndex->find(tempIndexWord);
       indexVect.push_back(indexObj2); //dont need
       for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
       {
           string inputId = indexObj2.getDocVect()[i].getDocID();
           idFirst.push_back(inputId);
           Document tempDoc = indexObj2.getDocVect()[i];
           docVect.push_back(tempDoc);
       }
    }
    else {
        cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
        newSearch();
    }

    for(int i = 2; i < userSearch.size(); i++)
    {
        string tempInput = userSearch[i];
        IndexWord tempIndexWord(tempInput);
        if(queryIndex->contains(tempIndexWord))
        {
           IndexWord indexObj2 = queryIndex->find(tempIndexWord);
           indexVect.push_back(indexObj2);
           for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
           {
               string inputId = indexObj2.getDocVect()[i].getDocID();
               idSec.push_back(inputId);
           }

           sort(idFirst.begin(), idFirst.end());
           sort(idSec.begin(), idSec.end());
           set_difference(idFirst.begin(), idFirst.end(), idSec.begin(), idSec.end(), back_inserter(compareVect));
           idFirst = compareVect;
           for(int k = 0; k < docVect.size(); k ++)
           {
               string comparisonID = docVect[k].getDocID();
               if(std::find(idFirst.begin(), idFirst.end(), comparisonID) != idFirst.end())
               {
                  Document tempDoc = docVect[k];
                  finalDocVect.push_back(tempDoc);
               }

           }

           docVect = finalDocVect;
           finalDocVect.clear();
           compareVect.clear();
           idSec.clear();
        }
        else {
            cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
            newSearch();
        }
    }

     cout << endl << endl << endl << "RETURNING RESULTS FOR: ";
    for(int i = 1; i < wordsPreStem.size(); i++)
    {
         cout << wordsPreStem[i];
         if(i+1 <wordsPreStem.size())
         {
             cout << ", but not ";
         }
    }
    cout << endl;

    if(docVect.size() == 0)
    {
        cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
        newSearch();
    }

    cout << docVect.size() << " results found" << endl;

    if(docVect.size() < 4)
    {
        //Print all the doc vectors in 3 or less
        for(int i = 0; i < docVect.size(); i ++)
        {
            cout << endl << "----------Reslt #" << i+1 << "----------" <<endl;
            docVect[i].printQueryDoc();
        }
        IndexWord previewObject = makeIndexWordObj(docVect);
        previewPrompt(previewObject);
    }

    else {
        cout << "Only displaying the top 3 results..." << endl;
        for(int i = 0; i < 3; i ++)
        {
            cout << endl << "----------Result #" << i+1 << "----------" <<endl;
            docVect[i].printQueryDoc();
        }
        IndexWord previewObject = makeIndexWordObj(docVect);
        previewPrompt(previewObject);
    }
}

void Query::getStats() {

    cout << endl << endl;
    queryIndex->getStats();
    cout << endl << endl << "----------ATTENTION: REACHED END OF STATISTICS!----------" << endl;
    newSearch();
}

void Query::orNotSearch(int nIndex)
{

    string tempInput = userSearch[1];
    IndexWord tempIndexWord(tempInput);
    if(queryIndex->contains(tempIndexWord))
    {
       IndexWord indexObj2 = queryIndex->find(tempIndexWord);
       indexVect.push_back(indexObj2); //dont need
       for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
       {
           string inputId = indexObj2.getDocVect()[i].getDocID();
           idFirst.push_back(inputId);
           Document tempDoc = indexObj2.getDocVect()[i];
           docVect.push_back(tempDoc);
       }
    }
    else {
        cout << endl << endl << "----------ERROR: NO RESULTS FOUND----------" << endl << endl;
        newSearch();
    }

    for(int i = 2; i < nIndex; i++)
    {
        string tempInput = userSearch[i];
        IndexWord tempIndexWord(tempInput);
        if(queryIndex->contains(tempIndexWord))
        {
           IndexWord indexObj2 = queryIndex->find(tempIndexWord);
           indexVect.push_back(indexObj2);
           for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
           {
               string inputId = indexObj2.getDocVect()[i].getDocID();
               idSec.push_back(inputId);
           }

           sort(idFirst.begin(), idFirst.end());
           sort(idSec.begin(), idSec.end());
           set_union(idFirst.begin(), idFirst.end(), idSec.begin(), idSec.end(), back_inserter(compareVect));
           idFirst = compareVect;
           for(int k = 0; k < docVect.size(); k ++)
           {
               string comparisonID = docVect[k].getDocID();
               if(std::find(idFirst.begin(), idFirst.end(), comparisonID) != idFirst.end())
               {
                  Document tempDoc = docVect[k];
                  finalDocVect.push_back(tempDoc);
               }

           }

           docVect = finalDocVect;
           finalDocVect.clear();
           compareVect.clear();
           idSec.clear();
        }
        else {
            cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
            newSearch();
        }
    }

    for(int i = nIndex + 1; i < userSearch.size(); i++)
    {
        //id first and docVect containing the previous results
        //Now the not terms
        string tempInput = userSearch[i];
        IndexWord tempIndexWord(tempInput);
        if(queryIndex->contains(tempIndexWord))
        {
           IndexWord indexObj2 = queryIndex->find(tempIndexWord);
           indexVect.push_back(indexObj2);
           for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
           {
               string inputId = indexObj2.getDocVect()[i].getDocID();
               idSec.push_back(inputId);
           }

           sort(idFirst.begin(), idFirst.end());
           sort(idSec.begin(), idSec.end());
           set_difference(idFirst.begin(), idFirst.end(), idSec.begin(), idSec.end(), back_inserter(compareVect));
           idFirst = compareVect;
           for(int k = 0; k < docVect.size(); k ++)
           {
               string comparisonID = docVect[k].getDocID();
               if(std::find(idFirst.begin(), idFirst.end(), comparisonID) != idFirst.end())
               {
                  Document tempDoc = docVect[k];
                  finalDocVect.push_back(tempDoc);
               }

           }
           docVect = finalDocVect;
           finalDocVect.clear();
           compareVect.clear();
           idSec.clear();
        }
        else {
            cout << "Warning: not term (" << tempInput << ") isn't in search results!" <<endl << endl;
        }
    }


     cout << endl << endl << endl << "RETURNING RESULTS FOR: ";
    for(int i = 1; i < nIndex; i++)
    {
         cout << wordsPreStem[i];
         if(i+1 < nIndex)
         {
             cout << " or ";
         }
    }
    cout << ", but not ";
    for(int i = nIndex+1; i < wordsPreStem.size(); i++)
    {
        cout << wordsPreStem[i];
        if(i+1 < wordsPreStem.size())
        {
            cout << " and not ";
        }
    }
    cout << endl;

    if(docVect.size() == 0)
    {
        cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
        newSearch();
    }


    cout << docVect.size() << " results found" << endl;
    if(docVect.size() < 4)
    {
        //Print all the doc vectors in 3 or less
        for(int i = 0; i < docVect.size(); i ++)
        {
            cout << endl << "----------Reslt #" << i+1 << "----------" <<endl;
            docVect[i].printQueryDoc();
        }
        IndexWord previewObject = makeIndexWordObj(docVect);
        previewPrompt(previewObject);
    }

    else {
        cout << "Only displaying the top 3 results..." << endl;
        for(int i = 0; i < 3; i ++)
        {
            cout << endl << "----------Result #" << i+1 << "----------" <<endl;
            docVect[i].printQueryDoc();
        }
        IndexWord previewObject = makeIndexWordObj(docVect);
        previewPrompt(previewObject);
    }

}

void Query::andNotSearch(int nIndex)
{

    string tempInput = userSearch[1];
    IndexWord tempIndexWord(tempInput);
    if(queryIndex->contains(tempIndexWord))
    {
       IndexWord indexObj2 = queryIndex->find(tempIndexWord);
       indexVect.push_back(indexObj2); //dont need
       for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
       {
           string inputId = indexObj2.getDocVect()[i].getDocID();
           idFirst.push_back(inputId);
           Document tempDoc = indexObj2.getDocVect()[i];
           docVect.push_back(tempDoc);
       }
    }
    else {
        cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
        newSearch();
    }

    for(int i = 2; i < nIndex; i++)
    {
        string tempInput = userSearch[i];
        IndexWord tempIndexWord(tempInput);
        if(queryIndex->contains(tempIndexWord))
        {
           IndexWord indexObj2 = queryIndex->find(tempIndexWord);
           indexVect.push_back(indexObj2);
           for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
           {
               string inputId = indexObj2.getDocVect()[i].getDocID();
               idSec.push_back(inputId);
           }

           sort(idFirst.begin(), idFirst.end());
           sort(idSec.begin(), idSec.end());
           set_intersection(idFirst.begin(), idFirst.end(), idSec.begin(), idSec.end(), back_inserter(compareVect));
           idFirst = compareVect;
           for(int k = 0; k < docVect.size(); k ++)
           {
               string comparisonID = docVect[k].getDocID();
               if(std::find(idFirst.begin(), idFirst.end(), comparisonID) != idFirst.end())
               {
                  Document tempDoc = docVect[k];
                  finalDocVect.push_back(tempDoc);
               }

           }

           docVect = finalDocVect;
           finalDocVect.clear();
           compareVect.clear();
           idSec.clear();
        }
        else {
            cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
            newSearch();
        }
    }

    for(int i = nIndex + 1; i < userSearch.size(); i++)
    {
        //id first and docVect containing the previous results
        //Now the not terms
        string tempInput = userSearch[i];
        IndexWord tempIndexWord(tempInput);
        if(queryIndex->contains(tempIndexWord))
        {
           IndexWord indexObj2 = queryIndex->find(tempIndexWord);
           indexVect.push_back(indexObj2);
           for(int i = 0; i < indexObj2.getIndexWordSize(); i++)
           {
               string inputId = indexObj2.getDocVect()[i].getDocID();
               idSec.push_back(inputId);
           }

           sort(idFirst.begin(), idFirst.end());
           sort(idSec.begin(), idSec.end());
           set_difference(idFirst.begin(), idFirst.end(), idSec.begin(), idSec.end(), back_inserter(compareVect));
           idFirst = compareVect;
           for(int k = 0; k < docVect.size(); k ++)
           {
               string comparisonID = docVect[k].getDocID();
               if(std::find(idFirst.begin(), idFirst.end(), comparisonID) != idFirst.end())
               {
                  Document tempDoc = docVect[k];
                  finalDocVect.push_back(tempDoc);
               }

           }
           docVect = finalDocVect;
           finalDocVect.clear();
           compareVect.clear();
           idSec.clear();
        }
        else {
            cout << "Warning: not term (" << tempInput << ") isn't in search results!" <<endl << endl;
        }
    }


     cout << endl << endl << endl << "RETURNING RESULTS FOR: ";
    for(int i = 1; i < nIndex; i++)
    {
         cout << wordsPreStem[i];
         if(i+1 < nIndex)
         {
             cout << " and ";
         }
    }
    cout << ", but not ";
    for(int i = nIndex+1; i < wordsPreStem.size(); i++)
    {
        cout << wordsPreStem[i];
        if(i+1 < wordsPreStem.size())
        {
            cout << " and not ";
        }
    }
    cout << endl;

    if(docVect.size() == 0)
    {
        cout << endl << endl << "----------ERROR: NO RESULTS FOUND!----------" << endl << endl;
        newSearch();
    }

    cout << docVect.size() << " results found" << endl;
    if(docVect.size() < 4)
    {
        //Print all the doc vectors in 3 or less
        for(int i = 0; i < docVect.size(); i ++)
        {
            cout << endl << "----------Reslt #" << i+1 << "----------" <<endl;
            docVect[i].printQueryDoc();
        }
        IndexWord previewObject = makeIndexWordObj(docVect);
        previewPrompt(previewObject);
    }

    else {
        cout << "Only displaying the top 3 results..." << endl;
        for(int i = 0; i < 3; i ++)
        {
            cout << endl << "----------Result #" << i+1 << "----------" <<endl;
            docVect[i].printQueryDoc();
        }
        IndexWord previewObject = makeIndexWordObj(docVect);
        previewPrompt(previewObject);
    }


}

void Query::previewPrompt(IndexWord & obj)
{
    char numArray[100];
    bool invalidInput = true;
    int choice = 0;
    cout << endl << endl << endl << "----------SEARCH RESULTS DISPLAYED ABOVE----------" << endl << endl << endl;
    cout << endl <<"----------PREVIEW OF RESULT OPTION----------" << endl;
    cout << "1.) Enter corresponding search result number for a preview of the document" << endl;
    cout << "\t Example: Enter (1) for preview of Result #1" << endl;
    cout << "2.) Enter (4) for a new search" << endl;
    cout << "3.) Enter (5) to display statistics" << endl;
    cout << "4.) Enter (6) to exit" << endl;
    cout << "Choice: ";

    cin.getline(numArray, 100);
    int maxDocs = obj.getIndexWordSize();
    choice = atoi(numArray);

    if(choice == 1 && maxDocs >0)
    {
        invalidInput = false;
        //Print 1st doc's preview
        cout << endl <<"----------PRINTING PREVIEW OF RESULT #1----------" << endl;
        obj.getDocPreviewAt(choice);
        cout << endl << "----------ATTENTION: REACHED END OF PREVIEW!----------" << endl;
        newSearch(); //Enter new search after printing preview

    }
    else if(choice == 2 && maxDocs >1)
    {
        invalidInput = false;
        //Print 2nd doc's preview
        cout << endl <<"----------PRINTING PREVIEW OF RESULT #2----------" << endl;
        obj.getDocPreviewAt(choice);
        cout << endl << "----------ATTENTION: REACHED END OF PREVIEW!----------" << endl;
        newSearch(); //Enter new search after printing preview
    }
    else if(choice == 3 && maxDocs >2)
    {
        invalidInput = false;
        //Print 3rd doc's preview
        cout << endl <<"----------PRINTING PREVIEW OF RESULT #3----------" << endl;
        obj.getDocPreviewAt(choice);
        cout << endl << "----------ATTENTION: REACHED END OF PREVIEW!----------" << endl;
        newSearch(); //Enter new search after printing preview
    }
    else if(choice == 4)
    {
        invalidInput = false;
        //New search
        cout << endl <<"----------ENTERING NEW SEARCH----------" << endl;
        readQuery();
    }
    else if(choice == 5)
    {
        invalidInput = false;
        //Print the stats
        cout << endl <<"----------DISPLAYING STATISTICS----------" << endl;
        getStats();
        //newSearch();
    }
    else if(choice == 6)
    {
        invalidInput = false;
        //Exit search engine
        cout << endl <<"----------EXITING SEARCH ENGINE----------" << endl;
        cout << "Thank you for using the search engine!" << endl;
        cout << "Creator of search engine: Kyle Kolodziej" << endl;
        cout << "Contact information: kylekolodziejscn2018@gmail.com" << endl;
        return;
    }
    else{
        /* Invalid input
         * (1) Need to account for user entering a result number
         * And not having enough documents to be able to preview
         * (2) Need to account for user entering number > 5 or < 1
         * (3) Need to account for user not entering a number
         */
        while(invalidInput)
        {
            cout << endl << "----------INVALID OPTION! TRY AGAIN!----------" << endl;
            cout << "1.) Enter corresponding search result number for a preview of the document" << endl;
            cout << "\t Example: Enter (1) for preview of Result #1" << endl;
            cout << "2.) Enter (4) for a new search" << endl;
            cout << "3.) Enter (5) to display statistics" << endl;
            cout << "4.) Enter (6) to exit" << endl;
            cout << "Choice: ";

            cin.getline(numArray, 100);
            int maxDocs = obj.getIndexWordSize();
            choice = atoi(numArray);

            if(choice == 1 && maxDocs >0)
            {
                invalidInput = false;
                //Print 1st doc's preview
                cout << endl <<"----------PRINTING PREVIEW OF RESULT #1----------" << endl;
                obj.getDocPreviewAt(choice);
                cout << endl << "----------ATTENTION: REACHED END OF PREVIEW!----------" << endl;
                newSearch(); //Enter new search after printing preview
            }
            else if(choice == 2 && maxDocs >1)
            {
                invalidInput = false;
                //Print 1st doc's preview
                cout << endl <<"----------PRINTING PREVIEW OF RESULT #2----------" << endl;
                obj.getDocPreviewAt(choice);
                cout << endl << "----------ATTENTION: REACHED END OF PREVIEW!----------" << endl;
                newSearch(); //Enter new search after printing preview
            }
            else if(choice == 3 && maxDocs >2)
            {
                invalidInput = false;
                //Print 1st doc's preview
                cout << endl <<"----------PRINTING PREVIEW OF RESULT #3----------" << endl;
                obj.getDocPreviewAt(choice);
                cout << endl << "----------ATTENTION: REACHED END OF PREVIEW!----------" << endl;
                newSearch(); //Enter new search after printing preview
            }
            else if(choice == 4)
            {
                //New search
                invalidInput = false;
                cout << endl <<"----------ENTERING NEW SEARCH----------" << endl;
                readQuery();
            }
            else if(choice==5)
            {
                //Display stats
                cout << endl <<"----------DISPLAYING STATISTICS----------" << endl;
                getStats();
                //newSearch();
            }
            else if(choice == 5)
            {
                //Exit the search
                invalidInput = false;
                cout << endl <<"----------EXITING SEARCH ENGINE----------" << endl;
                cout << "Thank you for using the search engine!" << endl;
                cout << "Creator of search engine: Kyle Kolodziej" << endl;
                cout << "Contact information: kylekolodziejscn2018@gmail.com" << endl;
                return;
            }
        }
    }
}

IndexWord Query::makeIndexWordObj(vector<Document> &docVect)
{
    /* Preview prompt takes an IndexWord& as parameter
     * In some of the searches, final result is a vector<Document>
     * Need to make an IndexWord object from this docVect parameter
     * Will then be used to pass into previewPrompt function
     *
     * NOTE:
     * Only display top 3 results so only need 3 document objects
     * At most from docVect into an IndexWord object
     */
    IndexWord indexWordObject;
    if(docVect.size() < 4)
    {
        //Add all the doc objects from vector if 3 or less
        for(int i = 0; i < docVect.size(); i ++)
        {
            indexWordObject.addDocObj(docVect[i]);
        }
    }

    else {
        //Only need first 3
        for(int i = 0; i < 3; i ++)
        {
            indexWordObject.addDocObj(docVect[i]);
        }
    }

    return indexWordObject;
}
