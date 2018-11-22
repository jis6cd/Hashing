//Jessica Shaughnessy
// jis6cd
// 10/15/2017
//hash.cpp
//lab section: 106 (3:30-4:45)

#include "hashTable.h"
#include <iostream>
#include <string>

using namespace std;

hashTable::hashTable(){
   vector<string> hash_vector;
}

void hashTable::resize_hash(int x){
  unsigned int p = x;
  if(checkprime(p)){
    hash_vector.resize(x);
  }
  else {
    int real_m = getNextPrime(p);
    hash_vector.resize(real_m);
  }
}

int hashTable::hash_function(string s){
  int hash = 7;
  for (int i = 0; i<s.length(); i++){
    hash= hash*31 +s[i];
  }
  int new_hash = hash%hash_vector.size();
  return new_hash;
}

void hashTable::insert(string s){
  int m = hash_function(s);
  if (hash_vector[m] == ""){
    hash_vector[m] = s;
  }
  else{
    while (hash_vector[m] != ""){
      m+=1;
      if (hash_vector.size() < m){
	m = 0;
      }
    }
    hash_vector[m] = s;
  }
}

bool hashTable::find(string s){
  int m = hash_function(s);
  while (m < hash_vector.size()){
    if (hash_vector[m] == s){
      return true;
    }
    else{
      m+=1;
    }
  }
  return false;
}
bool hashTable::checkprime(unsigned int p){
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}

int hashTable::getNextPrime (unsigned int n) {
    while ( !checkprime(++n) );
    return n; // all your primes are belong to us
}

