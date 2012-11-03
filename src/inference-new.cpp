#include "inference.h"

/* @brief    to calculate the topic likelihood for single document
 * @param    word Topic Likelihood, topic document likelihood, document index
 * @retval   a vector of likihood in document and words
 */
vector<vector<double> > conditionalProb(
  vector<vector<double> > wordTopicParms ,
  vector<vector<double> > DocTopicParms,
  vector<unsigned int> documentData,
  int K){
  double logC=0;
  double delta=0.9;
  double epsilon=(1-delta)/(K-1);
  vector <vector<double> > resultProb;
  vector <vector<double> > wordLikeliOfEachDoc;
  //vector<vector<double> > wordTopicParms_Trans;//Dim: |word|*|topic|
  //vector<vector<double> > DocTopicParms_Trans;// Dim: |Doc |*|topic|

  //cout<<"X" <<endl;
  //wordTopicParms_Trans=vectorMatrixTranpose(wordTopicParms);
  //DocTopicParms_Trans= vectorMatrixTranpose(DocTopicParms);

  vector<vector <double> > maML;

  int lenDoc=documentData[i].size();
  for(int j=0;j<lenDoc;j++)//for all the words in the document, compute ML
  {
    maML.push_back(computeML(wordTopicParms, DocTopicParms, maML, documentData[i], delta, epsilon,
          K, j, i));
  }

  vector<vector <double> > maMR;
  for(int j=lenDoc-1;j>=0;j--)//for all the words in the document, compute ML
  {
    maMR.push_back(computeMR(wordTopicParms, DocTopicParms, maMR, documentData[i], delta, epsilon,
          K, j, i,lenDoc));
  }
#if (_DEBUG_ 11)
  for(int z1=0;z1<maMR.size();z1++)
  {
      for(int z2=0;z2<maMR[z1].size();z2++)
      {
         cout<<maMR[z1][z2]<<" ";
      }
      cout<<endl;
  }
#endif

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
