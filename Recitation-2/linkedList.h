#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>

using namespace std;

class Node{
    public:

        Node* next;
        Node(char);
        char get_data();
        void set_data(char);
        Node* get_next();
        void set_next(Node*);
        char letter;
        
};


class LinkedList{


    public:
        Node* head;
        void reorderList();
        void removeDublicates();
        void reverseList();
        void printList();
};

#endif