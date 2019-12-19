/* Creator of file: Kyle Kolodziej
 * Last updated: December 18th, 2019
 *
 * DESCRIPTION OF DOCPARSE:
 *
 *
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include "docparse.h"
#include "regex.h"
#include "json.hpp"
#include "dirent.h"
#include "stemfunctionality.h"
#include "avl.h"
#include "example.h"
using namespace std;

DocParse::DocParse()
{
    totalOpinions = 0;
    totalWords = 0;
    addStopWords(); //Populate stopWord vector
    //Switch stop word vector to avl tree?

}

DocParse::~DocParse()
{

}

void DocParse::readDoc(char *argv[], Index *& p)
{
    DIR * point;
    struct dirent *pointEnt;
    if((point=opendir(argv[1]))!= nullptr)
    {
        while((pointEnt = readdir(point))!= nullptr)
        {
            vector<string> data;
            string fPath = argv[1];
            string direct = fPath;
            string fileName = pointEnt->d_name;
            string getID;
            getID = fileName.substr(0, fileName.size() - 5); //subtract four for the .json added to file name
            docID = getID;
            string tempFile = fPath + "/" + fileName;
            ifstream file(tempFile);
            if(fileName != + "." && fileName != "..")
            {
                nlohmann::json jObj;
                std::string temp;
                file >> jObj;
                //Getting the url below, will be used for doc obj
                url = jObj["resource_uri"];
                //cout << "URL: " << url << endl;

                //Using the absolute_url to get the name of the case
                //Getting starting position of the docId and then moving past that to get a substring of the name
                //Referenced: http://www.cplusplus.com/reference/string/string/find/
                string abUrl = jObj["absolute_url"];
                std::size_t found = abUrl.find(docID);
                found = found + docID.size() + 1;
                string caseName;
                caseName = abUrl.substr(found);
                formatTitle(caseName);
                string html;

                /* Loops below used to determine where the html text is located
                 * Tag options are:
                 * "html"
                 * "html_with_citations"
                 * "html_lawbox"
                 * "html_columbia"
                 *
                 * NOTE:
                 * Also can have "Certiorari denied" or "Petition for rehearing denied"
                 * Need to ignore these two cases
                 * Will check size of html to see if either of these cases?
                 * Will create two strings for these test cases and use std::find function
                 * In order to determine whether the html text contains these test cases
                 *
                 */

                string case1 = "Certiorari denied";
                string case2 = "Petition for rehearing denied";
                if(jObj["html"] == nullptr)
                {
                    if(jObj["html_with_citations"] == nullptr)
                    {
                        if(jObj["html_lawbox"] == nullptr)
                        {
                            if(jObj["html_columbia"] == nullptr)
                            {
                                //don't do anything, all are nullptr
                            }
                            else {
                                html = jObj["html_columbia"];
                            }
                        }
                        else {
                            html = jObj["html_lawbox"];
                        }
                    }
                    else {
                        html = jObj["html_with_citations"];
                    }

                }
                else {
                    html = jObj["html"];
                }


               if((html.find(case1) != string::npos) || (html.find(case2) != string::npos))
                {
                    //cout << "found them" << endl << endl;
                   //USE AS TESTER FOR FILES THAT WERE GIVING TROUBLE******
                    break;
                }
                else {
                    totalOpinions++; //Update size (Total number of opinions parsed)

                    int a = 0, b = 0;
                    /* Using the code below to
                     * (1) Remove the html tags
                     * (2) Remove any non ASCII characters
                     * Referred to: https://stackoverflow.com/questions/49333136/removing-html-tags-from-a-string-of-text
                     *
                     *
                     * The stripping the html tag part is the first if statement in for loop (<> checked)
                     * Below it checks whether the character in the string is within range of ASCII characters
                     * If not, then it will remove the character
                     *
                     * Attempted to use HTML parser (FILL IN) to strip the HTML tags
                     * Attempted to use Regex to strip the non ASCII characters
                     */

                    for (int a = b; a < html.length(); a++)
                    {
                        if (html[a] == '<') //Removing the HTML tags
                        {
                            for (int b = a; b < html.length(); b++)
                            {
                                if (html[b] == '>')
                                {
                                    html.erase(a, (b - a + 1));
                                    break;
                                }
                            }
                        }
                        else if(html[a] < 26 || html[a] > 128) //Removing non ascii characters
                        {
                            html.erase(a, a+1);
                        }

                    }

                    strippedHtml = html; //feel like should be using dynamic memory location with html so large
                    char * word = new char[html.length() +1];
                    strcpy(word, &html[0]);
                    removeStopWords(word, p); //Adding all of the words that aren't stop words to the documentWords vect
                    delete [] word;
                }
            }
            file.close();
        }
    }
    closedir(point);
}

