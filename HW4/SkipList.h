//
//  SkipList.h
//  Skip_List
//
//  Copyright © Tali Moreshet. All rights reserved.
//
//
//  This is an implementation of a Skip List class, consisting of Linked Lists, which are made up of Nodes.
//  All classes are templated, such that their types may be provided at creation.
//  Nodes contain data (which doubles as key), and pointers to all directions.

#ifndef SkipList_h
#define SkipList_h

#include <iostream>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

template<class T>
class Node {
public:
    Node(const T& data);                            // constructor
    T data;                                         // node data, doubles as key
    Node<T> *next;                                  // node next pointer
    Node<T> *prev;                                  // node previous pointer
    Node<T> *up;                                    // node above pointer
    Node<T> *down;                                  // node below pointer
    void printData();                               // prints data value
    void print();                                   // prints entire node object content
};

template <class T>
class LinkedList {
public:
    LinkedList(T minVal, T maxVal);                 // constructor: accepts -infinity, +infinity values,
                                                    //  creates linked list with two corresponding nodes
    ~LinkedList();                                  // destructor
    Node<T>* search(Node<T>* location, T data);     // search for data starting at location, return node <= data
    Node<T>* insert(Node<T>* location, T data);     // insert node with data at new node to be placed directly 
                                                    //  after node with povided location, return new node
    void printData();                               // prints linked list data
    void print();                                   // prints linked list with all nodes pointers
    Node<T>* head;                                  // head of list
    Node<T>* tail;                                  //tail of list
    LinkedList<T> *down;                            //linked list down pointer
    LinkedList<T> *up;                              //linked list up pointer
};

template <class T>
class SkipList {
public:
    SkipList(T minVal, T maxVal);                   // constructor: accepts -infinity, +infinity values,
                                                    //  creates skip list with top-level only
    ~SkipList();                                    // destructor
    Node<T>* search(T data);                        // search for data, return node <= data (existing node, or location
                                                    //  where new node should be inserted in the bottom-most list)
    Node<T>* insert(T data);                        // insert node with data, return pointer if inserted, NULL if error
    void printData();                               // prints skip list data
    void print();                                   // prints skip list with all nodes pointers
    LinkedList<T>* addList(LinkedList<T>* current); //adds a list to the SkipList.  returns a pointer to top-most list
    LinkedList<T> *topList;                         // pointer to the top-most list
    LinkedList<T> *bottomList = topList;             // pointer to the bottom-most list, same as topList to begin with
    int height = 1;                                     //height of Skip Lists
    int randSeed = 330;                             // to be used as seed for the getRand() function
};

//returns 0 or 1 with a 50% chance 
//When it returns 1, insert the node to next level of the skiplist
int getRand(){
    return rand()%2;
}

/********************** From here down is the content of the LinkedList.cpp file: ***********************/

/****** Implementation of Node ******/

// Constructor
template<class T>
Node<T>::Node(const T& data)
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
    this->up = nullptr;
    this->down = nullptr;
}

// Print node's data value
template <class T>
void Node<T>::printData()
{
    cout << data << " ";
}

// Print entire node object content (data value, object's address, and all pointers)
template <class T>
void Node<T>::print()
{
    cout << " * " << data << ": [addr: " << this << " next: " << this->next << " prev: " << this->prev << " up: " << this->up << " down: " << this->down << "]  ";
}


/****** Implementation of linked list ******/
// Constructor
template <class T>
LinkedList<T>::LinkedList(T minVal, T maxVal)
{
    //Creating head node & assigning it minVal
    head = new Node<T>(minVal);

    //Setting tail, as head->next & assigning it maxVal
    head->next = new Node<T>(maxVal);
    this->tail = head->next;
    //Setting the tail's previous node as the head
    head->next->prev = head;

    //Setting the Linked List up and down pointer to null
    this->down = nullptr;
    this->up = nullptr;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    //Need to delete all values to delete linked list
    Node<T>* current = head;
    Node<T>* temp;

    //Iterate through Linked List deleting one Node at a time
    while(current != nullptr)
    {
        temp = current->next;
        delete current;
        current = temp;
    }

}

