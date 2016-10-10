//
// Created by Mardo on 2016/9/26.
//

#include "main.h"

int main(){
    //testMaxLikelihoodLearning();
    //testMapLearning();
    testBayesianApproach();
    //testMLofCat();
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
    input = bud.getTrainData(5000);
    //x_test = -20:0.01:30;
    for(double i=-20.0; i<30 ;i+= 0.01) {
        test.push_back(i);
    }
    prediction = bud.BayesianApproach(input, 1,1,1,0, test);
    bud.estimateError(test, prediction);
}

void testMLofCat() {
    ML_of_Categorical_Parameters mlcp;
    double array[6] = {0.25,0.15,0.1,0.1,0.15,0.25};
    size_t count = sizeof(array) / sizeof(double);
    vector<double> weights(array, array+count);
    vector<double> try1 = mlcp.randomSample(6, 20000, weights);
    vector<double> out1 = mlcp.mleOfCat(try1, 6);
    mlcp.estimateError(weights, out1);
}