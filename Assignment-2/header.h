
#ifndef _H
#define _H

using namespace std;

class Token{
    public:
        string cityname; // To store city name
        int parentDistance = 0; // To store distance to the parent node
        int totalDistance = 0; // To store distance to the root node
};

class Node{
    public:
        Token token;  // To store token
        Node *left;   // To store address of left node
        Node *right;  // To store address of right node
};
#endif