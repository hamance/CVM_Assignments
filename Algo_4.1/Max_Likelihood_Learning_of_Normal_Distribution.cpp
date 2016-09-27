//
// Created by Mardo on 2016/9/26.
//

#include "Max_Likelihood_Learning_of_Normal_Distribution.h"
#include <iostream>
#include <numeric>
#include <random>

double Max_Likelihood_Learning_of_Normal_Distribution::gaussRand(double E, double V) {
    static double v1, v2, s;
    static int phase=0;
    double x;

    if (phase==0) {
        do {
            double u1 = (double)rand()/RAND_MAX;
            double u2 = (double)rand()/RAND_MAX;

            v1 = 2 * u1 -1;
            v2 = 2 * u2 -1;
            s = v1*v1 + v2*v2;
        } while (s >=1 || s==0);

        x = v1 * sqrt(-2*log(s)/s);
    } else {
        x = v2 * sqrt(-2*log(s)/s);
    }
    phase = 1-phase;

    return x * V + E;
}

vector<double> Max_Likelihood_Learning_of_Normal_Distribution::getTrainData(int num) {
    vector<double> temp;
    default_random_engine generator;
    //minstd_rand generator;
    normal_distribution<double> distribution(original_mu, original_var);
    for (int i = 0; i < num; ++i) {
        double number = distribution(generator);
        cout<<number;
        temp.push_back(number);
    }
    return temp;
}

void Max_Likelihood_Learning_of_Normal_Distribution::maxLikelihoodLearning(vector<double> input) {
    int size = input.size();
    if (size <=0) {
        cout<<"Invalid input!";
        exit(0);
    }
    double sum = accumulate(input.begin(), input.end(), 0.0f);
    mu = sum / size;
    vector<double> temp;
    for (vector<double>::iterator iter=input.begin(); iter != input.end(); iter++) {
        temp.push_back(pow(((*iter) - mu),2.0));
    }
    var = sqrt(accumulate(temp.begin(), temp.end(), 0.0)/size);
    cout<<"Learning finished!";
}

void Max_Likelihood_Learning_of_Normal_Distribution::estimateError() {
    cout<<"Estimating Error..."<<endl;
    cout<<"mu: "<<fabs(original_mu - mu)<<endl;
    cout<<"var: "<<fabs(original_var - var)<<endl;
}

double Max_Likelihood_Learning_of_Normal_Distribution::getMu() {
    return mu;
}

double Max_Likelihood_Learning_of_Normal_Distribution::getVar() {
    return var;
}