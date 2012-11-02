#include "inference.h"


/* @brief    to calculate the topic likelihood for single document
 * @param    word Topic Likelihood, topic document likelihood, document index
 * @retval   a vector of likihood in document and words
 */
vector<vector<double> > conditionalProb(
    vector<vector<double> > wordTopicLikelihood , 
    vector<double> DocTopicLikelihood, 
    vector<unsigned int> document,
    unsigned int docIndex,
    unsigned int K,
    double delta){ 

  double logC=0;
  vector<double> tmpVector;
  vector<double> resultVector;
  vector<vector<double> > tmpMatrix;
  vector<vector<double> > resultMatrix;

  double epsilon=(1-delta)/(K-1);

  for (unsigned int t = 0; t < document.size(); t++) {
    //unsigned int t=1;
    // ----- determine the word topic ----- //
    tmpMatrix = getWordProb(wordTopicLikelihood,document,K);
    tmpMatrix = vectorMatrixTranpose(tmpMatrix);

    // ----- compute conditional log likelihood ----- //
    tmpVector = vectorElementSum(tmpMatrix[t],DocTopicLikelihood);
    tmpVector = 
      vectorElementSum(
          MLcompute(tmpMatrix,DocTopicLikelihood,delta,epsilon,K,t+1,document.size()),
          tmpVector);
    tmpVector = 
      vectorElementSum(
          MRcompute(tmpMatrix,DocTopicLikelihood,delta,epsilon,K,t+1,document.size()), 
          tmpVector);
#if (_DEBUG_ == 6)
    cout << "resultVector: " << endl;
    for (int i = 0; i < tmpVector.size(); i++) {
      cout << tmpVector[i] << ' '; 
      //cout << exp(resultVector[i]) ;
    }
    cout << endl;
#endif
    // ----- compute the log likelihood C ----- //
    logC = vectorLogSum(tmpVector);  
#if (_DEBUG_ == 6)
    cout << "logC: " << logC << endl;
#endif
    // ----- comupte the conditinal probability ----- //
    for (int i = 0; i < tmpVector.size(); i++) {
      resultVector.push_back(tmpVector[i]-logC);
    }
    resultMatrix.push_back(resultVector);
    resultVector.clear();
  }
  // end loop
  return resultMatrix;
} 

/* @brief   get the correspond word top log prob.
 * @param   word topic log likelihood table
 *          document   
 *          topic number K
 * @retval  vector of word topic word topic log likelihood
 */
vector<vector<double> > getWordProb(vector<vector<double> > WTL, 
    vector<unsigned int> doc, unsigned int K) {

  vector<vector<double> > result;
  vector<double> forSingleTopic;

  for (int i = 0; i < K; i++) {
    for (int j = 0; j < doc.size(); j++) {
      forSingleTopic.push_back(WTL[i][doc[j]-1]);
    }
    result.push_back(forSingleTopic);
    forSingleTopic.clear();
  }

#if (_DEBUG_ == 10)
  cout << "_DEBUG_ 3 result size(columns): " << result[0].size() << endl;
  cout << "_DEBUG_ 3 result size(rows):    " << result.size() << endl; 
  for (int i = 0; i < result.size(); i++) {
    int j;
    for (j= 0; j < result[i].size(); j++) {
      cout << result[i][j] << ' ';
    }
    cout << result[i][j] << endl; 
  }
#endif
  return result;
}

/* @brief   to transpose the vector vector double matrix
 * @param   matrix a
 * @retval  matrix
 */
vector<vector<double> > vectorMatrixTranpose(vector<vector<double> >  a){
  vector<vector<double> > result;
  vector<double> rowDouble;
  for (size_t i = 0; i < a[0].size(); i++) {
    for (size_t j = 0; j < a.size(); j++) {
      rowDouble.push_back(a[j][i]);
    }
    result.push_back(rowDouble);
    rowDouble.clear();
  }
#if ( _DEBUG_ == 20)
  cout << "_DEBUG_ 4 a size(columns):      " << a[0].size()     << endl;
  cout << "_DEBUG_ 4 a size(rows):         " << a.size()        << endl; 
  cout << "_DEBUG_ 4 result size(columns): " << result[0].size()<< endl;
  cout << "_DEBUG_ 4 result size(rows):    " << result.size()   << endl; 
#endif

  return result;
}

/* @brief   summation of crosp. elements in two vectors (for log operation)
 * @param   vector a, vector b
 * @retval  vector 
 */
