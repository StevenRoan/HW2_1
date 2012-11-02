#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include "inference.h"
#include "writeData.h"

using namespace std;
int main(int argc, char* argv[]){

  ifstream dataFile;
  ifstream indexFile; 
  ifstream WordTopicFile;
  ifstream DocTopicFile;
  string fileName;
  string token;
  string line;
  stringstream trans;
  vector<vector<unsigned int> > matrix;   //To store document data
  vector<unsigned int> veeector;          
  vector<string> word;                    //To store word index 
  vector<vector<double> > WordTopicParms; //To store word topic conditional prob
  vector<vector<double> > DocTopicParms;  //To store top doc conditional prob
  vector<double> rowDouble; 
  int value;
  double logValue;

  if (argc != 7) {
    cout << "Usage: [Data]" << endl; 
    cout << "       [Index]"<< endl; 
    cout << "       [Word topic parms]" << endl; 
    cout << "       [Topic doc parms]"  << endl;
    cout << "       [Prob output file]" << endl; 
    cout << "       [Tag output file]" << endl; 
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
    cout << "Unable to open the file: " << argv[3] << endl;
    return 1;
  }

  DocTopicFile.open(argv[4]);
  if (!DocTopicFile.is_open()) {
    cout << "Unable to open the file: " << argv[4] << endl;
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
#if (_DEBUG_ == 9)
  for (size_t i = 0; i < matrix.size(); i++) {
    size_t j;
    for (j = 0; j < matrix[i].size()-1; j++) {
      cout << matrix[i][j] << ' ';
    }
    cout << matrix[i][j++] << endl;
  }
#endif
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
#if (_DEBUG_ == 100)
  for (int i = 0; i < word.size(); i++) {
    cout << word[i] << endl;
  }
#endif
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
#if (_DEBUG_ < 1)
  cout << "_DEBUG_ 0 WordTopicParms size(columns): " 
    << WordTopicParms[0].size() << endl;
  cout << "_DEBUG_ 0 WordTopicParms size(rows):    " 
    << WordTopicParms.size() << endl; 

  for (size_t i = 0; i < WordTopicParms.size(); i++) {
    size_t j;
    for (j = 0; j < WordTopicParms[i].size()-1; j++) {
      printf("%.10lf ",WordTopicParms[i][j]);
    }
    printf("%.10lf\n",WordTopicParms[i][j]);
  }
#endif
#endif

  // -------------------------------------------------------------------------- //
  // @Description: To read topic doc parameters
  // @Provides: 
  // -------------------------------------------------------------------------- //

  while (!DocTopicFile.eof()){
    getline(DocTopicFile,line,'\n');
    trans << line;
    while (!trans.eof()) {
      trans >> logValue;
      rowDouble.push_back(logValue);
    }
    DocTopicParms.push_back(rowDouble);
    rowDouble.clear();
    trans.clear();
    line.clear();
  }

#ifdef _DEBUG_ 
#if (_DEBUG_ < 1)
  for (size_t i = 0; i < DocTopicParms.size(); i++) {
    size_t j;
    for (j = 0; j < DocTopicParms[i].size()-1; j++) {
      printf("%.15lf ",DocTopicParms[i][j]);
    }
    printf("%.15lf\n",DocTopicParms[i][j]);
  }
#endif
#endif

  // ----- transport the topic doc parms matrix ----- //
  vector<vector<double> > DocTopicParms_p;
  DocTopicParms_p = vectorMatrixTranpose(DocTopicParms);

  // ----- inference ----- //
  // to calculate document for 1 to k, I focus on the document 0 first
  int documentIndex=1; 
  vector<vector<double> > Doc;
  vector<unsigned int> singlTopicIndex;
  vector<vector<unsigned int> > topicIndex;
  
  for (int i = 0; i < 10; i++) {
    Doc = conditionalProb(WordTopicParms,DocTopicParms_p[i],matrix[i],documentIndex,10,0.9);
    singlTopicIndex = mostProbobalAssign(Doc);
    topicIndex.push_back(singlTopicIndex);
  }
  // ----- write the inference result to the file ----- //

  if (!writeTagFile(argv[6],matrix,topicIndex)) {
    return 1;
  }

  if (!writeProbFile(argv[5],WordTopicParms)) {
    cerr << "Write data error" << endl;
    return 1;
  }
  return 0;
}
