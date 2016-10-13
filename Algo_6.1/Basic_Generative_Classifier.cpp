//
// Created by hamance on 2016/10/11.
//

#include "Basic_Generative_Classifier.h"

#include <iostream>
#include <random>

vector<pair<double, int>> Basic_Generative_Classifier::randomTrain(vector<double> mu, vector<double> var, vector<double> num) {
    int size = mu.size();
    if (var.size() != size || num.size()!= size) {
        cout<<"Invalid Input of randomTrain..."<<endl;
        exit(1);
    }

    vector<pair<double, int>> temp;
    default_random_engine generator;
    //minstd_rand generator;
    for (int j = 0; j < size; ++j) {
        normal_distribution<double> distribution(mu[j], var[j]);
        for (int i = 0; i < num[j]; ++i) {
            temp.push_back(make_pair(distribution(generator), j));
        }
    }

    return temp;
}

vector<double> Basic_Generative_Classifier::randomTest() {
    vector<double> temp;
    for (int i = -4; i <= 4 ; i+=0.01) {
        temp.push_back(i);
    }
    return temp;
}

vector<double> Basic_Generative_Classifier::generativeClassfy(vector<pair<double,int>> train, vector<double> test, int cat) {

    int size = train.size();
    int dimension = 1;
    vector<double> x_train_per_class[cat];
    int catCount[cat] = {0};

    for (int i = 0; i < size; ++i) {
        x_train_per_class[train[i].second].push_back(train[i].first);
        catCount[train[i].second]++;
    }

    double mus[cat] = {0};
    double var[cat] = {0};
    double lamda[cat] = {0};
    for (int j = 0; j < cat; ++j) {

        mus[j] = accumulate(x_train_per_class[j].begin(), x_train_per_class[j].end(), 0.0f)/catCount[j];

        for (int k = 0; k < catCount[j]; ++k) {
            var[j] += pow(x_train_per_class[j][k]-mus[j], 2);
        }
        var[j] /= catCount[j];
        lamda[j] = catCount[j]/size;
    }

    int test_size = test.size();
    int likelihoods[test_size][cat] = {0};
    //for (int m = 0; m < test_size; ++m) {
    //   for (int n = 0; n < cat; ++n) {
    //        likelihoods[m][n] = gauss(test[m], mus[n], var[n]);
    //   }
    //}

    double denominator[test_size] = {0};
    //for (int p = 0; p < test_size; ++p) {
    //    denominator[p] = 1/(sum(likelihoods[p]));
    //}

}