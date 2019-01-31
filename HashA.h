//HashA.h
//Written by Lu Han for CS 130A, F18
#ifndef HASHA_H
#define HASHA_H

#include <iostream>
#include <string>
#include <vector>

class Hash{
public:
	Hash(int size);

	void insert(std::string word);
	// insert command. Exceptional needed!!!

	void delete_v(std::string word);
	// delete command. Exceptional

	bool lookup(std::string word) const;

	void stat() const;


private:
	// capacity for the hash table array

	int num_insert = 0;

	int num_delete = 0;

	int num_collide_max = 0;

	int max_position = 0;

	std::vector<std::vector<std::string>> table;
	//hash table array of vectors. Each index in the array will contain
    // a vector. Each element in the vector contains an integer

	std::vector<int> randomHashing;
	// random Hashing number for universal hashing functions.

	void hash_helper();
	
	int size;

	int hash(std::string word) const;
	// Hash function that will return an index for the hash table.
};

#endif