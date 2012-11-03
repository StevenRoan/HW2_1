#include<iostream>
#include<vector>
#include<cmath>
#include<stdio.h>

using namespace std;

vector<vector<double> > conditionalProb(
    vector<vector<double> > wordTopicLikelihood , 
    vector<double> DocTopicLikelihood, 
    vector<unsigned int> document,
    unsigned int docIndex,
    unsigned int K,
    double delta,
    double &logC); 

vector<vector<double> > getWordProb(vector<vector<double> > WTL, 
    vector<unsigned int> doc, unsigned int K);

vector<double> vectorElementSum(vector<double> a, vector<double> b);
double vectorLogSum(vector<double> a);
vector<vector<double> > vectorMatrixTranpose(vector<vector<double> > a);


/* @brief   to perform the vector elemets product
 * @param   two vector 
 * @retval  one vector
 */
vector<double> vectorSum(vector<double> a, vector<double> b);


double sumlog(double a, double b);
double minuslog(double a, double b);

/* @brief   to compute the ML vector
 * @param   log of word topic prob. 
 *          log of doc topic prob. 
 *          delta 
 *          epsilon 
 *          K 
 *          current topic t 
 *          total word Num T 
 * @retval  ML vector 
 */
vector<double> MLcompute(vector<vector<double> > wordTopic, vector<double> docTopic
    , double delta, double epsilon, int K, int t, int T);

/* @brief   to compute the MR vector
 * @param   log of word topic prob.
 *          log of doc topic prob. 
 *          delta 
 *          epsilon 
 *          K 
 *          current topic t  
 *          total word Num T 
 * @retval  MR vector 
 */
vector<double> MRcompute(vector<vector<double> > wordTopic, vector<double> docTopic,
    double delta, double epsilon, int K, int t, int T);

/* @brief   to find the most probobal assignment
 * @param   probability table
 * @retval  vector of unsigned int
 */
vector<unsigned int> mostProbobalAssign(vector<vector<double> > wordTopicProb);
