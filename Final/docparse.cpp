//Kyle Kolodziej
//Updated 12/8

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <regex>
#include <string.h>
//#include "myhtml/api.h"
#include "docparse.h"
#include "regex.h"
#include "json.hpp"
#include "dirent.h"
#include "stemfunctionality.h"
#include "avl.h"
#include "example.h"
using namespace std;
//using json = nlohmann::json;

DocParse::DocParse()
{
    size = 0;
    addStopWords();
    /*cout << "stop words are: " << endl;
    for(int i = 0; i < stopWords.size(); i++)
    {
        cout << stopWords[i] << endl;
    }*/
}

DocParse::~DocParse()
{

}



void DocParse::readDoc(char *argv[], int structureChoice, Index * p)
{
   // cout << "in doc parse class" << endl;
    DIR * point;
    struct dirent *pointEnt;
    //ifstream file;
    if((point=opendir(argv[1]))!= NULL)
    {
       // cout << "in loop 1" << endl;
        while((pointEnt = readdir(point))!= NULL)
        {
           // cout << "in loop 2" << endl;

            vector<string> data;
            string fPath = argv[1];
            string direct = fPath;
            string fileName = pointEnt->d_name;
            string getID;
            getID = fileName.substr(0, fileName.size() - 5); //subtract four for the .json added to file name
            //char * convert;
           //cout << "id is: " << getID << endl << endl;
            //strcpy(convert, &getID[0]);
            docID = getID;
            //cout << "file name: " << fileName << endl;
            string tempFile = fPath + "/" + fileName;
           // string tempFile = "/home/student/Desktop/scotus-small/" + fileName;
            //cout << "temp file is: " << tempFile << endl;
            ifstream file(tempFile);
            //ifstream file("/home/student/Desktop/scotus-small/111319.json");
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
                //cout << "Case name is : " << caseName << endl;
                formatTitle(caseName);
                //cout << "Formatted is: " << title << endl;


                string html = jObj["html"];
                if(html.size() < 20)
                {
                    //cout << "Type 1" << endl;
                    html = jObj["html_lawbox"]; //If not on html tag need to look elsewhere

                }

                if(html.size() < 20)
                {
                    //cout << "Type 2" << endl;
                    html = jObj["html_columbia"]; //If not on html tag need to look elsewhere

                }

                if(html.size() < 20)
                {
                    //cout << "Type 3" << endl;
                    html = jObj["html_with_citations"]; //If not on html tag need to look elsewhere

                }

                if(html.size() < 20)
                {
                    throw "Error finding html text for file!";
                }

                if(html == "certiorari is denied")
                {
                    continue;
                }

                size++;
//
                //getDates(html);
                int a = 0, b = 0;
                //Using this to remove the html tags
                //Referred to: https://stackoverflow.com/questions/49333136/removing-html-tags-from-a-string-of-text

                for (int a = b; a < html.length(); a++)
                {
                    if (html[a] == '<')
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
                }
                //stripUnicode(html);


                //string s = "søme string";
                //html = Regex.Replace(html, @"[^\u0000-\u007F]+", string.Empty);
               // Regex regex = new Regex(@"[^a-zA-Z0-9\s]", (RegexOptions)0);
                    //return regex.Replace(html, "");
                submissionDate = html;
                char word[html.length() +1];
                strcpy(word, &html[0]);
                removeStopWords(word); //Adding all of the words that aren't stop words to the documentWords vect
                if(structureChoice == 1)
                {
                    stemDocWordstoAVL(p);
                }
                else {
                    stemDocWordstoHash(p);
                }
                //stemDocWords();
                //At this point need to send to index handler
                //sendToIndex();
               //delete [] word;



            }
            file.close();
        }
        //file.close();
       closedir(point);
    }
    //closedir(point);
    //indexTree.print();
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
        IndexWord newObj(temp, docID, title, url);
        indexTree.insert(newObj);
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

void DocParse::removeStopWords(char *arr)
{
    //Adding all of the words that aren't stop words to the documentWords vect
    char * temp;
    temp = strtok(arr, ".-;:,?><='()[]& \n");
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
            documentWords.push_back(temp2);
            //If not a stop word, it will add to the docWords vect
        }
        temp = strtok(nullptr, ".-;:,?><='()[]& \n");
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

void DocParse::stemDocWordstoAVL(Index * p)
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
        IndexWord newIndexObj(temp, docID, title, url);
        newIndexObj.addDocHTML(submissionDate, newIndexObj.getDocVect().size()-1);
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
        IndexWord newIndexObj(temp, docID, title, url);
        p->insert(newIndexObj);
        stemmedDocWords.push_back(temp);
    }
   // cout << "out of has function" << endl;
   // p->print();
}

int DocParse::getSize()
{
    return size;
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

AVL<IndexWord>& DocParse::getIndexTree() {
    return indexTree;
}

void DocParse::printWords()
{

}
