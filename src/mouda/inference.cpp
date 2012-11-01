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

  vector<double> result;
  vector<double> conditionalZ;
  double epsilon=(1-delta)/(K-1);
  for (int i = 0; i < K; i++) {
//    conditionalZ.push_back(ML*);
  }

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
  return result; 
}

// -------------------------------------------------------------------------- //
// @Description: sumlog
// @Provides: 
// -------------------------------------------------------------------------- //

double sumlog( double a, double b){
  return a + log10(1+exp(a-b));  
}

// -------------------------------------------------------------------------- //
// @Description:  ML
// @Provides: 
// -------------------------------------------------------------------------- //

vector<double> MLcompute(vector<vector<double> >wordTopic, 
    vector<double> docTopic, double delta, double epsilon, int K, int t){

  vector<double> ML(K,0);
  double allEpsilon = 0.0;
  double temp=0.0;

  for (int j = 0; j < t-1; j++) {
    for (int i = 0; i < K; i++) {
      allEpsilon+=sumlog(allEpsilon, epsilon+wordTopic[j][i]+docTopic[i]+ML[i]);
    }
    for (int i = 0; i < K; i++) {
      temp=sumlog(allEpsilon,-1*(epsilon+wordTopic[j][i]+docTopic[i]+ML[i]));
      ML[i]=sumlog(temp,(delta+wordTopic[j][i]+docTopic[i]+ML[i]));
    }
  }
  return ML;
}


// -------------------------------------------------------------------------- //
// @Description: MR
// @Provides: 
// -------------------------------------------------------------------------- //

vector<double> MRcompute(vector<vector<double> > wordTopic, 
    vector<double> docTopic, double delta, double epsilon, int K, int t){

  vector<double> MR(K,0);
  double allEpsilon = 0.0;
  double temp=0.0;

  for (int j = t+1; j < K; j++) {
    for (int i = 0; i < K; i++) {
      allEpsilon+=sumlog(allEpsilon, epsilon+wordTopic[j][i]+docTopic[i]+MR[i]);
    }
    for (int i = 0; i < K; i++) {
      temp=sumlog(allEpsilon,-1*(epsilon+wordTopic[j][i]+docTopic[i]+MR[i]));
      MR[i]=sumlog(temp,(delta+wordTopic[j][i]+docTopic[i]+MR[i]));
    }
  }
  return MR;
}
