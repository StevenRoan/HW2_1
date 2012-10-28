#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;
int main(int argc, char* argv[]){

  ifstream dataFile;
  ifstream indexFile; 
  ifstream WordTopicFile;
  ifstream TopicDocFile;
  string fileName;
  string token;
  string line;
  stringstream trans;
  vector<vector<unsigned int> > matrix;   //To store document data
  vector<unsigned int> veeector;          
  vector<string> word;                    //To store word index 
  vector<vector<double> > WordTopicParms; //To store word topic conditional prob
  vector<vector<double> > TopicDocParms;  //To store top doc conditional prob
  vector<double> rowDouble; 
  int value;
  double logValue;

  if (argc != 5) {
    cout << "Usage: [Data] [Index] [Word topic parms] [Topic doc parms]" << endl; 
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

  WordTopicFile.open(argv[3]);
  if (!WordTopicFile.is_open()) {
    cout << "Unable to open the file: " << argv[2] << endl;
    return 1;
  }
  
  TopicDocFile.open(argv[4]);
  if (!TopicDocFile.is_open()) {
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

// -------------------------------------------------------------------------- //
// @Description: To read word topic parameters
// @Provides: 
// -------------------------------------------------------------------------- //

  while(!WordTopicFile.eof()){
    getline(WordTopicFile,line,'\n');
    trans << line;
    while(!trans.eof()) {
      trans >> logValue; 
      rowDouble.push_back(logValue);
    }
    WordTopicParms.push_back(rowDouble);
    rowDouble.clear();
    trans.clear();
    line.clear();
  }

#ifdef _DEBUG_
  for (size_t i = 0; i < WordTopicParms.size(); i++) {
    size_t j;
    for (j = 0; j < WordTopicParms[i].size()-1; j++) {
      printf("%.10lf ",WordTopicParms[i][j]);
    }
    printf("%.10lf\n",WordTopicParms[i][j]);
  }
#endif

// -------------------------------------------------------------------------- //
// @Description: To read topic doc parameters
// @Provides: 
// -------------------------------------------------------------------------- //

  while (!TopicDocFile.eof()){
    getline(TopicDocFile,line,'\n');
    trans << line;
    while (!trans.eof()) {
      trans >> logValue;
      rowDouble.push_back(logValue);
    }
    TopicDocParms.push_back(rowDouble);
    rowDouble.clear();
    trans.clear();
    line.clear();
  }

#ifdef _DEBUG_
  for (size_t i = 0; i < TopicDocParms.size(); i++) {
    size_t j;
    for (j = 0; j < TopicDocParms[i].size()-1; j++) {
      printf("%.15lf ",TopicDocParms[i][j]);
    }
    printf("%.15lf\n",TopicDocParms[i][j]);
  }
#endif




  return 0;
}
