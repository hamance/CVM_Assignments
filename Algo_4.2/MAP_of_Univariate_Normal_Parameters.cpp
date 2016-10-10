//
// Created by Mardo on 2016/9/26.
//

#include "MAP_of_Univariate_Normal_Parameters.h"

#include <iostream>
#include <numeric>
#include <random>

vector<double> MAP_of_Univariate_Normal_Parameters::getTrainData(int num) {
    vector<double> temp;
    default_random_engine generator;
    //minstd_rand generator;
    normal_distribution<double> distribution(original_mu, original_var);
    for (int i = 0; i < num; ++i) {
        double number = distribution(generator);
        //cout<<number;
        temp.push_back(number);
    }
    return temp;
}

void MAP_of_Univariate_Normal_Parameters::mapLearning(vector<double> input, double alpha, double beta, double gamma, double delta) {
    int size = input.size();
    if (size <0 || alpha <= 0 || beta <= 0 || gamma <= 0) {
        cout<<"Invalid input or parameters!"<<endl;
        exit(0);
    }

    double sum = accumulate(input.begin(), input.end(), 0.0f);
    mu = (sum + gamma*delta) / (size + gamma);
    vector<double> temp;
    for (vector<double>::const_iterator iter=input.begin(); iter != input.end(); iter ++) {
        temp.push_back(pow((*iter - mu),2));
    }

    double var_up = accumulate(temp.begin(), temp.end(),0.0f) + 2*beta + gamma*pow((delta-mu),2);
    double var_down = size + 3 + 2*alpha;
    var = sqrt(var_up / var_down);
}

void MAP_of_Univariate_Normal_Parameters::estimateError() {
    cout<<"Estimating Error..."<<endl;
    cout<<"mu: "<<fabs(original_mu - mu)<<endl;
    cout<<"var: "<<fabs(original_var - var)<<endl;
}

void testMapLearning() {
    MAP_of_Univariate_Normal_Parameters mup;
    vector<double> input;

    int Num = 100;
    cout<<"Maximum likelihood leanring of normal distribution..."<<endl;
    cout<<"Please input the scale of training data.(integer): ";
    cin>>Num;

    input = mup.getTrainData(Num);

    mup.mapLearning(input, 1,1,1,0);
    mup.estimateError();
}