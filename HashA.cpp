//hashA.cpp
//Written by Lu Han for CS 130A
#include "HashA.h"
#include <stdlib.h> 
#include <algorithm> 
#include <sstream>
#include <time.h> 
#include <stdio.h> 

using namespace std;


void Hash::hash_helper(){

	srand (time(NULL));
	 for(int i = 0; i < 4; i++)
         {
         	randomHashing.push_back(rand() % size + 0);
         	//cout << "randomHashing["<<i<<"]="<<randomHashing[i]<<endl;
         }
}


Hash::Hash(int size){
	this->size = size;
	table.resize(size);
	hash_helper();
}


int Hash::hash(string word) const{

    istringstream iss(word);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(iss, token, '.')) {
        if (!token.empty())
            tokens.push_back(token);
    }
    
     int accumulator = 0;
     for(int i = 0; i < 4; i++)
     {
       	accumulator += atoi(tokens[3 - i].c_str())*randomHashing[i];
    //   	cout << "accumulator: "<< accumulator << endl;
     }
 	int result = accumulator % size;
    //cout << "hash(word) = "<<result << endl;
    
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
	//	cout << "INSERT is called with index " << index<< endl;
		this->num_insert++;
		// if(table[hash(word)] != 0)
		// 	cout << "Error : could not insert "+ word +" because it's already existed." << endl;
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
	//cout << "DELETE is called"<< endl;
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
	for(int i = 0; i < 4; i++)
	{
		cout << randomHashing[i];
		if(i != 3)
			cout << " ";
		else cout << endl;
	}

	cout << this->num_insert << endl;
	//Number of items successfully inserted:
	cout << this->num_delete << endl;
	//Number of items successfully deleted:

	int empty = 0;
	int one_hash = 0;
	
	//cout << "Here comes the table!" << endl;

	for(int j = 0; j < table.size(); j++)
	{
	//	cout << j << " : "<< table[j].size() << endl;

		if(table[j].empty())
		{
			empty++;
	//		cout << "empty: " << j << " " << endl;
		}
		else if(table[j].size()== 1)
		{
			one_hash++;
	//		cout << "one hash: " << j << " " << endl;
			//cout << "one_hash:" << j << endl;
		}
	}
	cout << empty << endl;
	// The number of empty slots in the hash table:
	cout << one_hash << endl;
	// The number of hash table slots with exactly 1 item:
	cout << this->num_collide_max << " " << this->max_position << endl;
	// The maximum number of collisions in the hash table: (count, location)
}