vector<double> vectorElementSum(vector<double> a, vector<double> b){
  vector<double> result;
  for (int i = 0; i < a.size(); i++) {
    result.push_back(a[i]+b[i]);
  }
  return result;
}

/* @brief   log summation of all the elements in a vector
 * @param   vector a
 * @retval  single double value
 */
double vectorLogSum(vector<double> a){
  double result=a[0];
  for (int i = 1; i < a.size(); i++) {
    result=sumlog(result, a[i]);
  }
  return result;
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
// @Description: sumlog
// @Provides: 
// -------------------------------------------------------------------------- //

double sumlog( double a, double b){
  if ( a-b > 6) return a;
  if ( b-a > 6) return b;
  return a + log(1+exp(b-a));  
}

double minuslog( double a, double b){
  if ( a-b > 6) return a;
  if ( b-a > 6) return b;
  return a + log(1-exp(b-a));

}

// -------------------------------------------------------------------------- //
// @Description:  ML
// @Provides: 
// -------------------------------------------------------------------------- //

vector<double> MLcompute(vector<vector<double> >wordTopic, 
    vector<double> docTopic, double delta, double epsilon, int K, int t, int T){

  vector<double> ML(K,0);
  double allEpsilon = 0.0;
  double temp=0.0;
  double logEpsilon=log(epsilon);
  double logDelta=log(delta); 

  for (int j = 1; j <= t-1; j++) {
    allEpsilon = logEpsilon+wordTopic[j-1][0]+docTopic[0]+ML[0];
    for (int i = 1; i < K; i++) {
      allEpsilon=sumlog(allEpsilon, logEpsilon+wordTopic[j-1][i]+docTopic[i]+ML[i]);
    }
    for (int i = 0; i < K; i++) {
      temp=minuslog(allEpsilon,(logEpsilon+wordTopic[j-1][i]+docTopic[i]+ML[i]));
      ML[i]=sumlog(temp,(logDelta+wordTopic[j-1][i]+docTopic[i]+ML[i]));
   }
  }
#if (_DEBUG_ == 4)
  for (int i = 0; i < ML.size(); i++) {
      cout << ML[i] << ' ';
  }
  cout << endl;
#endif
  return ML;
}


// -------------------------------------------------------------------------- //
// @Description: MR
// @Provides: 
// -------------------------------------------------------------------------- //

vector<double> MRcompute(vector<vector<double> > wordTopic, 
    vector<double> docTopic, double delta, double epsilon, int K, int t, int T){

  vector<double> MR(K,0);
  double allEpsilon = 0.0;
  double temp=0.0;
  double logEpsilon=log(epsilon);
  double logDelta=log(delta); 

  for (int j = T-2; j >= t-1; j--) {
    allEpsilon=logEpsilon+wordTopic[j+1][0]+docTopic[0]+MR[0];
    for (int i = 1; i < K; i++) {
      allEpsilon=sumlog(allEpsilon, logEpsilon+wordTopic[j+1][i]+docTopic[i]+MR[i]);
    }

    for (int i = 0; i < K; i++) {
      temp=minuslog(allEpsilon,(logEpsilon+wordTopic[j+1][i]+docTopic[i]+MR[i]));
      MR[i]=sumlog(temp,(logDelta+wordTopic[j+1][i]+docTopic[i]+MR[i]));
    }
  }
#if (_DEBUG_ == 5)
  for (int i = 0; i < MR.size(); i++) {
      cout << MR[i] << ' ';
  }
  cout << endl;
#endif
  return MR;
}

// -------------------------------------------------------------------------- //
// @Description: mostProbobalAssign
// @Provides: 
// -------------------------------------------------------------------------- //

vector<unsigned int> mostProbobalAssign(vector<vector<double> > wordTopicProb ){
  double maxValue=-65536.0;
  unsigned int maxIndex= 65536;
  vector<unsigned int> result;
#if (_DEBUG_ ==7)
  for (int i = 0; i < wordTopicProb.size(); i++) {
    for (int j = 0; j < wordTopicProb[i].size(); j++) {
      cout << wordTopicProb[i][j] << ' ' ;
    }
    cout << endl;
  }
#endif
  for (int i = 0; i < wordTopicProb.size(); i++) {
    for (int j = 0; j < wordTopicProb[i].size(); j++) {
      if ( wordTopicProb[i][j] > maxValue) {
        maxValue = wordTopicProb[i][j];
        maxIndex = j;
      }
    }
    result.push_back(maxIndex);
    maxValue=-65536.0;
    maxIndex = 65536;
  }
  return result; 
}
