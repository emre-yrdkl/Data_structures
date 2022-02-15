/* @Author
Student Name: EMRE YURDAKUL
Student ID: 150190030
E-mail: yurdakule19@itu.edu.tr
Date: 29.12.21
*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <stdio.h>

#include "header.h"

using namespace std;

string arr[100];
int check=0;
string arr2[100];
int check2=0;

void createTree1(string input){// it adds friend1's cities to arr

    ifstream file_obj; //object to read file
    
    file_obj.open(input,ifstream::in);
    string s;
    if (!file_obj.is_open()) {
        file_obj.open(input,ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    file_obj>>s;

    while (!file_obj.eof()) 
    {
        arr[check] = s;
        check++;

        file_obj>>s;
        
    }
    file_obj.close();
}

void createTree2(string input){// it adds friend2's cities to arr2
    
    ifstream file_obj; //object to read file
    
    file_obj.open(input,ifstream::in);
    string s;
    if (!file_obj.is_open()) {
        file_obj.open(input,ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    file_obj>>s;

    while (!file_obj.eof()) 
    {
        arr2[check2] = s;
        check2++;

        file_obj>>s;
        
    }
    file_obj.close();
}

void printPreorder( Node* node)
{
    if (node == NULL)
        return;
 
    cout << node->token.cityname << " " <<node->token.totalDistance<<" ";
 
    printPreorder(node->left);
    printPreorder(node->right);
}

Node* nodeFinder(Node* head, string city){//it finds node of holding the given city

    if(head==NULL){
        return NULL;
    }

    if(head->token.cityname==city){
        return head;
    }

    Node* leftWay=new Node();
    Node* rightWay=new Node();

    leftWay=nodeFinder(head->left, city);
    rightWay= nodeFinder(head->right, city);

    if(leftWay!=NULL){
        return leftWay;
    }
    if(rightWay!=NULL){
        return rightWay;
    }

    return NULL;
    
}

Node* parentFinder(Node* head, string city){//it finds parent node of the node holding the given city

    if(head==NULL){
    return NULL;
    }

    if(head->left!=NULL && head->left->token.cityname==city){
        return head;
    }
    else if(head->right!=NULL && head->right->token.cityname==city){
        return head;
    }

    Node* leftWay = new Node();
    Node* rightWay = new Node();

    leftWay=parentFinder(head->left,city);
    rightWay=parentFinder(head->right,city);

    if(leftWay!=NULL){
        return leftWay;
    }
    if(rightWay!=NULL){
        return rightWay;
    }
    return NULL;
}

int minDistance[20];
string minCity[20];
int checker = 0;

void findMin(Node* node, Node* node2)// it adds cities and their total distance to arrays
{
    if (node == NULL){
        return;
    }
 
    Node* copyhead = new Node();
    copyhead = node;
    
    Node* temp= new Node();

    temp = nodeFinder(node2,copyhead->token.cityname);

    if(temp!=NULL){

            minDistance[checker] = copyhead->token.totalDistance + temp->token.totalDistance;
            minCity[checker] = temp->token.cityname;
            checker++;

    }
    
    findMin(node->left,node2);
    findMin(node->right,node2);
}



int main(int argc, char* argv[]){

    //creating friend1's tree
    createTree1(argv[1]);

    Node* head = new Node();
    Node* leftBranch= new Node();
    Node* rightBranch= new Node();

    head->token.cityname=arr[0];
    head->token.parentDistance=0;
    head->token.totalDistance=0;

    head->left=leftBranch;
    leftBranch->token.cityname= arr[1];
    leftBranch->token.parentDistance = stoi(arr[2]);
    leftBranch->token.totalDistance = stoi(arr[2]);


    head->right=rightBranch;
    rightBranch->token.cityname= arr[4];
    rightBranch->token.parentDistance = stoi(arr[5]);
    rightBranch->token.totalDistance = stoi(arr[5]);

    Node* temp = head;

    for(int i=6; i<check; i+=3){
        

        Node* tempParent= new Node();
        Node* tempChild= new Node();

        tempParent = nodeFinder(temp, arr[i]);
        tempChild = nodeFinder(temp, arr[i+1]);

        if(tempChild==NULL){

            Node* newChild= new Node();
            
            newChild->token.cityname=arr[i+1];
            
            newChild->token.parentDistance= stoi(arr[i+2]);
            newChild->token.totalDistance= tempParent->token.totalDistance + stoi(arr[i+2]);

            if(tempParent->left==NULL){
                tempParent->left=newChild;
            }
            else if(tempParent->right==NULL){
                tempParent->right=newChild;
            }
            
        }

        else{
            if(tempChild->token.totalDistance  >  tempParent->token.totalDistance + stoi(arr[i+2])){

                Node* delNode = new Node();

                delNode = parentFinder(temp, arr[i+1]);

                if(delNode->left==tempChild){

                    delNode->left=NULL;

                    if(tempParent->left==NULL){
                        tempParent->left = tempChild;
                    }
                    else if(tempParent->right==NULL){
                        tempParent->right = tempChild;
                    }
                    tempChild->token.totalDistance = tempParent->token.totalDistance + stoi(arr[i+2]);
                }

                else if(delNode->right==tempChild){

                    delNode->right=NULL;

                    if(tempParent->left==NULL){
                        tempParent->left = tempChild;
                    }
                    else if(tempParent->right==NULL){
                        tempParent->right = tempChild;
                    }
                    tempChild->token.totalDistance = tempParent->token.totalDistance + stoi(arr[i+2]);
                }

            }
            else{
                continue;
            }
        }
    }
//-----------------------------------------------------------------------------------------------------------

    //creating friend2's tree

    createTree2(argv[2]);

    Node* head2 = new Node();
    Node* leftBranch2 = new Node();
    Node* rightBranch2= new Node();

    head2->token.cityname=arr2[0];
    head2->token.parentDistance=0;
    head2->token.totalDistance=0;

    head2->left=leftBranch2;
    leftBranch2->token.cityname= arr2[1];
    leftBranch2->token.parentDistance = stoi(arr2[2]);
    leftBranch2->token.totalDistance = stoi(arr2[2]);

    head2->right=rightBranch2;
    rightBranch2->token.cityname= arr2[4];
    rightBranch2->token.parentDistance = stoi(arr2[5]);
    rightBranch2->token.totalDistance = stoi(arr[5])-1;

    Node* temp2 = head2;

    for(int i=6; i<check2; i+=3){

        Node* tempParent2= new Node();

        Node* tempChild2= new Node();

        tempParent2 = nodeFinder(temp2, arr2[i]);
        tempChild2 = nodeFinder(temp2, arr2[i+1]);


        if(tempChild2==NULL){
            
            Node* newChild= new Node();
            
            newChild->token.cityname=arr2[i+1];
            
            newChild->token.parentDistance= stoi(arr2[i+2]);
            newChild->token.totalDistance= tempParent2->token.totalDistance + stoi(arr2[i+2]);

            if(tempParent2->left==NULL){
                tempParent2->left=newChild;
            }
            else if(tempParent2->right==NULL){
                tempParent2->right=newChild;
            }
            
        }

        else{
            if(tempChild2->token.totalDistance  >  tempParent2->token.totalDistance + stoi(arr2[i+2])){

                Node* delNode2 = new Node();

                delNode2 = parentFinder(temp, arr2[i+1]);

                if(delNode2->left==tempChild2){
                    delNode2->left=NULL;

                    if(tempParent2->left==NULL){
                        tempParent2->left = tempChild2;
                    }
                    else if(tempParent2->right==NULL){
                        tempParent2->right = tempChild2;
                    }
                }

                else if(delNode2->right==tempChild2){
                    delNode2->right=NULL;

                    if(tempParent2->left==NULL){
                        tempParent2->left = tempChild2;
                    }
                    else if(tempParent2->right==NULL){
                        tempParent2->right = tempChild2;
                    }
                }

            }
            else{
                continue;

            }
        }
    }

  findMin(temp,temp2);

  int minNum=50;
  string lastCity;

  for(int i = 0; i<checker;i++){//finding city with minimum distance

      if(minDistance[i]<minNum){
          minNum = minDistance[i];
          lastCity= minCity[i];
      }
  }

  cout<<"FRIEND-1: ";
  printPreorder(temp);
  cout<<"\n"<<endl;
  cout<<"FRIEND-2: ";
  printPreorder(temp2);
  cout<<"\n"<<endl;

  cout<<"MEETING POINT: ";
  cout<<lastCity<<endl;
  cout<<"\n"<<endl;
  cout<<"TOTAL DURATION COST: ";
  cout<<minNum<<endl;

  free(head);
  free(head2);


    return 0;
}