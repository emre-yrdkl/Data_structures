#include <iostream>
#include <stdio.h>
#include "linkedList.h"

using namespace std;

Node::Node(char letter){
    this->letter = letter;
    this->next = NULL;
}

char Node::get_data(){
    return this->letter;

}

void Node::set_data(char letter){
     this->letter=letter;

}

void Node::set_next(Node* next){
    this->next=next;
}

Node* Node::get_next(){
    return this->next;
}

void LinkedList::reorderList(){

    int checker;

    do {

    checker=0;

    Node* first = head;
    Node* sec = first->get_next();

    while(first != NULL && sec != NULL){

        char firstc = first->get_data();
        char secc = sec->get_data();
        
        if(firstc>secc){
            checker=1;

            char tmp= first->get_data();

            char s = sec->get_data();
            first->set_data(s);

            sec->set_data(tmp); 
            first = first->get_next();
            sec = sec->get_next(); 
            
        }
        else{
            first = first->get_next();
            sec = sec->get_next();
        }
        
    }
    }while(checker==1);


};

void LinkedList::removeDublicates(){
    
    Node* prev = head;

    Node* next = head->get_next();

    while (next != NULL)
    {
        if(prev->get_data()==next->get_data()){
            Node* check = next;
            next = next->get_next();
            prev->next = next;
            free(check);
        }
        else{
            prev = next;
            next = next->get_next();
        }
    }
    
};

void LinkedList::reverseList(){
    
    Node* prev=NULL;
    Node* curr= head;
    Node* next=head->next;

    while (curr!=NULL)
    {
        
        curr->set_next(prev);
        prev = curr;

        if(next!=NULL){
            
            curr= next;
            next = next->get_next();

        }
        else
            break;

    }
    head = prev;

};

void LinkedList::printList(){
    Node* temp = head;
    while(temp != NULL){
        cout<<temp->letter<<" ";
        temp = temp->next;
    }
    cout<<endl;
};