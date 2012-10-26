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

  cout << argv[1] << endl;
  infile.open(argv[1]);
  while(!infile.eof()) {
    getline(infile,line,'\n');
    while (!trans.eof()) {
      trans << line;
      trans >> value;
      veeector.pushback
    }
    trans.clear();
  }







  return 0;
}
