#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
int main(int argc, char* argv[]){

  ifstream dataFile;
  ifstream indexFile; 
  string fileName;
  string token;
  string line;
  stringstream trans;
  vector<vector<unsigned int> > matrix;
  vector<unsigned int> veeector;
  vector<string> word; 
  int value;

  if (argc != 3) {
    cout << "Usage: [Data] [Index]" << endl; 
    return 1;
  }

  dataFile.open(argv[1]);
  if (!dataFile.is_open()) {
    cout << "Unable to open the file: " << argv[1] << endl;
    return 1;
  }

  indexFile.open(argv[2]);
  if (!dataFile.is_open()) {
    cout << "Unable to open the file: " << argv[2] << endl;
    return 1;
  }

// -------------------------------------------------------------------------- //
// @Description: read data file 
// @Provides: 
// -------------------------------------------------------------------------- //

  for (int i = 0; i< 2250; i++) {
    getline(dataFile,line,'\n');
    trans << line;
    while (!trans.eof()) {
      trans >> value;
      veeector.push_back(value);
    }
    matrix.push_back(veeector);
    veeector.clear();
    trans.clear();
    line.clear();
  }
#ifdef _DEBUG_
  for (size_t i = 0; i < matrix.size(); i++) {
    size_t j;
    for (j = 0; j < matrix[i].size()-1; j++) {
      cout << matrix[i][j] << ' ';
    }
    cout << matrix[i][j++] << endl;
  }
#endif
  dataFile.close();

// -------------------------------------------------------------------------- //
// @Description: read index file
// @Provides: 
// -------------------------------------------------------------------------- //

  while(!indexFile.eof()){
    getline(indexFile,line,'\n');
    trans << line;
    trans >> token; 
    word.push_back(token);
    trans.clear();
    line.clear();
    token.clear();
  }

#ifdef _DEBUG_
  for (int i = 0; i < word.size(); i++) {
    cout << word[i] << endl;
  }
#endif




  return 0;
}
