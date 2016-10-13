//
// Created by hamance on 2016/10/11.
//

#ifndef CVM_ASSIGNMENTS_BASIC_GENERATIVE_CLASSIFIER_H
#define CVM_ASSIGNMENTS_BASIC_GENERATIVE_CLASSIFIER_H

#include <vector>

using namespace std;

class Basic_Generative_Classifier {


public:

    //随机产生正态训练样本，根据输入均值、方差对应产生相应数量的样本，并按均值依次编号为0，1，2，...类
    vector<pair<double, int>> randomTrain(vector<double> mu, vector<double> var, vector<double> num);


    //产生均匀分布样本作为测试集
    vector<double> randomTest();


    vector<double> generativeClassfy(vector<pair<double,int>> train, vector<double> test, int cat);


    void estimateErros(vector<double> origin, vector<double> result);



};

void testBGC();


#endif //CVM_ASSIGNMENTS_BASIC_GENERATIVE_CLASSIFIER_H
