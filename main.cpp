#include<iostream>
#include<fstream>
#include<string.h>
#include "DFA.c"
#define LIMITING_LIMIT 1024
#define BUFFER_LIMIT 100000
using namespace std;

int main()
{
//buffer = new char[BUFFER_LIMIT];
int count = 0;
int pos = 0;
char data_buffer[LIMITING_LIMIT];
int list_of_path = 0;
char * LOG;
ifstream myfile;
string buffer = "";
string search_string;

cout << "Enter search string : ";
//search_string = (char *)malloc(sizeof(char) * 1024);
cin >> search_string;

myfile.open("output.txt");


if(myfile.fail())
{
cerr<<"file not found"<<endl;
return 1;
}

string item[LIMITING_LIMIT];
while(!myfile.eof())
{

myfile>>item[count];
//cout << "Path " << (count+1) << " is " << item[count] << endl;
count++;
}
myfile.close();


for(list_of_path=0; list_of_path < count; list_of_path++)
{
string line;
myfile.open(item[list_of_path].c_str());
//if(myfile.is_open()){ cout << "Opened file " << item[list_of_path] << endl; }
while(!myfile.eof() && myfile.is_open() && getline(myfile, line)){
    buffer = buffer + line;
}

//TODO:Need to call the routine of DFA here.

//cout << "FILE BUFFER " << buffer <<endl;
int result = simulate_lex(item[count].c_str(), buffer.c_str(), search_string.c_str());
buffer = "";
myfile.close();
//cout << "Contents of the File are : " << buffer << endl;
//execute the c code here
}

//cout << "Contents of the File are : " << buffer << endl;

}
