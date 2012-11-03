#include "inference.h"

/* @brief    to calculate the topic likelihood for single document
 * @param    word Topic Likelihood, topic document likelihood, document index
 * @retval   a vector of likihood in document and words
 */
vector<vector<double> > conditionalProb(
    vector<vector<double> > wordTopicParms ,
    vector<vector<double> > DocTopicParms,
    vector<unsigned int>  documentData,
    int docIndex,
    int K){
  double delta=0.9;
  double epsilon=(1-delta)/(K-1);

  //vector<vector<double> > wordTopicParms_Trans;//Dim: |word|*|topic|
  //vector<vector<double> > DocTopicParms_Trans;// Dim: |Doc |*|topic|

  //cout<<"X" <<endl;
  //wordTopicParms_Trans=vectorMatrixTranpose(wordTopicParms);
  //DocTopicParms_Trans= vectorMatrixTranpose(DocTopicParms);

  int lenDoc=documentData.size();
  vector <vector<double> > maML;
  for(int j=0;j<lenDoc;j++)//for all the words in the document, compute ML
  {
    maML.push_back(computeML(wordTopicParms, DocTopicParms, maML, documentData, delta, epsilon,
          K, j, docIndex));
  }

  vector <vector<double> > maMR;
  for(int j=lenDoc-1;j>=0;j--)//for all the words in the document, compute ML
  {
    maMR.push_back(computeMR(wordTopicParms, DocTopicParms, maMR, documentData, delta, epsilon,
          K, j, docIndex,lenDoc));
  }


  /*
     for(int i=0;i<1;i++)//For all document

     {
     vector<vector <double> > maML;
     int lenDoc=documentData[i].size();

     for(int j=0;j<lenDoc;j++)//for all the words in the document, compute ML
     {
     maML.push_back(computeML(wordTopicParms, DocTopicParms, maML, documentData[i], delta, epsilon,K, j, i));
     }
     vector<vector <double> > maMR;
     for(int j=lenDoc-1;j>=0;j--)//for all the words in the document, compute ML
     {
     maMR.push_back(computeMR(wordTopicParms, DocTopicParms, maMR, documentData[i], delta, epsilon,K, j, i,lenDoc));
     }
     for(int z1=0;z1<maMR.size();z1++)
     {
     for(int z2=0;z2<maMR[z1].size();z2++)
     {
     cout<<maML[z1][z2]<<" ";
     }
     cout<<endl;
     }
     }*/

#if (_DEBUG_ == 11)
  //  cout << "_DEBUG_ 11 num of rows   " << wordTopicParms.size()<< endl;
  //  cout << "_DEBUG_ 11 num of columns" << wordTopicParms[0].size()<< endl;

  for(int z1=0;z1<maML.size();z1++)
  {
    for(int z2=0;z2<maML[z1].size();z2++)
    {
      cout<<maML[z1][z2]<<" ";
    }
    cout<<endl;
  }
#endif

  vector <double> tmpVector;
  vector <double> resultVector;
  vector <vector<double> > resultProb;
  vector <vector<double> > wordParmsForDoc;
  double logC=0;
  // ----- determine the word topic ----- //
  wordParmsForDoc = getWordProb(wordTopicParms,documentData,K);
  wordParmsForDoc = vectorMatrixTranpose(wordParmsForDoc);
  for (int i = 0; i < lenDoc; i++) {
    tmpVector = vectorElementSum(wordParmsForDoc[i],DocTopicParms[docIndex]);
    tmpVector = vectorElementSum(maML[i],tmpVector);
    tmpVector = vectorElementSum(maMR[lenDoc-1-i], tmpVector);
    logC = vectorLogSum(tmpVector);  

    for (int i = 0; i < tmpVector.size(); i++) {
      resultVector.push_back(tmpVector[i]-logC);
    }
    resultProb.push_back(resultVector);
    tmpVector.clear();
    resultVector.clear();
  }

  return resultProb;
}





