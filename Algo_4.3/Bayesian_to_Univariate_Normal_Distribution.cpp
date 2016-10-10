//
// Created by Mardo on 2016/9/26.
//

#include "Bayesian_to_Univariate_Normal_Distribution.h"

#include <iostream>
#include <random>
#include <cmath>

vector<double> Bayesian_to_Univariate_Normal_Distribution::getTrainData(int num) {
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

vector<double> Bayesian_to_Univariate_Normal_Distribution::BayesianApproach(vector<double> input, double alpha, double beta,
                                                                  double gamma, double delta, vector<double> test) {
    int size = input.size();
    int size_test = test.size();
    if (size <= 0 || size_test <= 0 || alpha <= 0 || beta <= 0 || gamma <= 0) {
        cout<<"Invalid input or parameters!"<<endl;
    }

    double alpha_post = alpha + size/2;
    vector<double>temp;
    for (vector<double>::const_iterator iter = input.begin(); iter != input.end(); iter++) {
        temp.push_back(pow(*iter, 2));
    }
    double beta_post = accumulate(temp.begin(), temp.end(), 0.0f) + beta + (gamma*delta*delta)/2
                       - pow((gamma*delta+accumulate(input.begin(), input.end(), 0.0f)),2)/(2*(gamma+size));
    double gamma_post = gamma + size;
    double delta_post = (gamma*delta + accumulate(input.begin(), input.end(), 0.0f))/(gamma+size);

    //Computer itermediate parameters;
    temp.clear();
    double alpha_int = alpha_post + 0.5;
    for (vector<double>::const_iterator iter = test.begin(); iter != test.end(); iter++) {
        temp.push_back(pow(*iter, 2)/2 + beta_post + (gamma_post*delta_post*delta_post)/2
                       - pow((gamma_post*delta_post + *iter), 2) / (2* gamma_post + 2));
    }
    vector<double> beta_int = temp;
    double gamma_int = gamma_post + 1;

    //Predict values for test.
    double temp1 = sqrt(gamma_post) * pow(beta_post, alpha_post)*tgamma(alpha_int);
    vector<double> x_prediction_up;
    x_prediction_up.assign(size_test, temp1);
    const long PI = 3.141592653589793;
    vector<double> x_prediction_down;
    for (vector<double>::const_iterator iter=beta_int.begin(); iter != beta_int.end(); iter++) {
        x_prediction_down.push_back(sqrt(2*PI) * sqrt(gamma_int) * tgamma(alpha_post)
                                    * pow(*iter, alpha_int));
    }
    vector<double> x_prediction;
    if (x_prediction_up.size() != x_prediction_down.size()) {
        cout<<"Error!"<<endl;
        exit(1);
    }
    for (vector<double>::const_iterator iter1 = x_prediction_up.begin(), iter2 = x_prediction_down.begin();
            iter1 != x_prediction_up.end(); iter1++, iter2++) {
        x_prediction.push_back(*iter1 / *iter2);
    }
    return x_prediction;

}

void Bayesian_to_Univariate_Normal_Distribution::estimateError() {
    //Todo
}