//hash.cpp
//Written by Lu Han for CS 130A
#include "HashB.h"
#include <stdlib.h> 
#include <algorithm> 
#include <sstream>
#include <time.h> 
#include <stdio.h>
#include <math.h>  

using namespace std;

Hash::Hash(int size, int divisor){
	this->size = size;
	this->divisor = divisor;
	table.resize(size);
	groups = ceil(32.0/divisor);
    srand (time(NULL));
	for(int i = 0; i < groups; i++)
		randomHashing.push_back(rand() % size);
}


string decimalToBinary(int n)
{
    std::string binary = std::bitset<8>(n).to_string();
    return binary;
}

int binaryToDecimal(string bin){
	int dec = 0;
	int rem = 0;
	int base = 1;
    int num = atoi(bin.c_str());
    while (num > 0)
    {
        rem = num % 10;
        dec = dec + rem * base;
        base = base * 2;
        num = num / 10;
    }

    return dec;

}


int Hash::hash(string word) const{

    istringstream iss(word);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(iss, token, '.')) {
        if (!token.empty())
            tokens.push_back(token);
    }
    
    string binary = "";
    for(int i = 0; i < 4; i++)
    {
    	binary += decimalToBinary(atoi(tokens.at(i).c_str()));
    }

	// generate random coefficients
    string binarys[groups];
	int i = 0;
    int remain = 32 % divisor;
    if(remain != 0)
    {
    	binarys[0] = binary.substr(0,remain);
    	binary.erase(0,remain);
    	i = 1;
    }

    for(; i < groups; i++)
    {
    	binarys[i] = binary.substr(0,divisor);
    	binary.erase(0,divisor);
    }



    int accumulator = 0;
    
    for(int i = 0; i < groups; i++)
     {
       	accumulator += binaryToDecimal(binarys[groups - 1 - i])*randomHashing[i];
     }
 	int result = accumulator % size;
    
    return result;

}


void Hash::insert(string word)
{

	int index = hash(word);

	if(!table[index].empty())
	{
		for(int i = 0; i < table[index].size();i++)
		{
			if(table[index].at(i) == word)
			{
				std::cout << word << " already exists" << std::endl;
				return;
			}

		}
	}
		this->num_insert++;

		table[index].push_back(word);
		if(this->num_collide_max == table[index].size())
		{
			this->max_position = max(max_position,index);
		}else if(this->num_collide_max < table[index].size()){
			this->num_collide_max = table[index].size();
			this->max_position = index;
		}

}

void Hash::delete_v(string word) // once delete, no matter how many collision becomes 0?
{
	int index = hash(word);
	bool flag = true;
	if(!table[index].empty())
	{
		for(int i = 0; i < table[index].size();i++)
		{
			if(table[index].at(i) == word)
			{
				table[index].erase(table[index].begin()+i);
				this->num_delete++;
				flag = false;
			}

		}
	}

	if(flag)
		cout << "Error : could not delete "+ word +" because it does not existed." << endl;

}

bool Hash::lookup(string word) const{
	//cout << "LOOKUP is called"<< endl;
	int index = hash(word);

	if(!table[index].empty())
	{
		for(int i = 0; i < table[index].size();i++)
		{
			if(table[index].at(i) == word)
			{
				cout << word +": " + "found." << endl;
				return true;
			}

		}
	}
	cout << word +": " + "not found." << endl;

	return false;
}



void Hash::stat() const{
	// print random numbers used for hashing
	for(int i = 0; i < groups; i++)
	{
		cout << randomHashing[i];
		if(i != groups - 1)
			cout << " ";
		else cout << endl;
	}

	cout << this->num_insert << endl;
	//Number of items successfully inserted:
	cout << this->num_delete << endl;
	//Number of items successfully deleted:

	int empty = 0;
	int one_hash = 0;

	for(int j = 0; j < table.size(); j++)
	{
		if(table[j].empty())
			empty++;
		else if(table[j].size()== 1)
			one_hash++;
	}
	cout << empty << endl;
	// The number of empty slots in the hash table:
	cout << one_hash << endl;
	// The number of hash table slots with exactly 1 item:
	cout << this->num_collide_max << " " << this->max_position << endl;
	// The maximum number of collisions in the hash table: (count, location)
}



