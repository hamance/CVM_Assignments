// MAP_of_Univariate_Normal_Parameters.h
/*******************************************************************
系统名称:  无
文件名称:  MAP_of_Univariate_Normal_Parameters.h
实现功能:  MAP_of_Univariate_Normal_Parameters，该类描述基于标准正态分布参数的MAP实现.
开发人员:  XXX
开发日期:  2016年9月
版权信息: 无
********************************************************************/
#ifndef CVM_ASSIGNMENTS_MAP_OF_UNIVARIATE_NORMAL_PARAMETERS_H
#define CVM_ASSIGNMENTS_MAP_OF_UNIVARIATE_NORMAL_PARAMETERS_H

#include <vector>

using namespace std;


class MAP_of_Univariate_Normal_Parameters {//声明类

private:

    const double original_mu = 5.0;//初始化均值

    const double original_var = 8.0;//初始化方差

    double mu;

    double var;

public:

    MAP_of_Univariate_Normal_Parameters(): mu(0), var(0) {};//类构造函数

    vector<double> getTrainData(int num=1000000);//声明getTrainData函数

    void mapLearning(vector<double>, double alpha, double beta, double gamma, double delta);//声明mapLearning函数

    void estimateError();


};


#endif //CVM_ASSIGNMENTS_MAP_OF_UNIVARIATE_NORMAL_PARAMETERS_H
