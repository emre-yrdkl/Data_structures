/* 

Emre Yurdakul
150190030      


*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include "huffman.h"

using namespace std;

int token_counter=0;
int numToken = 0;
Node* head = new Node();
int tokenarr = 0;
 int token_num = -1;
PriorityQueue prior;

int numberChar(Node* temp){
    int x=0;
    Node* tempNode =temp;
    while(tempNode->next!=NULL){
        x++;

        tempNode=tempNode->next;
    }

    return x+1;
}

int Huffman::findindex(Token *arr,string elem){
	
    for(int i=0;i<token_count;i++){

        
        if(elem==(arr+i)->symbol){
            
            return i;
        }
    }
    return -1;
}

void Huffman::find_frequencies()
{
    int index = -1;
    ifstream file_obj; //object to read file
    file_obj.open("../input.txt",ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open()) {
        file_obj.open("input.txt",ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    while (file_obj.get(symbol)) 
    {
        string s;
        s.push_back(symbol);

        priority_queue.head=head;

        Node* tempnode = priority_queue.head;

        if(index==-1){
            
            index++;
            tempnode->token.symbol=s;
            tempnode->token.count++;
            
        }
        else{
            Node* tempnode2 = priority_queue.head;
            
            int check = 0;
            while(tempnode2!=NULL){
                if(tempnode2->token.symbol==s){
                    tempnode2->token.count++;
                    check++;
                }

                if(tempnode2->next!=NULL){
               tempnode2=tempnode2->next;
               }
               else{
                   break;
               }

            }

            if(check==0 && index!=-1){

                tempnode2->next = new Node();
                tempnode2=tempnode2->next;

                tempnode2->token.symbol=s;
                tempnode2->token.count++;
            }

        }
    numToken=numberChar(priority_queue.head);
    token_count=numToken;
    prior=priority_queue;
        
    }
    file_obj.close();
}

PriorityQueue::PriorityQueue()
{
    head = NULL;
    token_count = 0;
}

void PriorityQueue::push(Node *newnode)//push function
{
	Node* temphead = head;

    while(temphead!=NULL){

        if(temphead->next!=NULL){
            temphead= temphead->next;
        }
        else{
            break;
        }
    }

    temphead->next=newnode;
}

Node* PriorityQueue::pop()//pop function
{
    Node* temphead = head;
    
    head = head->next;

    temphead->next=NULL;
    return temphead;
}

int PriorityQueue::minimumInd(int sortInd)//find minimum index
{
    
    int min_val = 155;
    int min_ind = -1;
    int x = numberChar(head);
    for (int i=1; i < x+1; i++)
    {
        
        Node* current = head;
        pop(); 

            if (current->token.count <= min_val && (i-1) <= sortInd)
            {
                min_ind = (i-1);
                min_val = current->token.count;
            }

            push(current);

    }
    return min_ind;
}
  
void PriorityQueue::insertMin( int min_index)// insert minimum
{
    
    Node* min_val;

    int x = numberChar(head);
    
    for (int i = 1; i < x+1; i++)
    {
        Node* curr = head;
        pop();       
        if (i-1 != min_index){

            push(curr);

            }

        else{
            min_val = curr;
        }
    }
    push(min_val);
}



void Huffman::get_priority_queue()//it sorts the queue
{

int char_num = numberChar(priority_queue.head);

   if(char_num>=3){
     for (int i = 1; i <= char_num; i++)
    {
        int minIndex = priority_queue.minimumInd(char_num - i);
        
        priority_queue.insertMin( minIndex);

    }

}
    else if (char_num==2)
    {
        Node* nextPrio = priority_queue.head->next;

        if(priority_queue.head->token.count > nextPrio->token.count){

            Node* temp=priority_queue.head;


            priority_queue.pop();
            priority_queue.push(temp);
        }
    }
     
    prior = priority_queue;

}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = NULL;
}

Node * HuffmanBinaryTree::merge(Node *node1, Node *node2)
{
    Node* temp = new Node();

    temp->left=node1;
    temp->right=node2;

    temp->token.count= node1->token.count + node2->token.count;

    temp->token.symbol = node1->token.symbol + node2->token.symbol;


    prior.pop();
    prior.push(temp);
    prior.pop();

    return temp;


}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal)
{
    if(traversal!=NULL) 
    {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    delete_postorder_traversal(root);
    cout<<"Code with no memory leak ;)"<<endl;
    root = NULL;
}

void Huffman::get_huffman_tree()//it gets huffman tree 
{
    int char_num = numberChar(priority_queue.head);

     while(char_num!=0){

        priority_queue=prior;
        if(priority_queue.head->next==NULL){
            huffman_binary_tree.root=priority_queue.head;
            break;
        }
        else{
            get_priority_queue();
            priority_queue=prior;
            
            huffman_binary_tree.merge(priority_queue.head,priority_queue.head->next);
        }
       

    } 
}

void Huffman::get_codes(Node *traversal,string codepart)// it gives binary code for each leaf node
{    
    token_num=1;


    if(token_num>0){
        if(traversal!=NULL){

            traversal->token.code = codepart;

            get_codes(traversal->right,codepart + "1");
            
            get_codes(traversal->left,codepart + "0");

            if(traversal->right==NULL && traversal->left ==NULL){

                token_array[tokenarr]=traversal->token;

                tokenarr+=1;
            }


        }
    token_count = tokenarr;
    }

}

string Huffman::return_code(string target)
{
    int index = findindex(token_array,target);
    return token_array[index].code;
}

double Huffman::calculate_compression_ratio()
{
    double bit_required_before = 0;
    for(int i=0;i<token_count;i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for(int i=0;i<token_count;i++)
        bit_required_after += token_array[i].count * token_array[i].code.length();
    return bit_required_before / bit_required_after;
}
