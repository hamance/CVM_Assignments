//
// Created by hamance on 2016/10/13.
//

#include <iostream>
#include "Basic_Generative_Classifier_Eigen.h"

using Eigen::VectorXf;
using Eigen::RowVectorXf;
using namespace std;

MatrixXf Basic_Generative_Classifier_Eigen::randomTrain(vector<double> mu, vector<double> var, vector<double> num) {
    int size = mu.size();
    if (var.size() != size || num.size()!= size) {
        cout<<"Invalid Input of randomTrain..."<<endl;
        exit(1);
    }

    MatrixXf temp(accumulate(num.begin(), num.end(), 0), 2);
    //Vector2f rv2f;
    int N(0);
    for (int i = 0; i < size; ++i) {
        default_random_engine generator;
        normal_distribution<double> distribution(mu[i], var[i]);
        for (int j = N; j < N+num[i]; ++j) {
            temp.row(j).head(2) << distribution(generator),i;
        }
        //cout<<temp<<endl;
        N+=num[i];
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

int Basic_Generative_Classifier_Eigen::trainClassify(MatrixXf train, int cat) {
    category = cat;
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
        x_train_per_class[k].conservativeResize(nrow+1, dimensionality);
        x_train_per_class[k].row(nrow) << train.row(i).head(length-1);
        class_count[k] ++;
    }
    // init matrix mu , array of matrices sig , array lambda (categorical prior)
    //mu(cat, dimensionality);
    mu = MatrixXf::Zero(cat, dimensionality);
    //MatrixXf sig[cat];
    sig = new MatrixXf[cat];

    //double lambda[cat] = {0};
    lambda = new double[cat];
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

            lambda[k] = class_count[k]/(double)I;
        }
        //cout<<"--------"<<k<<"----------"<<endl;
        //cout<<sig[k]<<endl;
        //cout<<lambda[k]<<endl;
    }
    //cout<<mu<<endl;
    this->trained = true;
    return 1;
}

int Basic_Generative_Classifier_Eigen::test(MatrixXf test, int cat) {
    if (!this->trained) {
        cout<<"Error! untrained!"<<endl;
        exit(4);
    }

    MatrixXf likelihoods(test.rows(), cat);likelihoods<<MatrixXf::Zero(test.rows(), cat);
    VectorXf _data(test.cols()), _mu(mu.cols());
    for (int k = 0; k < cat; ++k) {
        _mu << mu.row(k);
        for (int l = 0; l < test.rows(); ++l) {
            _data << test.row(l);
            double t = mvnpdf (_data, _mu, sig[k]);
            likelihoods.row(l).col(k) << t;
        }
    }
    //cout<<likelihoods<<endl;


    VectorXf lambdaV(cat);
    for (int i1 = 0; i1 < cat; ++i1) {
        lambdaV.row(i1) << lambda[i1];
    }
    MatrixXf temp = likelihoods*lambdaV;
    //cout<<temp<<endl;
    VectorXf denominator(test.rows());
    for (int m = 0; m < test.rows(); ++m) {
        denominator[m] = 1 / temp.row(m).head(1).value();
    }
    posterior = likelihoods;
    for (int n = 0; n < posterior.cols(); ++n) {
        posterior.col(n) *= lambda[n];
    }
    //cout<<posterior<<endl;
    MatrixXf posterior_T(cat, test.rows()); posterior_T = posterior.transpose();
    //cout<<posterior_T<<endl;
    //posterior = posterior.transpose();
    MatrixXf dd = denominator.asDiagonal();
    posterior_T = posterior_T * dd;
    posterior = posterior_T.transpose();
    //cout<<posterior<<endl;

    return 1;
}



