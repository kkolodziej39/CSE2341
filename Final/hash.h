//Kyle Kolodziej
//last revision: 12/9/19

#ifndef HASH_H
#define HASH_H
#include "avl.h"
#include "indexword.h"
#include<iostream>
#include <string.h>
#include <cstddef>
#include <list>

using namespace std;

template<typename K, typename V>
class HashNode
{
public:
    V value;
    K key;
    HashNode * next;

    //Constructor of hashnode
    HashNode(K &key, V& value)
    {
        this->value = value;
        this->key = key;
        next = nullptr;
    }
    K& getKey()
    {
        return key;
    }
    V& getVal()
    {
        return value;
    }
    void setNext(HashNode*next)
    {
        this->next = next;
    }

    HashNode * getNextNode()
    {
        return next;
    }

    void setNodeVal(V & input)
    {
        value = input;
    }



};

//template for generic type
template<typename K, typename V>
class Hash
{
    //hash element array
    HashNode<K,V> **arr;
    int capacity;
    //current size
    int size;
    HashNode<K,V> *hashNode;
    list<IndexWord> * table;
    //AVL<IndexWord>** table;

public:
    Hash()
    {
        capacity = 1000;
        size=0;
        table = new list<IndexWord>[capacity];
        //table = new AVL<IndexWord>*[capacity];
    }
    // This implements hash function to find index
    // for a key
    ~Hash()
    {
        /*for(int i = 0; i < capacity; i++)
        {
            //delete table[i];
            HashNode<K, V> * newObj = table[i];
            while(newObj!= nullptr)
            {
                HashNode<K, V> * old = newObj;
                newObj = newObj->next;
                delete old;
            }
        }*/
        delete [] table;
    }

    //Ref : https://www.sanfoundry.com/cpp-program-hash-tables-binary-trees/
    int hashConvert(string & s)
    {
        unsigned int hashVal = 0;

        for (unsigned int i = 0; i < s.length(); i++)

            hashVal ^= (hashVal << 5) + (hashVal >> 2) + s[i];

        return hashVal % size;

    }

    void insertHash(const IndexWord &x)
    {
        IndexWord newWord = x;
        string input = newWord.getIndexWord();
        long temp = hashConvert(input);
        cout << "temp is : " << temp << endl;
        //table[temp]->insert(x);
    }



    //Function to add key value pair
    void insertNode(K key, V value)
    {
        //HashNode<K,V> *prevPointer;
        int hashIndex = hashConvert(key);
        HashNode<K,V> * previous = nullptr;
        HashNode<K,V> * temp = table[hashIndex];

        while(temp != nullptr)
        {
            previous = temp;
            temp = temp->next;
        }
        if(temp == nullptr)
        {
            temp = new HashNode<K,V>(key, value);

            if(previous == nullptr)
            {
                //if only one there, no collision to handle
                table[hashIndex] = temp;
                size++;
            }
            else {
                //if collision need to set the next
                previous->next = temp;
                size++;
            }
        }
        else {
            //just setting value
            temp->value=value;
        }
    }

    //Function to delete a key value pair
    V deleteNode(int key)
    {
        // Apply hash function to find index for given key
        int hashIndex = hashConvert(key);

        //finding the node with given key
        while(arr[hashIndex] != NULL)
        {
            //if node found
            if(arr[hashIndex]->key == key)
            {
                HashNode<K,V> *temp = arr[hashIndex];

                //Insert dummy node here for further use
                arr[hashIndex] = hashNode;

                // Reduce size
                size--;
                return temp->value;
            }
            hashIndex++;
            hashIndex %= capacity;

        }

        //If not found return null
        return nullptr;
    }

    //Function to search the value for a given key
    V getValueAtKey(int key)
    {
        // Apply hash function to find index for given key
        int hashIndex = hashConvert(key);
        int counter=0;
        //finding the node with given key
        while(arr[hashIndex] != nullptr)
        {    //int counter =0;
             if(counter++>capacity)  //to avoid infinite loop
                return nullptr;
            //if node found return its value
            if(arr[hashIndex]->key == key)
                return arr[hashIndex]->value;
            hashIndex++;
            hashIndex %= capacity;
        }

        //If not found return null
        return nullptr;
    }

    //Return current size
    int sizeofMap()
    {
        return size;
    }

    //Return true if size is 0
    bool isEmpty()
    {
        if(size == 0)
        {
            return true;
        }
        return false;
    }

    //Function to display the stored key value pairs
    void display()
    {
       //cout << "size is : " << size << endl;
        cout << "in print statement" << endl;
        for(int i=0 ; i<capacity ; i++)
        {
            //cout << "At key value " << table[i]->key << endl;
            //AVL<IndexWord> * temp = table[i];
            //temp->print();
            //HashNode<K, V> * newObj = table[i];
            /*while(newObj!= nullptr)
            {
                IndexWord indexObj = newObj->getVal();
                cout << "Value at key is..." << endl << indexObj << endl;
                newObj = newObj->getNextNode();
            }*/

               // cout << "key = " << arr[i]->key <<"  value = "<< arr[i]->value << endl;
        }
    }
};

#endif //HASH_H
