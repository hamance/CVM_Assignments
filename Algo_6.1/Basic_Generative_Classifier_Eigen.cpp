//
// Created by hamance on 2016/10/13.
//

#include <iostream>
#include "Basic_Generative_Classifier_Eigen.h"

using Eigen::MatrixXd;
using Eigen::VectorXf;

MatrixXf Basic_Generative_Classifier_Eigen::randomTrain(vector<double> mu, vector<double> var, vector<double> num) {
    int size = mu.size();
    if (var.size() != size || num.size()!= size) {
        cout<<"Invalid Input of randomTrain..."<<endl;
        exit(1);
    }

    MatrixXf temp(2,accumulate(num.begin(), num.end(), 0));
    default_random_engine generator;
    //Vector2f rv2f;
    for (int i = 0; i < size; ++i) {
        normal_distribution<double> distribution(mu[i], var[i]);
        for (int j = 0; j < num[i]; ++j) {
            temp.col(j).head(2) << distribution(generator),i;
        }
    }
    return temp;
}

MatrixXf Basic_Generative_Classifier_Eigen::randomTest(double begin, int num, double interval) {
    MatrixXf temp(1, num);
    for (double i = begin, j=0; j < num; i += interval, j++) {
        temp.col(j) << i;
    }
    return temp;
}

MatrixXf Basic_Generative_Classifier_Eigen::generativeClassfy(MatrixXf train, MatrixXf test, int cat) {
    int I = train.cols();
    int dimensionality = train.rows()-1;
    MatrixXd x_train_per_class[cat];
    int class_count[cat] = {0};

    int length = train.rows();
    for (int i = 0; i < I; ++i) {
        int k = (int)train.col(i).tail(1).value();
        //uncertain size.
        x_train_per_class[k] << train.col(i).head(length-1);
        class_count[k] ++;
    }

    MatrixXf mu = MatrixXf::Zero(cat, dimensionality);
    MatrixXd sig[cat];
    double lambda[cat] = {0};

    for (int k = 0; k < cat; ++k) {
        if (class_count[k]) {
            for (int i = 0; i < dimensionality; ++i) {
                mu.col(k).row(i) << x_train_per_class[k].row(i).sum() / class_count[k];
            }
            sig[k] = MatrixXd::Zero(dimensionality, dimensionality);
            for (int j = 0; j < class_count[k]; ++j) {
                //size doesn't match
                MatrixXd mat = x_train_per_class[k] - mu.row(k);
                mat = mat.transpose() * mat;
                sig[k] += mat;
            }
            sig[k] /= class_count[k];
            lambda[k] = class_count[k]/I;
        }
    }

    MatrixXd likelihoods(test.cols(), cat);
    for (int k = 0; k < cat; ++k) {
        for (int l = 0; l < test.cols(); ++l) {
            likelihoods.row(l).col(k) << mvnpdf (test.col(l), mu.row(k).row(l), sig[k]);
        }
    }
    MatrixXd temp = likelihoods.dot(lambda);
    double denominator[test.cols()];
    for (int m = 0; m < test.cols(); ++m) {
        denominator[m] = 1 / temp.row(m).head(1).value();
    }
    MatrixXd posterior = likelihoods;
    for (int n = 0; n < posterior.cols(); ++n) {
        posterior.col(n) *= lambda[n];
    }
    posterior = posterior.transpose();
    for (int n = 0; n < posterior.cols(); ++n) {
        posterior.col(n) *= denominator[n];
    }
    posterior = posterior.transpose();

}


void testBGC_Matrix() {
    /*
    vector<double> mu(1,0), var(1,1), num(1,20);
    Basic_Generative_Classifier_Eigen bgcm;
    MatrixXf m = bgcm.randomTrain(mu, var, num);
    cout<<m<<endl;
     */
    /*
    Basic_Generative_Classifier_Eigen bgcm;
    cout<<bgcm.randomTest(-2, 5, 0.5);
     */
}