MatrixXf Basic_Generative_Classifier_Eigen::generativeClassfy(MatrixXf train, MatrixXf test, int cat) {
    category = cat;
    int I = train.rows();
    cout<<train<<endl;
    cout<<test<<endl;

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
        x_train_per_class[k].row(nrow-1) << train.row(i).head(length-1);
        class_count[k] ++;
    }
    // init matrix mu , array of matrices sig , array lambda (categorical prior)
    //mu(cat, dimensionality);
    mu = MatrixXf::Zero(cat, dimensionality);
    //MatrixXf sig[cat];
    sig = new MatrixXf[cat];

    cout<<"-----------0"<<endl;
    cout<<x_train_per_class[0]<<endl;
    cout<<"-----------1"<<endl;
    cout<<x_train_per_class[1]<<endl;

    //double lambda[cat] = {0};
    lambda = new double[cat];
    VectorXf mat(dimensionality);
    for (int k = 0; k < cat; ++k) {
        //check class_count
        if (class_count[k]) {
            for (int i = 0; i < dimensionality; ++i) {
                mu.row(k).col(i) << x_train_per_class[k].col(i).sum() / class_count[k];
            }
            cout<<mu<<endl;
            sig[k] = MatrixXf::Zero(dimensionality, dimensionality);
            for (int j = 0; j < class_count[k]; ++j) {
                for (int m = 0; m < dimensionality; ++m) {
                    mat.row(m) = x_train_per_class[k].row(j).col(m) - mu.row(k).col(m);
                    cout<<mat.row(m)<<endl;
                }
                cout<<"-------mat"<<endl;
                cout<<mat<<endl;
                mat = mat.transpose() * mat;
                sig[k] += mat;
            }
            cout<<"---------sig"<<endl;
            cout<<sig[k]<<endl;
            sig[k] /= class_count[k];

            lambda[k] = class_count[k]/(double)I;
        }
        //cout<<"--------"<<k<<"----------"<<endl;
        //cout<<sig[k]<<endl;
        //cout<<lambda[k]<<endl;
    }
    //cout<<mu<<endl;

    //compute likelihoods
    MatrixXf likelihoods(test.rows(), cat);likelihoods<<MatrixXf::Zero(test.rows(), cat);
    VectorXf _data(test.cols()), _mu(mu.cols());
    for (int k = 0; k < cat; ++k) {
        _mu << mu.row(k);
        for (int l = 0; l < test.rows(); ++l) {
            _data << test.row(l);
            double t = mvnpdf (_data, _mu, sig[k]);
            likelihoods.row(l).col(k) << t;
        }
    }
    //cout<<likelihoods<<endl;


    VectorXf lambdaV(cat);
    for (int i1 = 0; i1 < cat; ++i1) {
        lambdaV.row(i1) << lambda[i1];
    }
    MatrixXf temp = likelihoods*lambdaV;
    //cout<<temp<<endl;
    VectorXf denominator(test.rows());
    for (int m = 0; m < test.rows(); ++m) {
        denominator[m] = 1 / temp.row(m).head(1).value();
    }
    posterior = likelihoods;
    for (int n = 0; n < posterior.cols(); ++n) {
        posterior.col(n) *= lambda[n];
    }
    //cout<<posterior<<endl;
    MatrixXf posterior_T(cat, test.rows()); posterior_T = posterior.transpose();
    //cout<<posterior_T<<endl;
    //posterior = posterior.transpose();
    MatrixXf dd = denominator.asDiagonal();
    posterior_T = posterior_T * dd;
    posterior = posterior_T.transpose();
    //cout<<posterior<<endl;
}

void Basic_Generative_Classifier_Eigen::print() {
    cout<<"---------mu--------------\n";
    cout<<this->mu<<endl;
    cout<<"---------sig-------------\n";
    for (int i = 0; i < this->category; ++i) {
        cout<<"------:\n"<<this->sig[i]<<endl;
    }
    cout<<"---------lambda----------\n";
    //cout<<lambda<<endl;
    for (int i = 0; i < this->category; ++i) {
        cout<<"------:\n"<<this->lambda[i]<<endl;
    }
    cout<<"--------posterior--------\n";
    cout<<this->posterior<<endl;
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
    double mu_arr[] = {-2, 2};
    size_t mu_size = sizeof(mu_arr)/ sizeof(double);
    vector<double> mu(mu_arr, mu_arr+mu_size);

    double var_arr[] = {0.5, 0.5};
    size_t var_size = sizeof(var_arr)/ sizeof(double);
    vector<double> var(var_arr, var_arr+var_size);

    double num_arr[] = {100, 100};
    size_t num_size = sizeof(num_arr)/ sizeof(double);
    vector<double> num(num_arr, num_arr+num_size);


    Basic_Generative_Classifier_Eigen bgcm;
    MatrixXf train = bgcm.randomTrain(mu, var, num);
    //cout<<train<<endl;
    MatrixXf test = bgcm.randomTest(-4,801,0.01);
    //cout<<test.transpose()<<endl;

    bgcm.generativeClassfy(train, test, 2);
    //bgcm.trainClassify(train, 2);
    //bgcm.test(test,2);
    bgcm.print();
}
