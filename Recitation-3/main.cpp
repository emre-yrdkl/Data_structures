/* @Author
Student Name: Emre Yurdakul
Student ID : 150190030
Date: 09.11.2021 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

void infix_to_postfix(string,string&);
bool higher_priority(char,char);
double eval_postfix(string);
double evaluate(double,double,char);

int main(){
    string infix;
    string postfix;
    bool is_exit = false;

    while(!is_exit)
    {
        cout<<"Input the expression in infix: ";
        cin>>infix;

        if (infix == "E" || infix == "e") 
            is_exit = true;

        else
        {
            infix_to_postfix(infix, postfix);
            cout<<postfix<<endl;
            cout<<setprecision(2)<<fixed<<eval_postfix(postfix)<<endl; 
        }
        
        cin.clear();
        cin.ignore();
        infix.clear();
        postfix.clear();

    }
    return EXIT_SUCCESS;
}


void infix_to_postfix(string infix,string& postfix)
{
    stack<char> s;

    int counter = 0;
    
    while(infix[counter]){

        counter++;
    }

    for(int i=0; i<counter; i++){


        if(infix[i]!=42 && infix[i]!=43 && infix[i]!=45 && infix[i]!=47){

            postfix += infix[i];
        }

        else{

            if(s.empty()){
                s.push(infix[i]);
            }

            else{
                
                if(higher_priority(infix[i],s.top())){

                    s.push(infix[i]);

                }
                else{
                    
                    while(!higher_priority(infix[i],s.top()))
                    {
                        postfix += s.top();
                        s.pop();
                        
                        if(s.empty()){
                            s.push(infix[i]);
                            break;
                        }   
                    }

                    if(higher_priority(infix[i],s.top())){
                        s.push(infix[i]);
                        } 

                }
            }    

        }

        cout<<postfix<<endl;

    }

    while(!s.empty()){
        postfix += s.top();
        s.pop();
                                           
    }

}



 bool higher_priority(char first,char second){
    if((first=='*' || first=='/') && (second=='+' || second=='-'))
        return true;
  
    else return false;
} 

double eval_postfix(string expr){
    stack<double> s;
    double first, result;
    int counter1 = 0;
    
    while(expr[counter1]){

        counter1++;
    }

    for(int i=0; i<counter1; i++){

        if(expr[i]!=42 && expr[i]!=43 && expr[i]!=45 && expr[i]!=47){

            s.push(expr[i]-48);
        }

        else{
            first = s.top();

            s.pop();

            result = evaluate(s.top(),first,expr[i]);
            s.pop();

            s.push(result);
            
        }

    }

    return s.top();
}

double evaluate(double first,double second,char c){
    switch(c){
        case '*':
            return first*second;
        case '+':
            return first+second;
        case '-':
            return first-second;
        case '/':
            return first/second;
        default:
            return 0;
    }
}
