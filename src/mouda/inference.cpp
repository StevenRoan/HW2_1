#include "inference.h"

// -------------------------------------------------------------------------- //
// @Description: implementation of conditionalProb 
// @Provides: 
// -------------------------------------------------------------------------- //

vector<double> conditionalProb(
    vector<vector<double> > wordTopicLikelihood , 
    vector<double> DocTopicLikelihood, 
    unsigned int document,
    int K,
    double delta){ 

  double epsilon=(1-delta)/(K-1);
  // ----- construct the matrix A  ----- //
  vector<vector<double> > A;
  vector<double> rowA;
  for (int i = 0; i < K; i++) {
    for (int j = 0; j < K; j++) {
      if (j==i) rowA.push_back(delta);
      else rowA.push_back(epsilon);
    }
    A.push_back(rowA);
    rowA.clear();
  }
#ifdef _DEBUG_ 
#if (_DEBUG_ == 2)
  cout << "_DEBUG_ 2 A size(columns): " << A[0].size() << endl;
  cout << "_DEBUG_ 2 A size(rows):    " << A.size() << endl; 

  for (size_t i = 0; i < A.size(); i++) {
    size_t j;
    for (j = 0; j < A[i].size()-1; j++) {
      printf("%lf ",A[i][j]);
    }
    printf("%lf\n",A[i][j]);
  }
#endif
#endif

  //TODO
  vector<double> dummy;
  return dummy;
} 

// -------------------------------------------------------------------------- //
// @Description: implementation vectorProduct
// @Provides: 
// -------------------------------------------------------------------------- //

vector<double> vectorSum(vector<double> a, vector<double> b) {
  vector<double> result;
  if (a.size()*b.size()==0 || a.size() !=b.size()) {
    cerr << "error: input is NULL or un equal" << endl;
    return result;
  }
  for (int i = 0; i < a.size(); i++) {
    result.push_back(a[i]+b[i]);
  }
  return result;
}

// -------------------------------------------------------------------------- //
// @Description: matrix product
// @Provides: 
// -------------------------------------------------------------------------- //

vector<double> matrixProduct(double delta, double epsilon, vector<double> x) {
  vector<double> result;
  double allEpsilon = 0.0;
  for (int i = 0; i < x.size(); i++) {
    allEpsilon+=epsilon*x[i];
  }
  for (int i = 0; i < x.size(); i++) {
    result.push_back((allEpsilon-(x[i]*epsilon)+(x[i]*delta)));
  }
  return result; 
}

// -------------------------------------------------------------------------- //
// @Description:  ML
// @Provides: 
// -------------------------------------------------------------------------- //

vector<double> MLcompute(vector<double> wordTopic, vector<double> docTopic){
  vector<double> result;
  return result;
}


// -------------------------------------------------------------------------- //
// @Description: MR
// @Provides: 
// -------------------------------------------------------------------------- //

vector<double> MRcompute(vector<double> wordTopic, vector<double> docTopic){
  vector<double> result;
  return result;
}
