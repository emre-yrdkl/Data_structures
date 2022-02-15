/*

EMRE YURDAKUL
150190030


*/



#include <fstream>
#include <iostream>

#include "StudentsTrie.h"

using namespace std;

string arr[200];

int check=0;

TrieNode::TrieNode (const char& digit){
   this->digit = digit;
   for(int i=0; i<MAX_CHILDREN; children[i++] = NULL);
   this->index=-1; 
};

// Construct a StudentsTrie using the records in 'file_name' 
StudentsTrie::StudentsTrie ( const string& file_name  ) { 
    ifstream student_ids_file ( file_name );   // ifstream object for input file
    string current_student_id;

    root = new TrieNode('r');

    if( student_ids_file.is_open() ) {
        for(int i=1; student_ids_file >> current_student_id; i++ ) {
           
           arr[check] = current_student_id;
           
           insert_id(current_student_id, check); 
           check++;
        }
        student_ids_file.close();
    }
    else {
        cout << "File: " << file_name << " could NOT be opened!!";
        exit(1);
    }

    student_ids_file.close();
};

// Insert a student ID into the StudentsTrie 
void StudentsTrie::insert_id ( const string& student_id, int ind ) {
   
   TrieNode *temp = root;
 
    for (int i = 0; i < student_id.length(); i++)
    {
        int index = student_id[i]-'0';
        if (temp->children[index]==NULL){
            temp->children[index] = new TrieNode(student_id[i]);
            }
 
        temp = temp->children[index];
    }
    temp->index = ind;

}; 


void StudentsTrie::sorting(TrieNode* node, string arr[])
{

    if(node != NULL){    
 
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i] != NULL) {
 
            if (node->children[i]->index != -1)
                cout << arr[node->children[i]->index]<<" ";
 
            sorting(node->children[i], arr);
        }
    }
    }
}

// Print Student IDs in Trie in ascending order 
void StudentsTrie::print_trie(){

   sorting(root, arr);
   
}

// StudentsTrie Destructor
StudentsTrie::~StudentsTrie() {
   for (int i=0; i < MAX_CHILDREN; i++){
      if( root->children[i] ) delete root->children[i];
   };
};