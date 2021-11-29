// Mya Turner (mjturner@bu.edu) collaborated with Lesly Alcantara (leslyalc@bu.edu)
//  LinkedList.h
//  Linked_List
//
//  Copyright © Tali Moreshet. All rights reserved.
//
//  This is an implementation of an ordered Linked List class, which is made up of Nodes.
//  All classes are templated, such that their types may be provided at creation.
//  Nodes contain data (which doubles as key), and pointers to all directions.
//source(s): https://codereview.stackexchange.com/questions/20472/destructor-for-a-linked-list for destructor
#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <cstdlib>
#include <time.h>

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
};

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

    //Setting the tail's previous node as the head
    head->next->prev = head;
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

#endif /* LinkedList_h */