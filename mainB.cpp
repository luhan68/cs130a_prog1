#include "HashB.h"
#include "HashB.cpp"
#include <iostream>
#include <fstream>
#include <fstream>
#include <string>
#include <bitset> 

using namespace std;

bool IsPrime(int number)
{

    if (number == 2 || number == 3)
        return true;

    if (number % 2 == 0 || number % 3 == 0)
        return false;

    int divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= number)
    {

        if (number % (divisor - 1) == 0)
            return false;

        if (number % (divisor + 1) == 0)
            return false;

        divisor += 6;

    }

    return true;
}

int NextPrime(int a)
{

    while (!IsPrime(++a)) 
    { }
    return a;

}

int main() {

    string line = "";
        getline(cin,line);
        int divisor = log(atoi(line.c_str()))/log(2);
        int size = NextPrime(atoi(line.c_str()));
        Hash table(size, divisor);
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