void DocParse::getDates(string & arr)
{
    //Not as uniform as I thought it was going to be

    string s("Submitted");
    string d("Decided");
    std::size_t found = arr.find(s);
    std::size_t found2=arr.find(".",found+1,6);
    cout << "Start: " << found << " End: " << found2 << endl;
    //submissionDate = arr.substr(found, found2-1);
    //cout << "Submission date is: " << submissionDate << endl;
}

void DocParse::addStopWords()
{
    //Making the AVL Tree of stop words with the text file that references the site on the project handout of search algo stop words
    int numStopWords = 635;
    ifstream inputFile("/home/student/Desktop/CSE2341-F19-Kyle-David/Sprint5/build-Final-Desktop_Qt_5_10_0_GCC_64bit-Debug/StopWords");
    string temp;
    getline(inputFile, temp); //Need to ignore first line as just inserted url
    for(int i = 0; i < numStopWords; i++)
    {
        getline(inputFile, temp);
        stopWords.push_back(temp);
    }
}

void DocParse::sendToIndex()
{
    //string temp;
   // AVL<IndexWord> indexTree; 
    //string temp;
    for(int i = 0; i < stemmedDocWords.size(); i++)
    {
        string temp;
        temp = stemmedDocWords[i];
        cout << "word is " << temp << endl;
        //IndexWord newObj(temp, docID, title, url);
        //indexTree.insert(newObj);
        //then add these to an AVL tree?
        //IndexWord newObj(docID, temp);

        //tree.insert(newObj);
        //then add these to an AVL tree
    }
    indexTree.print();
}

void DocParse::upperToLower(string & inputString)
{
    //Turning all uppercase letters to lowercase with stl function
    //Referenced https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
    transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
}

void DocParse::removeStopWords(char *arr, Index*&p)
{
    StemFunctionality stemObj;
    //Adding all of the words that aren't stop words to the documentWords vect
    char * temp;
    temp = strtok(arr, ".-;:,?><='*$%()_!~#@[]& \n  \t");
    while(temp!= nullptr)
    {
        if(temp == nullptr)
        {
            continue;
        }
        string temp2 = temp;
        upperToLower(temp2); //Need to make all lowercase before checking if a stop word
        if(std::find(stopWords.begin(), stopWords.end(), temp2) != stopWords.end())
        {
            //Don't want to do anything with this string as a stop word
        }
        else if(temp2.size() < 3)
        {
            //do nothing if less than 3
        }
        else {
            string preview = strippedHtml.substr(0,200);
            stemObj.stemWord(temp2);
            IndexWord newIndexObj(temp2, docID, title, url, preview);
            p->insert(newIndexObj);
            totalWords++;
            //documentWords.push_back(temp2); //Document words has total number of words
            //If not a stop word, it will add to the docWords vect
        }
        temp = strtok(nullptr, ".-;:,?><='_~*$%#@!()[]& \n  \t");
    }
}

bool DocParse::invalidChar(char c)
{
    return !(c>=0 && c <128);
}

