//David Hoffman
//last revision: 12/6/19

//Kyle kolodziej revised 12/8/19
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

User::User(char* argv[]) {
   commandLine = argv;
}

void User::start(char * argv[]) {
    int choice;

    cout << "----------SEARCH ENGINE----------" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Maintenance Mode" << endl;
    cout << "2. Interactive Mode" << endl;
    cout << "Choice: ";
    cin >> choice;
      //displays initial menu and gets user input

    while(choice != 1 && choice != 2) {
        cout << "invalid choice, try again" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Maintenance Mode" << endl;
        cout << "2. Interactive Mode" << endl;
        cout << "Choice: ";
        cin >> choice;
    }  //redisplays menu until choice = 1 or 2

    if(choice == 1) {
        maintenanceMode(argv);
    }  //runs maintenance mode if choice = 1

    else if(choice == 2) {
        interactiveMode(argv);
    }  //runs interactive mode if choice = 2
}

void User::maintenanceMode(char * argv[]) {
    int choice;

    cout << "----------MAINTENANCE MODE----------" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Add Opinion to Index" << endl;
    cout << "2. Clear Index" << endl;
    cout << "3. Populate Index" << endl;
    cout << "Choice: ";
    cin >> choice;
      //displays menu and gets user input

    while(choice != 1 && choice != 2 && choice != 3) {
        cout << "invalid choice, try again" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Add Opinion to Index" << endl;
        cout << "2. Clear Index" << endl;
        cout << "3. Populate Index" << endl;
        cout << "Choice: ";
        cin >> choice;
    }  //redisplays menu until choice = 1, 2, or 3

    if(choice == 1) {
        cout << "Please enter the path to the file: " << endl;
        cin >> choice;
    }  //

    else if(choice == 2) {
        index->~Index();
    }  //clears index if option 2 is chosen

    else if(choice == 3) {

    }  //
}

void User::interactiveMode(char * argv[]) {
    int choice;

    cout << "----------INTERACTIVE MODE----------" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Load index into AVL Tree" << endl;
    cout << "2. Load index into Hash Table" << endl;
    cout << "Choice: ";
    cin >> choice;

    while(choice != 1 && choice != 2) {
        cout << "invalid choice, try again" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Load index into AVL Tree" << endl;
        cout << "2. Load index into Hash Table" << endl;
        cout << "Choice: ";
        cin >> choice;
    }  //redisplays menu until choice = 1 or 2

      //AVL tree option
    if(choice == 1) {
        index = new AVLIndex();
        Index * paramPoint = index;
        DocParse parsingDocObj;
        parsingDocObj.readDoc(argv, 1, paramPoint);
        cout << "----------AVL Tree----------" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Enter Search Query" << endl;
        cout << "2. Print Search Statistics" << endl;
        //cout << "3. Print AVL Tree" << endl;
        cout << "Choice: ";
        cin >> choice;

        while(choice != 1 && choice != 2) {
            cout << "invalid choice, try again" << endl;
            cout << "Choose an option:" << endl;
            cout << "1. Enter Search Query" << endl;
            cout << "2. Print Search Statistics" << endl;
            //cout << "3. Print AVL Tree" << endl;
            cout << "Choice: ";
            cin >> choice;
        }  //redisplays menu until choice = 1 or 2

        if(choice == 1) {
            Query q(index);
            q.readQuery();
        }  //creates query object & uses it to call the readQuery function

        else if(choice == 2) {
            Query q(index);
            q.getStats();
        }  //returns search statistics
    }

      //Hash table option
    else if(choice == 2) {
        index = new HashIndex();
        Index * paramPoint = index;
        DocParse parsingDocObj;
        parsingDocObj.readDoc(argv, 2, paramPoint);

        cout << "----------Hash Table----------" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Enter Search Query" << endl;
        cout << "2. Print Search Statistics" << endl;
        cout << "Choice: ";
        cin >> choice;

        while(choice != 1 && choice != 2) {
            cout << "invalid choice, try again" << endl;
            cout << "Choose an option:" << endl;
            cout << "1. Enter Search Query" << endl;
            cout << "2. Print Search Statistics" << endl;
            cout << "Choice: ";
            cin >> choice;
        }  //redisplays menu until choice = 1 or 2

        if(choice == 1) {
            Query q(index);
            q.readQuery();
        }  //creates query object & uses it to call the readQuery function

        else if(choice == 2) {
            Query q(index);
            q.getStats();
        }  //returns search statistics
    }
}

Index & User::returnIndex()
{
    return *index;
}
