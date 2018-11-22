//Jessica Shaughnessy
//jis6cd
//10/14/2017
//wordPuzzle.cpp
//labsection: 106 (3:30-4:45)

//Big Theta runtime:rcw 

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "timer.h"
#include "hashTable.h"

using namespace std;
#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];

//forward declarations
bool readInGrid (string filename, int &rows, int &cols);
char* getWordInGrid (int startRow, int startCol, int dir, int len,
                     int numRows, int numCols);
hashTable my_hash;

int main(int argc, char* argv[]){
/////////initializing
  ifstream file(argv[1]);
  timer t1;
  int total_words_found = 0;
  string line;
  int dict_total = 0;
  int longest_word= 22;
  int rows;
  int cols;

////////reading in file:
  if (argc == 1){
    cout << "No files were given. Please give a dictionary filename and a grid filename (in that order!)."<< endl;
    exit(-1);
  }
  else if (argc == 2){
    cout << "There is a file missing! Please give a dictionary filename and a grid filename (in that order!)." << endl;
    exit(-1);
  }
  else if (argc == 3){
    //count number of words
    if(file.is_open()){
      while (getline(file, line)){
	dict_total += 1;
      }
      file.clear();
      file.seekg(0, ios::beg);
      
      my_hash.resize_hash(dict_total);
      string word = "";
      while (getline(file, line)){
	word = line;
	my_hash.insert(word);
	word = "";
      }
      file.close();
    }
  }
  bool result = readInGrid(argv[2], rows, cols);
  if (!result){
    cout << "The file can't be read" << endl;
    exit(1);
  }
  if (rows < 22 && cols <= rows){
    longest_word = rows;
  }
  else if (cols < 22 && rows < cols){
      longest_word = cols;
  }
  vector<string> answer_array;
  //starting timer;
  t1.start();
  for (int i = 0; i < rows; i++){
    for (int j = 0; j <cols; j++){
      for (int k = 0; k < 8; k++){
	for (int l = 3; l<=longest_word; l++){
	  char* word_char = getWordInGrid(i, j, k, l, rows, cols);
	  string word = word_char;
	  string t = "";
	  if (word.size() == l){
	  if (3 <= word.size()){
	  if(my_hash.find(word)){
	    string str_i = to_string(i);
	    string str_j = to_string(j);
	    if (k == 0){
	      t = "N ("+ str_i +", "+ str_j + "): \t"+ word;
	    }
	    else if (k == 1){
	      t = "NE ("+ str_i +", "+ str_j + "): \t"+ word;
	    }
	    else if (k==2){
	      t = "E ("+ str_i + ", "+ str_j + "): \t"+ word;
	    }
	    else if (k==3){
	      t="SE ("+ str_i +", "+ str_j  + "): \t" +word;
	    }
	    else if (k==4){
	      t="S ("+ str_i +", "+ str_j + "): \t"+ word;
	    }
	    else if (k==5){
	      t = "SW ("+ str_i +", "+ str_j+"): \t"+word;
	    }
	    else if (k==6){
	      t = "W ("+ str_i +", "+ str_j + "): \t"+ word;
	    }
	    else if (k==7){
	      t="NW ("+ str_i +", "+ str_j +"): \t" +word;
	    }
	    // read string into vector if not already in there
	    if (find(answer_array.begin(), answer_array.end(), t) == answer_array.end()){
	      answer_array.push_back(t);
	    }
	    total_words_found += 1;
	  }
	  }
	  }
	}
      }
    }
  }  
  //ending timer;
  t1.stop();

  //output
  //print answer_array
  for (int u = 0; u < answer_array.size(); u++){
    cout << answer_array[u] << endl;
  }
  cout << total_words_found << " words found" << endl;
  cout << "Found all words in " << t1.toString() << " seconds" << endl;
  //int t1_int = t1.getTime()*1000;
  //cout << t1_int << endl;
  return 0;

}

bool readInGrid (string filename, int &rows, int &cols) {
    // a C++ string to hold the line of data that is read in
    string line;
    // set up the file stream to read in the file (takes in a C-style
    // char* string, not a C++ string object)
    ifstream file(filename.c_str());
    // upon an error, return false
    if ( !file.is_open() )
        return false;
    // the first line is the number of rows: read it in
    file >> rows;
    //cout << "There are " << rows << " rows." << endl;
    getline (file,line); // eats up the return at the end of the line
    // the second line is the number of cols: read it in and parse it
    file >> cols;
    //cout << "There are " << cols << " cols." << endl;
    getline (file,line); // eats up the return at the end of the line
    // the third and last line is the data: read it in
    getline (file,line);
    // close the file
    file.close();
    // convert the string read in to the 2-D grid format into the
    // grid[][] array.  In the process, we'll print the grid to the
    // screen as well.
    int pos = 0; // the current position in the input data
    for ( int r = 0; r < rows; r++ ) {
        for ( int c = 0; c < cols; c++ ) {
            grid[r][c] = line[pos++];
            //cout << grid[r][c];
        }
        //cout << endl;
    }
    // return success!
    return true;
}

char* getWordInGrid (int startRow, int startCol, int dir, int len,
                     int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocataion.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static char output[256];
    // make sure the length is not greater than the array size.
    if ( len >= 255 )
        len = 255;
    // the position in the output array, the current row, and the
    // current column
    int pos = 0, r = startRow, c = startCol;
    // iterate once for each character in the output
    for ( int i = 0; i < len; i++ ) {
        // if the current row or column is out of bounds, then break
        if ( (c >= numCols) || (r >= numRows) || (r < 0) || (c < 0) )
            break;
        // set the next character in the output array to the next letter
        // in the grid
        output[pos++] = grid[r][c];
        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }
    // set the next character to zero (end-of-string)
    output[pos] = 0;
    // return the string (a C-style char* string, not a C++ string
    // object)
    return output;
}
