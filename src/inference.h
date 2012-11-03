#include<iostream>
#include<vector>
#include<cmath>
#include<stdio.h>

using namespace std;

vector<vector<double> > conditionalProb(
    vector<vector<double> > wordTopicParms ,
    vector<vector<double> > DocTopicParms,
    vector<unsigned int> documentData,
    int docIndex,
    int K
    ); 

vector<double> computeML(vector<vector<double> > &wordTopicParms,
                         vector<vector<double> > &DocTopicParms, vector<vector<double> >& maML,
                         vector<unsigned int> & singleDocumentData,
                         double delta, double epsilon, int K, int inJ, int inDocIndex);

vector<double> computeMR(vector<vector<double> > &wordTopicParms,
                         vector<vector<double> > &DocTopicParms, vector<vector<double> >& maMR,
                         vector<unsigned int> & singleDocumentData,
                         double delta, double epsilon, int K, int inJ, int inDocIndex, int lenDoc); 


double sumlog(double a, double b);
vector<double> vectorElementSum(vector<double> a, vector<double> b);
double vectorLogSum(vector<double> a);
vector<vector<double> > getWordProb(vector<vector<double> > WTL, 
    vector<unsigned int> doc, unsigned int K);
vector<vector<double> > vectorMatrixTranpose(vector<vector<double> > a);

vector<unsigned int> mostProbobalAssign(vector<vector<double> > wordTopicProb);



