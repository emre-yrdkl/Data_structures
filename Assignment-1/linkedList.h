/* @Author
Student Name: Emre Yurdakul
Student ID : 150190030
Date: 10.11.2021 */


#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class materialNode{
    public:
        char id;
        int weight;
        materialNode* next;
        void set_mat_next(materialNode*);
        materialNode* get_mat_next();
};

class wagonNode{
    public:
        int wagonId;
        materialNode* material;
        wagonNode* next;
        void set_wag_next(wagonNode*);
        wagonNode* get_wag_next();
        void wagonIdd(int);
        
};

class Train{  

    
    public:
        wagonNode* head;
        void create();
        void addMaterial(char,int);
        void deleteFromWagon(char, int); 
        void printWagon(); //Prints wagon info
};

#endif