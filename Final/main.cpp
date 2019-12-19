/* Owner and Creator: Kyle Kolodziej
 * Date started: November 19th, 2019
 * Date updated: December 18th, 2019
 *
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"
#include "docparse.h"
#include "dirent.h"
#include "stemming.h"
#include "string_util.h"
#include "english_stem.h"
#include "safe_math.h"
#include "utilities.h"
#include "common_lang_constants.h"
#include "debug_logic.h"
#include "stemfunctionality.h"
#include "user.h"
#include "document.h"
#include"hash.h"

using namespace std;

/* COMMAND LINE PROMPT INSRUCTIONS:
 * 1.) First input should contain the path to a folder of Json files
 * 2.) Second input should contain the name of the Output File for the persistent index to be stored
 * 3.) Include optional 3rd input of search terms?
 *
 */

int main(int argc, char *argv[])
{
    User user(argv);
    user.start(argv);
   /* int first[] = {5,10,15,20,25};
      int second[] = {50,40,30,20,10};
      std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
      std::vector<int>::iterator it;

      //std::sort (first,first+5);     //  5 10 15 20 25
      //std::sort (second,second+5);   // 10 20 30 40 50

      it=std::set_union (first, first+5, second, second+5, v.begin());
                                                   // 5 10 15 20 25 30 40 50  0  0
      v.resize(it-v.begin());                      // 5 10 15 20 25 30 40 50

      std::cout << "The union has " << (v.size()) << " elements:\n";
      for (it=v.begin(); it!=v.end(); ++it)
        std::cout << ' ' << *it;
      std::cout << '\n';*/

    //char * command = argv[1];
   // string command = argv[1];
    //cout << "command is: " << command;
    //Index * index = new AVLIndex();
    //DocParse temp;
    //temp.readDoc(argv, 1, index);
    /*string a("algo");
    string b("12345");
    string c("Case 1");
    string d("123456");
    string u("url fill");

    IndexWord obj(a, b, c, u);
   // obj.printIndexWord();

    IndexWord obj2(a, b, c, u);
    IndexWord obj3(a, d, c, u);

    cout << endl << "printing tree" << endl;
    AVL<IndexWord> tree;
    tree.insert(obj);
    tree.print();
    cout << endl;
    tree.insert(obj2);
    tree.print();
    */
    /*
    cout << endl;
    tree.insert(obj3);
    tree.print();
    cout << endl;

    obj = obj + obj2;
    obj.printIndexWord();
    cout << endl;

    obj = obj + obj3;
    obj.printIndexWord();*/
    //DocParse temp;
    //temp.readDoc(argv);

    //Print total number of nodes (unique words)
    //avlTree.getNumOfNodes() ? funct

    //Print total number of docs parameter 1 (argv[2]) appears in
    //Need to stem it and have it go through upper to lower case transform
    //if contains funct is false can print 0
    //Else determine how many nodes at the matching node location

    //Print total number of appearences of the search query
    //if contains funct is false can print 0
    //else find the node and sum up the count of each node in DLL at that location

    return 0;
}
