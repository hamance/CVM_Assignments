// ML_of_Categorical_Parameters.cpp
/*******************************************************************
系统名称:  无
文件名称:  ML_of_Categorical_Parameters.cpp
实现功能:  实现ML_of_Categorical_Parameters类所声明的各个函数.
开发人员:  XXX
开发日期:  2016年9月
版权信息: 无
********************************************************************/
#include "ML_of_Categorical_Parameters.h"

#include <iostream>
#include <numeric>
#include <random>
#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////
// 函数名：randomSample
// 功能：获取Categorical分布的测试数据
//执行条件：
//输入参数：double max(最大类别数）.int num（所需数据的数量）. vector<double> weight (权值向量）.
//返回值：vector<double> output(训练数据向量).
//说明：无
//设计者	：xxx
//日期：……
//////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////
// 函数名：mleOfCat
// 功能：进行ML估计
//基本思想：利用ML方法估计输入数据的均值和方差
//执行条件：
//输入参数：vector<double> input（基于标准正态分布的数据向量）.int max(最大类别数)
//返回值：无.
//说明：无
//设计者	：xxx
//日期：……
//////////////////////////////////////////////////////////////////////////////////////////////
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