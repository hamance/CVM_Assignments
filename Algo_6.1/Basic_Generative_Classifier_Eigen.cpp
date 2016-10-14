//
// Created by hamance on 2016/10/13.
//

#include <iostream>
#include "Basic_Generative_Classifier_Eigen.h"

using Eigen::VectorXf;
using Eigen::RowVectorXf;

MatrixXf Basic_Generative_Classifier_Eigen::randomTrain(vector<double> mu, vector<double> var, vector<double> num) {
    int size = mu.size();
    if (var.size() != size || num.size()!= size) {
        cout<<"Invalid Input of randomTrain..."<<endl;
        exit(1);
    }

    MatrixXf temp(accumulate(num.begin(), num.end(), 0), 2);
    default_random_engine generator;
    //Vector2f rv2f;
    for (int i = 0; i < size; ++i) {
        normal_distribution<double> distribution(mu[i], var[i]);
        for (int j = 0; j < num[i]; ++j) {
            temp.row(j).head(2) << distribution(generator),i;
        }
    }
    return temp;
}

MatrixXf Basic_Generative_Classifier_Eigen::randomTest(double begin, int num, double interval) {
    MatrixXf temp(num,1);
    for (double i = begin, j=0; j < num; i += interval, j++) {
        temp.row(j) << i;
    }
    return temp;
}

double mvnpdf(VectorXf data, VectorXf mu, MatrixXf sig) {
    int d = sig.cols();
    if (sig.rows() != d || data.size() != d || mu.size() != d) {
        cout<<"Error sig!"<<endl;
        exit(2);
    }
    double A = 1/(sqrt(sig.determinant()*pow(2*M_PI, d)));
    MatrixXf t(d,1);t << data-mu;
    double B = -0.5* (t.transpose() * sig.inverse() * t).value();
    return A * exp(B);
}

MatrixXf Basic_Generative_Classifier_Eigen::generativeClassfy(MatrixXf train, MatrixXf test, int cat) {
    int I = train.rows();

    //separate train data and class marker
    int dimensionality = train.cols()-1;
    MatrixXf x_train_per_class[cat];
    for (int j1 = 0; j1 < cat; ++j1) {
        x_train_per_class[j1].conservativeResize(0, dimensionality);
    }
    // count train data in each class
    int class_count[cat] = {0};
    int length = train.cols();

    int k(0), nrow(0);
    for (int i = 0; i < I; ++i) {
        k = (int)train.row(i).tail(1).value();
        nrow = x_train_per_class[k].rows()+1;
        x_train_per_class[k].conservativeResize(nrow, dimensionality);
        x_train_per_class[k].row(nrow) << train.row(i).head(length-1);
        class_count[k] ++;
    }
    // init matrix mu , array of matrices sig , array lambda (categorical prior)
    MatrixXf mu(cat, dimensionality);mu << MatrixXf::Zero(cat, dimensionality);
    MatrixXf sig[cat];
    double lambda[cat] = {0};


    MatrixXf mat(dimensionality, dimensionality);
    for (int k = 0; k < cat; ++k) {
        //check class_count
        if (class_count[k]) {
            for (int i = 0; i < dimensionality; ++i) {
                mu.row(k).col(i) << x_train_per_class[k].col(i).sum() / class_count[k];
            }
            sig[k] = MatrixXf::Zero(dimensionality, dimensionality);
            for (int j = 0; j < class_count[k]; ++j) {
                for (int m = 0; m < dimensionality; ++m) {
                    mat.row(m) = x_train_per_class[k].row(m) - mu.row(k);
                }
                mat = mat.transpose() * mat;
                sig[k] += mat;
            }
            sig[k] /= class_count[k];
            lambda[k] = class_count[k]/I;
        }
    }

    //compute likelihoods
    MatrixXf likelihoods(test.cols(), cat);likelihoods<<MatrixXf::Zero(test.cols(), cat);
    VectorXf _data, _mu;
    for (int k = 0; k < cat; ++k) {
        for (int l = 0; l < test.cols(); ++l) {
            _data << test.col(1);
            _mu << mu.row(k);
            likelihoods.row(l).col(k) << mvnpdf (_data, _mu, sig[k]);
        }
    }


    RowVectorXf lambdaV(cat);
    for (int i1 = 0; i1 < cat; ++i1) {
        lambdaV << lambda[i1];
    }
    MatrixXf temp = likelihoods*lambdaV;
    double denominator[test.cols()];
    for (int m = 0; m < test.cols(); ++m) {
        denominator[m] = 1 / temp.row(m).head(1).value();
    }
    MatrixXf posterior = likelihoods;
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
