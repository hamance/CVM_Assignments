// MAX_LIKELIHOOD_LEARNING_OF_NORMAL_DISTRIBUTION.h
/*******************************************************************
系统名称:  无
文件名称:  MAX_LIKELIHOOD_LEARNING_OF_NORMAL_DISTRIBUTION.h
实现功能:  声明Max_Likelihood_Learning_of_Normal_Distribution类，该类描述基于标准正态分布参数的最大似然估计实现.
开发人员:  XXX
开发日期:  2016年9月
版权信息: 无
********************************************************************/

#ifndef CVM_ASSIGNMENTS_MAX_LIKELIHOOD_LEARNING_OF_NORMAL_DISTRIBUTION_H
#define CVM_ASSIGNMENTS_MAX_LIKELIHOOD_LEARNING_OF_NORMAL_DISTRIBUTION_H

#include <vector>

using namespace std;

class Max_Likelihood_Learning_of_Normal_Distribution {      //声明类

private:
    const double original_mu = 5.0; //初始化期望值u
    const double original_var = 8.0;//初始化方差
    double mu;//定义期望
    double var;//定义方差

public:

    Max_Likelihood_Learning_of_Normal_Distribution():mu(0), var(0) {};//构造函数

    vector<double> getTrainData(int num=100);//声明getTrainData函数

    void maxLikelihoodLearning(vector<double>);//声明maxLikelihoodLearning函数

    void estimateError();//声明estimateError函数

    double getMu();//声明getMu函数

    double getVar();//声明getVar函数




};


#endif //CVM_ASSIGNMENTS_MAX_LIKELIHOOD_LEARNING_OF_NORMAL_DISTRIBUTION_H
