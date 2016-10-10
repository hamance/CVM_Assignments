//
// Created by hamance on 2016/10/10.
//

#include "MAP_of_Categorical_Parameters.h"

#include <iostream>
#include <numeric>
#include <random>

using namespace std;

vector<double> MAP_of_Categorical_Parameters::randomSample(int max, int num, vector<double> weight) {
    double weight_sum = accumulate(weight.begin(), weight.end(), 0.0f);
    int size = weight.size();
    if (weight_sum != 1 || size != max) {
        cout<<"Invalid weight! "<<endl;
        exit(0);
    }

    vector<double> probabilities;
    probabilities.push_back(0);
    double weight_accumulate=0;
    for (int i = 1; i <= size; ++i) {
        weight_accumulate += weight[i-1]*RAND_MAX;
        probabilities.push_back(weight_accumulate);
    }

    vector<double> output;
    for (int k = 0; k < num; ++k) {
        double tmp = rand();
        for (int i = 0; i <= size; ++i) {
            if (tmp < probabilities[i]) {
                output.push_back(i);
                break;
            }
        }
    }

    return output;
}


vector<double> MAP_of_Categorical_Parameters::mapOfCat(vector<double> input, vector<double> alpha) {
    int total = input.size();
    int len_alpha = alpha.size();

    double bins[len_alpha] = {0.0};
    for (vector<double>::const_iterator iter=input.begin(); iter != input.end(); iter ++) {
        bins[(int)*iter-1] ++;
    }

    double sum_alpha = accumulate(alpha.begin(), alpha.end(), 0.0f);

    vector<double> theta;
    for (int i = 0; i < len_alpha; ++i) {
        theta.push_back((bins[i]-1+alpha[i])/(total - len_alpha + sum_alpha));
    }
    return theta;
}

void MAP_of_Categorical_Parameters::estimateError(vector<double> original, vector<double> predict) {
    if (original.size() != predict.size()) {
        cout<<"Error!"<<endl;
        exit(1);
    }
    cout<<"Estimating Error...\n"<<"   ";
    for (vector<double>::const_iterator iter1 = original.begin(), iter2 = predict.begin();
         iter1 != original.end(); iter1++, iter2++) {
        cout<<fabs(*iter1 - *iter2)<<"   ";
    }
}

void testMAPofCat() {
    MAP_of_Categorical_Parameters mapcp;
    double array[6] = {0.25,0.15,0.1,0.1,0.15,0.25};
    double alpha[6] = {1,1,1,1,1,1};
    int Num = 0;
    //cout<<"Maximum a posterior learning of categorical parameters..."<<endl;
    //cout<<"Please input the scale of categorical.(integer, 0 for defalut): ";
    //cin>>Num;
    if (Num <= 0) {
        cout<<"Default: 6 categories at : ";
        for (int i = 0; i < 6; ++i) {
            cout<<array[i]<<" ";
        }
        cout<<endl;
    } else {
        delete(array);
        double array[Num];
        for (int i = 0; i < Num; ++i) {
            cin>>array[i];
        }
    }
    size_t count = sizeof(array) / sizeof(double);
    vector<double> weights(array, array+count);
    vector<double> try1 = mapcp.randomSample(6, 20000, weights);
    size_t count1 = sizeof(alpha) / sizeof(double);
    vector<double> alpha1(alpha, alpha+count1);
    vector<double> out1 = mapcp.mapOfCat(try1, alpha1);
    mapcp.estimateError(weights, out1);
}