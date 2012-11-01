#include<iostream>
#include<vector>
#include<math.h>
#include<stdio.h>

using namespace std;

/* @brief    to calculate the topic likelihood for single document
 * @param    word Topic Likelihood, topic document likelihood, document index
 * @retval   a vector of likihood in document and words
 */
vector<double> conditionalProb(
    vector<vector<double> > wordTopicLikelihood , 
    vector<double> DocTopicLikelihood, 
    unsigned int document,
    int K,
    double delta); 


/* @brief   to perform the vector elemets product
 * @param   two vector 
 * @retval  one vector
 */
vector<double> vectorSum(vector<double> a, vector<double> b);

/* @brief   Efficient way to compute matrix A
 * @param   matrix A, vector x
 * @retval  vector 
 */
vector<double> matrixProduct(vector<vector<double> > A, vector<double> x);

double sumlog(double a, double b);

/* @brief   to compute the ML vector
 * @param   log of word topic prob. | log of doc topic prob. | delta | epsilon 
 *          K | current topic t  
 * @retval  ML vector 
 */
vector<double> MLcompute(vector<vector<double> >wordTopic, 
    vector<double> docTopic, double delta, double epsilon, int K, int t);

/* @brief   to compute the MR vector
 * @param   log of word topic prob. | log of doc topic prob. | delta | epsilon 
 *          K | current topic t  
 * @retval  MR vector 
 */
vector<double> MRcompute(vector<double> wordTopic, vector<double> docTopic,
    double delta, double epsilon, int K, int t);

