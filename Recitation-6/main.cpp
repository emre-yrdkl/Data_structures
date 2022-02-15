/* @Author
Student Name: Emre Yurdakul
Student ID : 150190030
Date: 11.01.2022 */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

string file_path;


bool perform_operation(char);
void print_menu();
void listProducts();
void listDay();

vector<string> strvector;
vector<string> strvector2;

map<string, double> mon;
map<string, double> tues;
map<string, double> wedn;
map<string, double> thurs;
map<string, double> fri;
map<string, double> satur;
map<string, double> sun;

bool sorting(const pair<string, double> &a, 
               const pair<string, double> &b) 
{ 
    return (a.second >= b.second); 
} 

int main(int argc, char* argv[])
{
    bool end = false;
    char choice;
    ifstream inFile;

    file_path = argv[1];

    inFile.open(file_path,ios::in);

    if (!inFile.is_open()) 
    {
        cerr << "File cannot be opened";
        
        return EXIT_FAILURE;
    }
    else{

        string s;

        while(1){
            inFile >> s;

            
            strvector.push_back(s);
            strvector2.push_back(s);

            if(inFile.eof()){

                break;
            }
        }
    }

    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }
    
    inFile.close();
    return EXIT_SUCCESS;

}

void print_menu()
{
    cout << "Choose an operation" << endl;
    cout << "L: List 5 products with the highest revenue for total" << endl;
    cout << "D: List 5 products with the highest revenue for each day" << endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {L, D, E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    string strday;

    switch (choice)
    {
    case 'L':
    case 'l':
        listProducts();
        break;
    case 'D':
    case 'd':
        listDay();
        break;
    case 'E':
    case 'e':
            terminate = true;
        break;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}

void listProducts()
{

    map<string, double> total;

    for(auto i=strvector.begin()+4; i!=strvector.end();i+=4){


        if(total.find(*i)==total.end()){
            double first = stod(*(i+1));
            double second = stod(*(i+2));
            double max = first * second;
            total.insert(pair<string, double>(*i, max));
        }

        else{
            
            total[*i] = total[*i] + stod(*(i+1)) * stod(*(i+2));
        }

    }


  vector<pair<string, double>> vec;

  map<string, double> :: iterator it2;

  for (it2=total.begin(); it2!=total.end(); it2++) 
  {
    vec.push_back(make_pair(it2->first, it2->second));
  }

  sort(vec.begin(), vec.end(), sorting); 

    cout<<"5 products with the highest revenue for total are:"<<endl;
	for (int i = 0; i < 5; i++)
	{
        cout<< fixed;
		cout << vec[i].first << " " << setprecision(2) << vec[i].second << endl;
	}

}

void sortAndPrint(map<string, double> &temp_map){//sorting high to low and printing highest 5 items

    vector<pair<string, double>> vec2;

    map<string, double> :: iterator it3;

    for (it3=temp_map.begin(); it3!=temp_map.end(); it3++) 
    {
        vec2.push_back(make_pair(it3->first, it3->second));
    }

    sort(vec2.begin(), vec2.end(), sorting); 


        for (int i = 0; i < 5; i++)
        {
            cout<< fixed;
		    cout << vec2[i].first << " " << setprecision(2) << vec2[i].second << endl;
        }

}

void add(map<string, double> &temp_map, string day){//adding items in map

    for(auto i=strvector.begin()+4; i!=strvector.end();i+=4){

        
        if(temp_map.find(*i)==temp_map.end() && *(i+3)==day){
            double first = stod(*(i+1));
            double second = stod(*(i+2));
            double max = first * second;
            temp_map.insert(pair<string, double>(*i, max));
        }

        else if(*(i+3)==day){
            temp_map[*i] = temp_map[*i] + stod(*(i+1)) * stod(*(i+2));
        }

    }

}


void listDay()
{
    

        add(mon,"Monday");//adding items to monday's map
        add(tues,"Tuesday");//adding items to tuesday's map
        add(wedn,"Wednesday");//adding items to wednesday's map
        add(thurs,"Thursday");//adding items to thurday's map
        add(fri,"Friday");//adding items to friday's map
        add(satur,"Saturday");//adding items to saturday's map
        add(sun,"Sunday");//adding items to sunday's map


        cout<<"5 products with the highest revenue for Monday are:"<<endl;
        sortAndPrint(mon);

        cout<<"5 products with the highest revenue for Sunday are:"<<endl;
        sortAndPrint(sun);

        cout<<"5 products with the highest revenue for Tuesday are:"<<endl;
        sortAndPrint(tues);

        cout<<"5 products with the highest revenue for Wednesday are:"<<endl;
        sortAndPrint(wedn);

        cout<<"5 products with the highest revenue for Thursday are:"<<endl;
        sortAndPrint(thurs);

        cout<<"5 products with the highest revenue for Friday are:"<<endl;
        sortAndPrint(fri);

        cout<<"5 products with the highest revenue for Saturday are:"<<endl;
        sortAndPrint(satur);

}