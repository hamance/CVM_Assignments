//
// Created by Mardo on 2016/9/26.
//

#include <iostream>
#include "Algo_4.1/Max_Likelihood_Learning_of_Normal_Distribution.h"
#include "Algo_4.2/MAP_of_Univariate_Normal_Parameters.h"
#include "Algo_4.3/Bayesian_to_Univariate_Normal_Distribution.h"

using namespace std;

void testMaxLikelihoodLearning();
void testMapLearning();
void testBayesianApproach();

int main(){
    //testMaxLikelihoodLearning();
    //testMapLearning();
    testBayesianApproach();
    cout<<"Hello World!"<<endl;
    return 0;
}

void testMaxLikelihoodLearning() {
    Max_Likelihood_Learning_of_Normal_Distribution mle;
    vector<double> input;
    input = mle.getTrainData(100);

    //for (vector<double>::const_iterator iter=input.begin(); iter != input.end(); iter++) {
    //    cout<<*iter<<", ";
    //}
    //cout<<endl;

    mle.maxLikelihoodLearning(input);
    mle.estimateError();
}

void testMapLearning() {
    MAP_of_Univariate_Normal_Parameters mup;
    vector<double> input;
    input = mup.getTrainData();

    mup.mapLearning(input, 1,1,1,0);
    mup.estimateError();
}

void testBayesianApproach() {
    Bayesian_to_Univariate_Normal_Distribution bud;
    vector<double> input, test, prediction;
    input = bud.getTrainData();
    //x_test = -20:0.01:30;
    for(double i=-20.0; i<30 ;i+= 0.01) {
        test.push_back(i);
    }
    prediction = bud.BayesianApproach(input, 1,1,1,0, test);
}