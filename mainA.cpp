#include "HashA.h"
#include "HashA.cpp"
#include <iostream>
#include <fstream>
#include <fstream>
#include <string>

using namespace std;

int main() {


     string line = "";
        getline(cin,line);
        int size = atoi(line.c_str()) + 1;
        Hash table(size);
        //initialize
        while (getline(cin, line)) {
            //classify the functions call upon string line
        	if(line.at(0) == 'i')
            {
        		table.insert(line.substr(line.find(" ")+1, line.length()));
            }
        	// need to trim the string and turn into 4-number array lists before use
        	else if(line.at(0) == 'd')
        		table.delete_v(line.substr(line.find(" ")+1, line.length()));
        	else if(line.at(0) == 'l')
        		table.lookup(line.substr(line.find(" ")+1, line.length()));
        	else if(line.at(0) == 's')
        		table.stat();
        }

    return 0;
}