vector<double> computeMR(vector<vector<double> > &wordTopicParms,
    vector<vector<double> > &DocTopicParms, vector<vector<double> >& maMR,
    vector<unsigned int> & singleDocumentData,
    double delta, double epsilon, int K, int inJ, int inDocIndex, int lenDoc) {
  //K:# of topics, t:=index of document (1~),T:=documentLength
  double sumOfLN_PnWnEpsi=0;
  vector<double> singleWordMR(K,0);

  if((lenDoc-inJ)==1)
    return singleWordMR;
  else
  {
    //Compute the simmation of all p_w|z * p_d|z * epsilon`
    int i=0;
    sumOfLN_PnWnEpsi=log(epsilon)+ \
                     wordTopicParms[i][singleDocumentData[inJ]-1]+DocTopicParms[i][inDocIndex]+ \
                     maMR[lenDoc-inJ-2][i];
    for(i=1;i<K;i++)
    {
      double temp=log(epsilon)+ \
                  wordTopicParms[i][singleDocumentData[inJ]-1]+DocTopicParms[i][inDocIndex]+ \
                  maMR[lenDoc-inJ-2][i];
      sumOfLN_PnWnEpsi=sumlog(sumOfLN_PnWnEpsi,temp );

    }
    for(int i=0;i<K;i++)
    {
      double temp2=log(delta-epsilon)+ \
                   wordTopicParms[i][singleDocumentData[inJ]-1]+DocTopicParms[i][inDocIndex]+ \
                   maMR[lenDoc-inJ-2][i];
      //cout<<sumOfLN_PnWnEpsi<<" "<<temp2;
      singleWordMR[i]=sumlog(sumOfLN_PnWnEpsi,temp2);
      //cout<<singleWordMR[i]<<" ";
    }
    return singleWordMR;
  }
}







vector<double> computeML(vector<vector<double> > &wordTopicParms,
    vector<vector<double> > &DocTopicParms, vector<vector<double> >& maML,
    vector<unsigned int> & singleDocumentData,
    double delta, double epsilon, int K, int inJ, int inDocIndex) {
  //K:# of topics, t:=index of document (1~),T:=documentLength
  double sumOfLN_PnWnEpsi=0;
  vector<double> singleWordML(K,0);
  /*for (unsigned int i=0;i<singleDocumentData.size();i++)
    {
    cout<<i<<" "<<singleDocumentData[i]<<endl;;
    }
    cout<<"---"<<endl;*/
  if(inJ==0)
    return singleWordML;
  else
  {
    //Compute the simmation of all p_w|z * p_d|z * epsilon
    int i=0;
    sumOfLN_PnWnEpsi=log(epsilon)+ \
                     wordTopicParms[i][singleDocumentData[inJ]-1]+DocTopicParms[i][inDocIndex]+ \
                     maML[inJ-1][i];
    for(i=1;i<K;i++)
    {
      double temp=log(epsilon)+ \
                  wordTopicParms[i][singleDocumentData[inJ]-1]+DocTopicParms[i][inDocIndex]+ \
                  maML[inJ-1][i];
      sumOfLN_PnWnEpsi=sumlog(sumOfLN_PnWnEpsi,temp );

    }
    for(int i=0;i<K;i++)
    {
      double temp2=log(delta-epsilon)+ \
                   wordTopicParms[i][singleDocumentData[inJ]-1]+DocTopicParms[i][inDocIndex]+ \
                   maML[inJ-1][i];
      //out<<sumOfLN_PnWnEpsi<<" "<<temp2;
      singleWordML[i]=sumlog(sumOfLN_PnWnEpsi,temp2);
      //cout<<singleWordML[i]<<" ";
    }
    return singleWordML;
  }
}







double sumlog( double a, double b) {
  if ((a-b)>6) return a;
  else if ((b-a)>6) return b;
  else return a + log(1+exp(b-a));
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

#if (_DEBUG_ == 3)
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

/* @brief   to find the most probobal assignment
 * @param   probability table
 * @retval  vector of unsigned int
 */
vector<unsigned int> mostProbobalAssign(vector<vector<double> > wordTopicProb ){
  double maxValue=-65536.0;
  unsigned int maxIndex= 65536;
  vector<unsigned int> result;

  for (int i = 0; i < wordTopicProb.size(); i++) {
    for (int j = 0; j < wordTopicProb[i].size(); j++) {
      if ( wordTopicProb[i][j] > maxValue) {
        maxValue = wordTopicProb[i][j];
        maxIndex = j;
      }
    }
    result.push_back(maxIndex);
    maxValue = -65536.0;
    maxIndex = 65536;
  }
  return result; 
}
