//
// Created by Mardo on 2016/9/27.
//

#include "ML_of_Categorical_Parameters.h"

#include <iostream>
#include <numeric>
#include <random>
#include <cmath>



vector<double> ML_of_Categorical_Parameters::randomSample(double max, int num, vector<double> weight) {
    double weight_sum = accumulate(weight.begin(), weight.end(), 0.0f);
    int size = weight.size();
    if (weight_sum != 1 || size != max) {
        cout<<"Invalid weight! "<<endl;
        exit(0);
    }

    vector<double> probabilities;
    double weight_accumulate=0;
    for (int i = 1; i <= size; ++i) {
        weight_accumulate += weight[i-1];
        probabilities.push_back(weight_accumulate);
    }

    vector<double> output;
    for (int k = 0; k < num; ++k) {
        double tmp = rand() % 6 +1 ;
        output.push_back(tmp);
    }

    return output;
}


vector<double> ML_of_Categorical_Parameters::mleOfCat(vector<double> input, int max) {
    double bins[max] = {0.0};
    for (vector<double>::const_iterator iter=input.begin(); iter != input.end(); iter ++) {
        bins[(int)*iter-1] ++;
    }
    int total = input.size();
    for (int i = 0; i < max; ++i) {
        bins[i] = bins[i]/total;
    }
    return vector<double>(bins, bins+max);
}

void ML_of_Categorical_Parameters::estimateError(vector<double> original, vector<double> predict) {
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

void testMLofCat() {
    ML_of_Categorical_Parameters mlcp;
    double array[6] = {0.25,0.15,0.1,0.1,0.15,0.25};
    int Num = 100;
    cout<<"Maximum likelihood leanring of categorical parameters..."<<endl;
    cout<<"Please input the scale of categorical.(integer, 0 for defalut): ";
    cin>>Num;
    if (Num <= 0) {
        cout<<"Default: 6 categories at : ";
        for (int i = 0; i < 6; ++i) {
            cout<<array[i]<<" ";
        }
        cout<<endl;
    } else {
        int array[Num];
        for (int i = 0; i < Num; ++i) {
            cin>>array[i];
        }
    }
    size_t count = sizeof(array) / sizeof(double);
    vector<double> weights(array, array+count);
    vector<double> try1 = mlcp.randomSample(6, 20000, weights);
    vector<double> out1 = mlcp.mleOfCat(try1, 6);
    mlcp.estimateError(weights, out1);
}