// search for data starting at location, return node <= data
template<class T>
Node<T>* LinkedList<T>::search(Node<T>* location, T data){
    Node<T>* current = location;

    // check we are still in bounds of the LinkedList to iterate through
    while(current != nullptr)
    {
        // check if current node's is larger already
        if(current->data > data)
        {
            return current->prev; // return node where new number should be placed
        }

            // if data is contained in the list
        else if(current->data == data){
            return current;
        }

            // otherwise keep iterating
        else{
            current = current->next;
        }
    }
    // data is not in the list and is greater than all current values in linked list
    return current->prev;
}


// insert node with data at new node to be placed directly
template<class T>
Node<T>* LinkedList<T>::insert(Node<T>* location, T data){
    // first, check if the given location is NULL
    if(location == nullptr){
        cout<< "please give a location that isn't NULL" << endl;
        return nullptr;
    }

    // check for dupes
    if(location->data == data){
        return nullptr;
    }

    //allocate new node & assign it given data
    Node<T> *inserted_node = new Node <T>(data);


    //Check if the preceding value is greater than the insertion value => return null
    if (location->data > inserted_node->data)
    {
        return nullptr;
    }

    // Otherwise make the inserted node's previous node the location node
    inserted_node->prev = location;

    // Make the inserted's next node the current location's next node
    inserted_node->next = location->next;

    // Make location's new next node the inserted node
    location->next = inserted_node;

    // And finally assign the inserted's next node, inserted node as its previous
    inserted_node->next->prev = inserted_node;

    return inserted_node;
}

// prints linked list data
template<class T>
void LinkedList<T>::printData(){
    Node<T>* current; // allocate index node
    current = head; // initialize to beginning of the linkedlist

    // check we are still in bounds of the LinkedList
    while(current != nullptr){
        // print each node data with node printData function
        current->printData();
        current = current->next; // iterate through the list
    }
}

// prints linked list with all nodes pointers
template<class T>
void LinkedList<T>::print(){
    Node<T>* current; // allocate index node
    current = head; // initialize to beginning of the linkedlist

    // check we are still in bounds of the LinkedList
    while(current != nullptr){
        // print each node using node print function
        current->print();
        cout << endl; //next line
        current = current->next; // iterate through the list
    }
}

/****** Skip List Implementation ******/

// constructor: accepts -infinity, +infinity values,
//  creates skip list with top-level only
template <class T>
SkipList<T>::SkipList(T minVal, T maxVal)
{
    //Creating toplist Linked List
    topList = new LinkedList<T>(minVal, maxVal);

    //Setting the seed
    srand(this->randSeed);
}

// destructor
template <class T>
SkipList<T>:: ~SkipList()
{
    // start at the leftmost node at topList
    Node<T> *current = topList->head;
    LinkedList<T> *search_list = topList;

    // while not on the bottom row
    while (current->down != nullptr) {

        //Need to delete all values to delete linked list
        Node<T>* current_node = search_list->head;
        Node<T>* temp;

        //Iterate through Linked List deleting one Node at a time
        while(current_node != nullptr)
        {
            temp = current_node->next;
            delete current_node;
            current_node = temp;
            //cout<<"deleted node"<<endl;
        }

        current = current->down;

    }
    
    //calling delete one more time once in the bottom most list
        Node<T>* current_node = search_list->head;
        Node<T>* temp;

        //Iterate through Linked List deleting one Node at a time
        while(current_node != nullptr)
        {
            temp = current_node->next;
            delete current_node;
            current_node = temp;
            //cout<<"deleted node"<<endl;
         }
}

