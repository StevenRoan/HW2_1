#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
int main(int argc, char* argv[]){

  ifstream infile;
  string fileName;
  string token;
  string line;
  stringstream trans;
  vector<vector<unsigned int> > matrix;
  vector<unsigned int> veeector;
  int value;

  if (argc != 2) {
    cout << "error";
    return 1;
  }

  //cout << argv[1] << endl;
  infile.open(argv[1]);
  if (!infile.is_open()) {
    cout << "Unable to open the file: " << argv[1] << endl;
    return 1;
  }
  while(!infile.eof()) {
    getline(infile,line,'\n');
    while (!trans.eof()) {
      trans >> value;
      veeector.push_back(value);
    }
    matrix.push_back(veeector);
    veeector.clear();
    trans.clear();
    line.clear();
  }
  /*
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[i].size(); j++) {
      if (j==matrix.size()-1) {
        cout << matrix[i][j];
      }
      else {
        cout << matrix[i][j] << ' ';
      }
    }
    cout << endl;
  }*/







  return 0;
}
