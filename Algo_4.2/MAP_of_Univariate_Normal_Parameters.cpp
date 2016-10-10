// MAP_of_Univariate_Normal_Parameters.cpp
/*******************************************************************
系统名称:  无
文件名称:  MAP_of_Univariate_Normal_Parameters.cpp
实现功能:  实现MAP_of_Univariate_Normal_Parameters类所声明的各个函数.
开发人员:  XXX
开发日期:  2016年9月
版权信息: 无
********************************************************************/
#include "MAP_of_Univariate_Normal_Parameters.h"

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

vector<double> MAP_of_Univariate_Normal_Parameters::getTrainData(int num) {
    vector<double> temp;
    default_random_engine generator;
    //minstd_rand generator;
    normal_distribution<double> distribution(original_mu, original_var);
    for (int i = 0; i < num; ++i) {
        double number = distribution(generator);
        //cout<<number;
        temp.push_back(number);
    }
    return temp;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// 函数名：mapLearning
// 功能：进行MAP估计
//基本思想：利用MAP方法估计输入数据的均值和方差
//执行条件：
//输入参数：vector<double> input（基于标准正态分布的数据向量）.alpha，beta，gamma，delta
//返回值：无.
//说明：无
//设计者	：xxx
//日期：……
//////////////////////////////////////////////////////////////////////////////////////////////
void MAP_of_Univariate_Normal_Parameters::mapLearning(vector<double> input, double alpha, double beta, double gamma, double delta) {
    int size = input.size();
    if (size <0 || alpha <= 0 || beta <= 0 || gamma <= 0) {
        cout<<"Invalid input or parameters!"<<endl;
        exit(0);
    }

    double sum = accumulate(input.begin(), input.end(), 0.0f);
    mu = (sum + gamma*delta) / (size + gamma);
    vector<double> temp;
    for (vector<double>::const_iterator iter=input.begin(); iter != input.end(); iter ++) {
        temp.push_back(pow((*iter - mu),2));
    }

    double var_up = accumulate(temp.begin(), temp.end(),0.0f) + 2*beta + gamma*pow((delta-mu),2);
    double var_down = size + 3 + 2*alpha;
    var = sqrt(var_up / var_down);
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
void MAP_of_Univariate_Normal_Parameters::estimateError() {
    cout<<"Estimating Error..."<<endl;
    cout<<"mu: "<<fabs(original_mu - mu)<<endl;
    cout<<"var: "<<fabs(original_var - var)<<endl;
}