// search for data, return node <= data (existing node, or location
//  where new node should be inserted in the bottom-most list)
template <class T>
Node<T>* SkipList<T>::search(T data) {
    // start at the leftmost node at topList
    Node<T> *current = topList->head;
    LinkedList<T> *search_list = topList;

    // while not on the bottom row
    while (current->down != nullptr) {

        current = search_list->search(current, data);

        current = current->down;
    }
    
    //calling search one more time once in the bottom most list
    //to check for data
    
    current = search_list->search(current, data);
    return current;
}

// insert node with data, return pointer if inserted, NULL if error
template <class T>
Node<T>* SkipList<T>::insert(T data)
{
    //Using search function to find location for new data
    Node<T>* inserted_node= search(data);

    //If node with data already exists in the Skip List, return nullptr
    if(inserted_node->data == data){
        return nullptr;
    }

    //Always adding to the bottom list,
    //Adding to the bottom most list using Linked List insert function
    Node<T>* new_node = bottomList->insert(inserted_node, data); //returns pointer to new_node;

//    //Create new node pointer for data node to insert into higher levels
//    Node<T>* data_node = new_node;
//
//    //If bottomList up is null, add topList to Skip List
//    if(bottomList->head->up == nullptr)
//    {
//        topList = addList(topList);
//    }
//    /*Coin Toss */
//    //If coin toss is a head, add data node to the next level, else keep Skip List the same
//    //If the height of the SkipList is less or equal to levels, add new topList
//
//    //Keeping track of level for insertion in coin toss
//    int at_level = 2;
//    int coin = getRand();
//
//    //initial level, one above the bottomList
//    LinkedList<T>* current_level = bottomList->up;
//
//    while (coin == 1)
//    {
//        //search for where to put the data in current level of Skip List
//        //Then insert into current level
//        Node<T>* location = current_level->search(current_level->head, data);
//        data_node->up = current_level->insert(location, data);
//
//        //Connecting node in new linked list to the lower linked list
//        data_node->up->down = data_node;
//
//        //Changing data_node to new data node in the next level
//        data_node = data_node->up;
//
//        //if height of the Skip List equals current level, create new topList
//        if(this->height == at_level)
//        {
//            topList= this->addList(current_level);
//        }
//
//        at_level++;
//    }

    return inserted_node;
}

// prints skip list data
template <class T>
void SkipList<T>:: printData()
{
    // start at the leftmost node at topList
    Node<T> *current = topList->head;
    LinkedList<T> *this_list = topList;

    // while not on the bottom row
    while (current->down != nullptr) {
        this_list->printData();
        current = current->down; //drop down
        cout<< endl; //next line
    }
    
    //calling print one more time once in the bottom-most list
    //to check for data
    
    this_list->printData();

}

// prints skip list with all nodes pointers
template <class T>
void SkipList<T>:: print()
{
   // start at the leftmost node at topList
    Node<T> *current = topList->head;
    LinkedList<T> *this_list = topList;

    // while not on the bottom row
    while (current->down != nullptr) {

        this_list->print();
        current = current->down; //drop down
    }
    
    //calling print one more time once in the bottom-most list
    //to check for data
    
    this_list->print();
}

//adds a list to the SkipList.  returns a pointer to top-most list
template <class T>
LinkedList<T>* SkipList<T>:: addList(LinkedList<T>* current)
{
    //Creating new Linked List
    LinkedList<T>* newList = new LinkedList<T>(topList->head->data, topList->head->next->data);

    //Creating new list to connect to current list by connecting nodes
    newList->head->down = current->head; //connecting head of  new list to current head
    current->head->up = newList->head;

    newList->head->next->down = current->head->next; //connecting tail of new list to current tail
    current->head->next->up = newList->head->next;

    //incrementing height
    this->height++;

    //Connecting Linked Lists themselves
    newList->down = current;
    current->up = newList;

    //Making the new list the topList
    topList = newList;

    return newList;

}


#endif /* SkipList_h */
