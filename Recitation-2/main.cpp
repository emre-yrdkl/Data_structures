/* @Author
Student Name: Emre Yurdakul
Student ID : 150190030
Date: 09.11.2021 */

#include <iostream> 
#include <stdlib.h>
#include <fstream>
#include "linkedList.h"

using namespace std;

int main(int argc, char* argv[]) {
	system("clear");// make this line as comment if you are compiling on Linux or Mac
	//system("cls"); // make this line as comment if you are compiling on Windows

    LinkedList newLinkedList;
    Node* firstN = newLinkedList.head;

    int firstadd = 0;
    char n;

    if (argc > 1) {
        //cout << "argv[1] = " << argv[1] << endl; 
    } else {
        cout << "No file name entered. Exiting...";
        return -1;
    }
    ifstream infile(argv[1]); //open the file
    
    if (infile.is_open() && infile.good()) {
        string line = "";
        while (getline(infile, line)){
            n = line[0];
            if(firstadd==0){
                newLinkedList.head=new Node(n);

                firstN = newLinkedList.head;

                firstadd+=1;
        
            }
            else{
                firstN->set_next(new Node(n));

                firstN = firstN->get_next();

            }
        }
        
    } else {
        cout << "Failed to open file..";
    }

    cout<<"Readed letters in linked list: ";
    newLinkedList.printList();

    newLinkedList.reorderList();
    cout<<"After reordering: ";
    newLinkedList.printList();

    newLinkedList.removeDublicates();
    cout<<"After removing dublicates: ";
    newLinkedList.printList();
    
    newLinkedList.reverseList();
    cout<<"Reversed list: " <<endl;
    newLinkedList.printList();


    return EXIT_SUCCESS;
}