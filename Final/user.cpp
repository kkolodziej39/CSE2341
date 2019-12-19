/* Creator of file: Kyle Kolodziej
 * Last updated: December 18th, 2019
 *
 * DESCRIPTION OF USER:
 *
 *
 */

#include "user.h"
#include "index.h"
#include "hashindex.h"
#include "avlindex.h"
#include "query.h"
#include "avl.h"
#include "hash.h"
#include "indexword.h"
#include <iostream>

using namespace std;

User::User(char* argv[])
{
   commandLine = argv;
   //Set private data member in User to the command line
   //for later reference
}

void User::start(char * argv[])
{
    char userInputChoice[10];
    int choice;

    cout << "----------KYLE'S SEARCH ENGINE----------" << endl;
    cout << "Choose an option:" << endl;
    cout << "1.) Enter (1) for Maintenance Mode" << endl;
    cout << "2.) Enter (2) for Interactive Mode" << endl;
    cout << "Choice: ";
    cin.getline(userInputChoice, 10);
    choice = atoi(userInputChoice);

    while(choice != 1 && choice != 2)
    {
        cout << endl << "----------INVALID OPTION! TRY AGAIN!----------" << endl;
        cout << "Choose an option:" << endl;
        cout << "1.) Enter (1) for Maintenance Mode" << endl;
        cout << "2.) Enter (2) for Interactive Mode" << endl;
        cout << "Choice: ";
        cin.getline(userInputChoice, 10);
        choice = atoi(userInputChoice);
    }  //redisplays menu until choice = 1 or 2

    if(choice == 1) {
        maintenanceMode(argv);
    }  //runs maintenance mode if choice = 1

    else{
        interactiveMode(argv);
    }  //runs interactive mode if choice = 2
}

void User::maintenanceMode(char * argv[]) {
    int choice;

    cout << "----------MAINTENANCE MODE----------" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Add Opinion to Index" << endl;
    cout << "2. Clear Index" << endl;
    //cout << "3. Populate Index" << endl;
    cout << "Choice: ";
    cin >> choice;
      //displays menu and gets user input

    while(choice != 1 && choice != 2)
    {
        cout << endl << "----------INVALID OPTION! TRY AGAIN!----------" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Add Opinion to Index" << endl;
        cout << "2. Clear Index" << endl;
        //cout << "3. Populate Index" << endl;
        cout << "Choice: ";
        cin >> choice;
    }  //redisplays menu until choice = 1, 2, or 3

    if(choice == 1) {
        cout << "Please enter the path to the file: " << endl;
        cin.ignore();
        string inputPath;
        getline(cin,inputPath);
        char* newArg[3];
        char * word2 = new char[inputPath.length() +1];
        strcpy(word2, &inputPath[0]);
        newArg[1] = word2;
        newArg[2] = argv[2];
        cout << endl << "----------READING DIRECTORY----------" << endl << endl;
        start(newArg);
        delete [] word2;
        //cout << "Test: " << inputPath << endl;
        //cout << "Test 2: " << newArg[1] << endl;

    }
    else{
        /* Referenced clearing data in text file
         * https://stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c
         */
        ofstream outputFile2;
        outputFile2.open(argv[2], std::ostream::out | std::ostream::trunc);
        outputFile2.close();
        start(argv);
        //index->~Index();
        //start(argv);
    }  //clears index if option 2 is chosen
}

void User::interactiveMode(char * argv[]) {
    int choice2;
    //char numArray[100];
    ofstream outputFile;

    cout << "----------INTERACTIVE MODE----------" << endl;
    cout << "Choose an option:" << endl;
    cout << "1.) Enter (1) to load index into AVL Tree" << endl;
    cout << "2.) Enter (2) to load index into Hash Table" << endl;
    cout << "Choice: ";
    cin >> choice2;
    //cin.getline(numArray, 100);
    //choice2 = atoi(numArray);

    while(choice2 != 1 && choice2 != 2)
    {
        cout << endl << "----------INVALID OPTION! TRY AGAIN!----------" << endl;
        cout << "Choose an option:" << endl;
        cout << "1.) Enter (1) to load index into AVL Tree" << endl;
        cout << "2.) Enter (2) to load index into Hash Table" << endl;
        cout << "Choice: ";
        //cin.getline(numArray, 100);
        //choice2 = atoi(numArray);
        cin >> choice2;
    }  //redisplays menu until choice = 1 or 2

      //AVL tree option
    if(choice2 == 1) {
        index = new AVLIndex();
        Index * paramPoint = index;
        DocParse parsingDocObj;
        parsingDocObj.readDoc(argv, paramPoint);
        outputFile.open(argv[2]);
        parsingDocObj.printTotalWords(outputFile);
        parsingDocObj.printTotalOpinions(outputFile);
        paramPoint->setStats(parsingDocObj.getTotalOpinionCount(), parsingDocObj.getTotalWordCount());
        index->save(outputFile);
        outputFile.close();

        cout << endl << endl<< "----------AVL Tree Loaded----------" << endl;
        Query queryObject(index);
        cin.ignore();
        queryObject.newSearch();

        /*cout << "Choose an option:" << endl;
        cout << "1.) Enter (1) for Search Query" << endl;
        cout << "2.) Enter (2) to Print Search Statistics" << endl;
        cout << "Choice: ";
        cin >> choice2;
        //cin.getline(numArray, 100);
        //choice2 = atoi(numArray);

        while(choice2 != 1 && choice2 != 2) {
            cout << "ERROR: Invalid choice! Try again!" << endl;
            cout << "Choose an option:" << endl;
            cout << "1.) Enter (1) for Search Query" << endl;
            cout << "2.) Enter (2) to Print Search Statistics" << endl;
            cout << "Choice: ";
            cin >> choice2;
            //cin.getline(numArray, 100);
            //choice2 = atoi(numArray);
        }  //redisplays menu until choice = 1 or 2

        if(choice2 == 1) {
            Query q(index);
            q.readQuery();
        }  //creates query object & uses it to call the readQuery function
        else{
            Query q(index);
            q.getStats();
        }  //returns search statistics*/
    }
      //Hash table option
    else{
        index = new HashIndex();
        Index * paramPoint = index;
        DocParse parsingDocObj;
        parsingDocObj.readDoc(argv, paramPoint);

        cout << "----------Hash Table----------" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Enter Search Query" << endl;
        cout << "2. Print Search Statistics" << endl;
        cout << "Choice: ";
        cin >> choice2;

        while(choice2 != 1 && choice2 != 2) {
            cout << "invalid choice, try again" << endl;
            cout << "Choose an option:" << endl;
            cout << "1. Enter Search Query" << endl;
            cout << "2. Print Search Statistics" << endl;
            cout << "Choice: ";
            cin >> choice2;
        }  //redisplays menu until choice = 1 or 2

        if(choice2 == 1) {
            Query q(index);
            q.readQuery();
        }  //creates query object & uses it to call the readQuery function

        else if(choice2 == 2) {
            Query q(index);
            q.getStats();
        }  //returns search statistics
    }
}

Index & User::returnIndex()
{
    return *index;
}
