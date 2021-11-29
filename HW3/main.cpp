//
//  main.cpp
//  Linked_List
//
//  Copyright © Tali Moreshet. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include "LinkedList.h"

int main(int argc, const char * argv[]) {

  /* Uncomment */
    LinkedList<int> *myLL = new LinkedList<int>(INT_MIN, INT_MAX);

    Node<int> *newNodeLoc;

    newNodeLoc = myLL->search(myLL->head, 3);
    myLL->insert(newNodeLoc, 3);
    newNodeLoc = myLL->search(myLL->head, 2);
    myLL->insert(newNodeLoc, 2);
    newNodeLoc = myLL->search(myLL->head, 2);
    myLL->insert(newNodeLoc, 2);

//    LinkedList<char> *myLL = new LinkedList<char>(CHAR_MIN, CHAR_MAX);
//    Node<char> *newNodeLoc;
//    LinkedList<signed char> *myLL = new LinkedList<signed char>(SCHAR_MIN, SCHAR_MAX);
//    Node<signed char> *newNodeLoc;
//
//    newNodeLoc = myLL->search(myLL->head, 'a');
//    myLL->insert(newNodeLoc, 'a');
//    newNodeLoc = myLL->search(myLL->head, 'z');
//    myLL->insert(newNodeLoc, 'z');
//    newNodeLoc = myLL->search(myLL->head, 'b');
//    myLL->insert(newNodeLoc, 'b');

    cout << "Linked list data: \n";
    myLL->printData();

    cout << "\n Linked List entire content: \n";
    myLL->print();
    delete myLL;

    
  return 0;
}
