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

  // for t == 1
  unsigned int t=1;
  // ----- determine the word topic ----- //
  tmpMatrix = getWordProb(wordTopicLikelihood,document,K);
  tmpMatrix = vectorMatrixTranpose(tmpMatrix);


  // ----- compute conditional log likelihood ----- //
  tmpVector = vectorElementSum(tmpMatrix[0],DocTopicLikelihood);
#if (_DEBUG_ == 5)
  for (int i = 0; i < tmpVector.size(); i++) {
    cout << tmpVector[i] << ' ' ; 
  }
  cout << endl;
#endif
  tmpVector = 
    vectorElementSum(
        MLcompute(tmpMatrix,DocTopicLikelihood,delta,epsilon,K,t,document.size()),
        tmpVector);
  tmpVector = 
    vectorElementSum(
        MRcompute(tmpMatrix,DocTopicLikelihood,delta,epsilon,K,t,document.size()), 
        tmpVector);
#if (_DEBUG_ == 5)
  for (int i = 0; i < tmpVector.size(); i++) {
    cout << tmpVector[i] << ' ' ; 
  }
  cout << endl;
#endif
  // end loop

  // ----- compute the log likelihood C ----- //
  logC = vectorLogSum(tmpVector);  
  // ----- comupte the conditinal probability ----- //
  for (int i = 0; i < tmpVector.size(); i++) {
    resultVector.push_back(tmpVector[i]/logC);
  }

#if (_DEBUG_ == 5)
  for (int i = 0; i < resultVector.size(); i++) {
    cout << resultVector[i] << ' '; 
  }
  cout << endl;
#endif

  //TODO
  return tmpMatrix;
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
  }
#if ( _DEBUG_ == 4)
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
  double result;
  for (int i = 0; i < a.size(); i++) {
    result+=sumlog(result, a[i]);
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
  return a + log10(1+exp(a-b));  
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

  for (int j = 0; j < t-1; j++) {
#if (_DEBUG_ == 5)
  cout << "here" << endl;
#endif
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
    vector<double> docTopic, double delta, double epsilon, int K, int t, int T){

  vector<double> MR(K,0);
  double allEpsilon = 0.0;
  double temp=0.0;

  for (int j = T-1; j > t+1; j--) {
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