void DocParse::stripUnicode(string & str)
{
    //str.erase(remove_if(str.begin(),str.end(), invalidChar), str.end());
}

void DocParse::stemDocWordstoAVL(Index *& p)
{
    //This function will take the documentWords (html tags and stop words already removed)
    //And will stem each word before adding it into a vector of all the stemmedDocWords
    string temp; //Used to grab each index
    StemFunctionality stemObj; //Will be used for stemming
    //p = new AVLIndex();
    for(int i = 0; i < documentWords.size(); i++)
    {
        temp = documentWords[i];
        stemObj.stemWord(temp);
        string preview = strippedHtml.substr(0,200);
        IndexWord newIndexObj(temp, docID, title, url, preview);
        //newIndexObj.addDocHTML(submissionDate, newIndexObj.getDocVect().size()-1);
        p->insert(newIndexObj);
        stemmedDocWords.push_back(temp);
    }
    //cout << "DOne with avl" << endl;
    //p->print();
}


void DocParse::stemDocWordstoHash(Index * p)
{
    //This function will take the documentWords (html tags and stop words already removed)
    //And will stem each word before adding it into a vector of all the stemmedDocWords
    string temp; //Used to grab each index
    StemFunctionality stemObj; //Will be used for stemming
    //p = new HashIndex();
    //cout << "In hash function..." << endl;
    for(int i = 0; i < documentWords.size(); i++)
    {
        //cout << "In loop " << endl;
        temp = documentWords[i];
        stemObj.stemWord(temp);
        string preview = strippedHtml.substr(0,200);
        IndexWord newIndexObj(temp, docID, title, url, preview);
        p->insert(newIndexObj);
        stemmedDocWords.push_back(temp);
    }
}

double DocParse::getTotalWordCount()
{
    return totalWords;
}

int DocParse::getTotalOpinionCount()
{
    return totalOpinions;
}


void DocParse::parseHTML(char * html)
{

/*
   // char html[] = "<div><span>HTML</span></div>";

       // basic init
       myhtml_t* myhtml = myhtml_create();
       myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

       // first tree init
       myhtml_tree_t* tree = myhtml_tree_create();
       myhtml_tree_init(tree, myhtml);

       // parse html
       myhtml_parse(tree, MyENCODING_UTF_8, html, strlen(html));

       // print result
       // or see serialization function with callback: myhtml_serialization_tree_callback
       mycore_string_raw_t str = {0};
       myhtml_serialization_tree_buffer(myhtml_tree_get_document(tree), &str);
       //printf("%s\n", str.data);
       cout << "In html parser..." << endl << endl;
       string returner;
       //cout << str << endl;
       int htmlSize = sizeof(str);
       cout << "html size is: " << htmlSize << endl;
       for(int i = 0; i < htmlSize; i++)
       {
           returner = returner + str.data[i];
           cout << returner << endl;
       }
       // release resources
       mycore_string_raw_destroy(&str, false);
       myhtml_tree_destroy(tree);
       myhtml_destroy(myhtml);
       //str.data
       //cout << str.data[1] << endl;*/


}

void DocParse::formatTitle(string & caseName)
{
    string tempTitle;
    char word[caseName.length() +1];
    strcpy(word, &caseName[0]);
    char*temp = strtok(word, "-");
    tempTitle = temp;
    temp = strtok(nullptr, "-/");
    while(temp!= nullptr)
    {
        if(temp == nullptr)
        {
            continue;
        }
        else {
            tempTitle = tempTitle + " " + temp;
        }
        temp = strtok(nullptr, "-/");
    }
    title = tempTitle;
}

void DocParse::printTotalWords(ostream & out)
{
    out << "Total Number of Words Indexed: " << totalWords << endl;
}

void DocParse::printTotalOpinions(ostream & out)
{
    out << "Total Number of Opinions Indexed: " << totalOpinions << endl;
}

AVL<IndexWord>& DocParse::getIndexTree() {
    return indexTree;
}

void DocParse::printWords()
{

}
