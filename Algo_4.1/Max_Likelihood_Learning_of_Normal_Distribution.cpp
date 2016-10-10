// MAX_LIKELIHOOD_LEARNING_OF_NORMAL_DISTRIBUTION.cpp
/*******************************************************************
系统名称:  无
文件名称:  MAX_LIKELIHOOD_LEARNING_OF_NORMAL_DISTRIBUTION.cpp
实现功能:  实现Max_Likelihood_Learning_of_Normal_Distribution类所声明的各个函数.
开发人员:  XXX
开发日期:  2016年9月
版权信息: 无
********************************************************************/

#include "Max_Likelihood_Learning_of_Normal_Distribution.h"
#include <iostream>
#include <numeric>
#include <random>

/////////////////////////////////////////////////////////////////////////////////////////////
// 函数名：getTrainData
// 功能：获取基于正态分布标准的测试数据
//执行条件：注意所输入的数据必须是int类型
//输入参数：int num（所需数据的数量）..
//返回值：vector<double> temp(训练数据向量).
//说明：无
//设计者	：xxx
//日期：……
//////////////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////////
// 函数名：maxLikelihoodLearning
// 功能：进行最大似然估计
//基本思想：利用最大似然估计方法估计输入数据的均值和方差
//执行条件：
//输入参数：vector<double> input（基于标准正态分布的数据向量）..
//返回值：无.
//说明：无
//设计者	：xxx
//日期：……
//////////////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////////
// 函数名：estimateError
// 功能：计算拟合值和设定值的误差
//基本思想：无
//执行条件：无
//输入参数：无..
//返回值：无.
//说明：无
//设计者	：xxx
//日期：……
//////////////////////////////////////////////////////////////////////////////////////////////
void Max_Likelihood_Learning_of_Normal_Distribution::estimateError() {
    cout<<"Estimating Error..."<<endl;
    cout<<"mu: "<<fabs(original_mu - mu)<<endl;
    cout<<"var: "<<fabs(original_var - var)<<endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// 函数名：getMu
// 功能：获取期望
//基本思想：无
//执行条件：无
//输入参数：无..
//返回值：拟合所得期望.
//说明：无
//设计者	：xxx
//日期：……
//////////////////////////////////////////////////////////////////////////////////////////////
double Max_Likelihood_Learning_of_Normal_Distribution::getMu() {
    return mu;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// 函数名：getVar
// 功能：获取方差
//基本思想：无
//执行条件：无
//输入参数：无..
//返回值：拟合所得方差.
//说明：无
//设计者	：xxx
//日期：……
//////////////////////////////////////////////////////////////////////////////////////////////
double Max_Likelihood_Learning_of_Normal_Distribution::getVar() {
    return var;
}