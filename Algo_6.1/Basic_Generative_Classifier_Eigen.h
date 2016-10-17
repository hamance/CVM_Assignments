//
// Created by hamance on 2016/10/13.
//

#ifndef CVM_ASSIGNMENTS_BASIC_GENERATIVE_CLASSIFIER_OPENCV_H
#define CVM_ASSIGNMENTS_BASIC_GENERATIVE_CLASSIFIER_OPENCV_H

#include "../lib/Eigen/Dense"

using Eigen::MatrixXf;
using namespace std;


class Basic_Generative_Classifier_Eigen {

public:

    Basic_Generative_Classifier_Eigen(){
        trained = false;
    }

    //随机产生正态训练样本，根据输入均值、方差对应产生相应数量的样本，并按均值依次编号为0，1，2，...类
    MatrixXf randomTrain(vector<double> mu, vector<double> var, vector<double> num);


    //产生均匀分布样本作为测试集
    MatrixXf randomTest(double begin, int num, double intervel=0.1);

    int trainClassify(MatrixXf train, int cat);

    int test(MatrixXf test, int cat);


    MatrixXf generativeClassfy(MatrixXf train, MatrixXf test, int cat);


    void print();


    void estimateErros(vector<double> origin, vector<double> result);

private:

    bool trained;

    int category;

    double* lambda;

    MatrixXf mu;

    MatrixXf* sig;

    MatrixXf posterior;

};

void testBGC_Matrix();

#endif //CVM_ASSIGNMENTS_BASIC_GENERATIVE_CLASSIFIER_OPENCV_H
