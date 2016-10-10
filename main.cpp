//
// Created by Mardo on 2016/9/26.
//

#include "main.h"

int main(){
   // testMaxLikelihoodLearning();
   // testMapLearning();
   //testBayesianApproach();
    testMLofCat();
    //testMAPofCat();
    cout<<"Hello World!"<<endl;
    return 0;
}

void testMaxLikelihoodLearning() {//正态分布最大似然估计
    Max_Likelihood_Learning_of_Normal_Distribution mle;
    vector<double> input;
    input = mle.getTrainData(100);
    mle.maxLikelihoodLearning(input);
    mle.estimateError();
}

void testMapLearning() {//正态分布MAP估计
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
    cout<<"input"<<"   "<<"prediction"<<"   "<<"error"<<endl;
    for(vector<double>::iterator j=test.begin(),i=prediction.begin();j!=test.end();j++,i++)
        cout<< *j<< " " <<*i<<" "<<*i-*j<<endl;
}

void testMLofCat() {//Categorical分布ML估计
    ML_of_Categorical_Parameters mlcp;
    double array[6] = {0.25,0.15,0.1,0.1,0.15,0.25};
    size_t count = sizeof(array) / sizeof(double);
    vector<double> weights(array, array+count);
    vector<double> try1 = mlcp.randomSample(6, 20000, weights);
    vector<double> out1 = mlcp.mleOfCat(try1, 6);
    mlcp.estimateError(weights, out1);
}
void testMAPofCat(){//Categorical分布MAP估计
    MAP_of_Categorical_Parameters mlcp;
    double array[6] = {0.25,0.15,0.1,0.1,0.15,0.25};
    size_t count = sizeof(array) / sizeof(double);
    vector<double> weights(array, array+count);
    vector<double> try1 = mlcp.randomSample(6, 20000, weights);
    double array1[6]  = {1,1,1,1,1,1};
    size_t count1 = sizeof(array1) / sizeof(double);
    vector<double> alpha(array, array+count);
    vector<double> out1 = mlcp.mapOfCat(try1,alpha);
    mlcp.estimateError(weights, out1);
}