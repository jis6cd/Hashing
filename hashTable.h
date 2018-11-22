//Jessica Shaughnessy
//jis6cd
//10/15/2017
//hash.h
//labsection: 106 (3:30-4:45)

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class hashTable{
 private:
  vector<string> hash_vector;

 public:
  hashTable();
  void resize_hash(int x);
  int hash_function(string s);
  void insert(string s);
  bool find(string s);
  bool checkprime(unsigned int p);
  int getNextPrime(unsigned int n);


};
#endif
