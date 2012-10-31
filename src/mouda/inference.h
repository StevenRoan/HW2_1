#include<iostream>
#include<vector>

using namespace std;

/* @brief    to calculate the topic likelihood for single document
 * @param    word Topic Likelihood, topic document likelihood, document index
 * @retval   a matrix of likihood in document and words
 */
vector<vector<double> > conditionalProb(
    vector<vector<double> > wordTopicLikelihood , 
    vector<double> TopicDocLikelihood, 
    unsigned int document); 
