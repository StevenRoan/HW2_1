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
  ifstream WordTopicFile;
  ifstream DocTopicFile;
  string fileName;
  string token;
  string line;
  stringstream trans;
  vector<vector<unsigned int> > matrix;   //To store document data
  vector<unsigned int> veeector;          
  vector<vector<double> > WordTopicParms; //To store word topic conditional prob
  vector<vector<double> > DocTopicParms;  //To store top doc conditional prob
  vector<double> rowDouble; 
  int value;
  double logValue;

  if (argc != 6) {
    cout << "Usage: [Data]" << endl; 
    cout << "       [Word topic parms]" << endl; 
    cout << "       [Doc  topic parms]"  << endl;
    cout << "       [Prob output file]" << endl; 
    cout << "       [Tag output file]" << endl; 
    return 1;
  }

  dataFile.open(argv[1]);
  if (!dataFile.is_open()) {
    cout << "Unable to open the file: " << argv[1] << endl;
    return 1;
  }

  WordTopicFile.open(argv[2]);
  if (!WordTopicFile.is_open()) {
    cout << "Unable to open the file: " << argv[3] << endl;
    return 1;
  }

  DocTopicFile.open(argv[3]);
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
    //trans >> value; //Not word
    while (!trans.eof()) {
      trans >> value;
      veeector.push_back(value);
    }
    matrix.push_back(veeector);
    veeector.clear();
    trans.clear();
    line.clear();
  }
  dataFile.close();

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


  // ----- inference ----- //
  // to calculate document for 1 to k, I focus on the document 0 first
  int K  = 10;
  vector<vector<double> > Doc;
  vector<unsigned int> singlTopicIndex;
  vector<vector<unsigned int> > topicIndex;

  for (int i = 0; i < 10; i++) {
    Doc = conditionalProb(WordTopicParms,DocTopicParms,matrix[i],i,K);
    singlTopicIndex = mostProbobalAssign(Doc);
    topicIndex.push_back(singlTopicIndex);
  }
  // ----- write the inference result to the file ----- //

  if (!writeTagFile(argv[5],matrix,topicIndex)) {
    cerr << "Write data error" << endl;
    return 1;
  }

  if (!writeProbFile(argv[4],WordTopicParms)) {
    cerr << "Write data error" << endl;
    return 1;
  }
  return 0;
}
