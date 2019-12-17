//David Hoffman
//last revision: 12/4/19
//Kyle kolodziej revise 12/8/19

#ifndef USER_H
#define USER_H
#include "index.h"
#include "avlindex.h"
#include "hashindex.h"
#include "docparse.h"
#include "avl.h"
#include "hash.h"

class User {
private:
    Index* index;
    char ** commandLine;
public:
    User(char * argv[]);
      //default constructor
    void start(char * argv[]);
      //starts program
    void maintenanceMode(char **);
      //runs maintenance mode
    void interactiveMode(char **);
      //runs interactive mode
    Index & returnIndex();
};

#endif // USER_H
