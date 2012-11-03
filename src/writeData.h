#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

bool writeProbFile(char* fileName, vector<vector<double> > probTable);
bool writeTagFile(char* fileName, vector<vector<unsigned int> > dataMatrix,
    vector<vector<unsigned int> > assignment);
