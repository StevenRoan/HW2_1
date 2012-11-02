#include "writeData.h"

/* @brief   write probability table to the file 
 * @param   file name
 *          probability table
 *                  Word1 Word2 Word3 Word4 Word5 ....
 *          Topic1  0.xx  0.xx  0.xx  0.xx  0.xx
 *          Topic2  0.xx  0.xx  0.xx  0.xx  0.xx
 *          Topic3  0.xx  0.xx  0.xx  0.xx  0.xx
 *          Topic4  0.xx  0.xx  0.xx  0.xx  0.xx
 *          ...
 * @retval  boolean value to determine if the table is write out correctly
 *
 * @output format
 *
 *          0.xx  0.xx  0.xx  0.xx  0.xx
 *          0.xx  0.xx  0.xx  0.xx  0.xx
 *          0.xx  0.xx  0.xx  0.xx  0.xx
 *          0.xx  0.xx  0.xx  0.xx  0.xx
 */

bool writeProbFile(char* fileName, vector<vector<double> > probTable){
  ofstream outFile;
  outFile.open(fileName);


  for (size_t i = 0; i < probTable.size(); i++) {
    size_t j;
    for (j = 0; j < probTable[i].size()-1; j++) {
      outFile << probTable[i][j] << ' ' ;
    }
    outFile << probTable[i][j] << endl;
  }

  outFile.close();
  return true;
}


/* @brief   tag input word data file with the most probable topic
 * @param   filename
 *          source data matrix
 *          probability table
 *                  Word1 Word2 Word3 Word4 Word5 ....
 *          Topic1  0.xx  0.xx  0.xx  0.xx  0.xx
 *          Topic2  0.xx  0.xx  0.xx  0.xx  0.xx
 *          Topic3  0.xx  0.xx  0.xx  0.xx  0.xx
 *          Topic4  0.xx  0.xx  0.xx  0.xx  0.xx
 *          ...
 * @retval  boolean value to determine if the table is write out correctly
 *
 * @output format
 *          
 *          doc1 284/0 5101/1 11592/3 7170/4 10523/5 9453/5  
 *          doc2 288/1 4327/3 6297/4 9239/5 11445/6 8185/0 6185/3
 *          doc3 281/1 11220/3 4174/5 5101/2 11633/2 7881/3 2450/5
 *          doc4 209/2 8203/2 1169/2 8197/2 6843/1 2664/2 10776/2 
 *          ...
 *
 */

//TODO
bool writeTagFile(char* fileName, vector<vector<unsigned int> > dataMatrix,
    vector<vector<unsigned int> > assignment) {

  ofstream outFile;
  outFile.open(fileName);

  for (size_t i = 0; i < assignment.size(); i++) {
    size_t j;
    for (j = 0; j < dataMatrix[i].size(); j++) {
      outFile << dataMatrix[i][j] <<'/' << assignment[i][j]+1 << ' ' ;
    }
    outFile<<endl;
  }

  outFile.close();
  return true;
}
