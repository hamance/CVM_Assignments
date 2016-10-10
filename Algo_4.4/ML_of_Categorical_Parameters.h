// ML_of_Categorical_Parameters.h
/*******************************************************************
系统名称:  无
文件名称:  ML_of_Categorical_Parameters.h
实现功能:  声明ML_of_Categorical_Parameters类，该类描述基于Categorical分布的最大似然估计实现.
开发人员:  XXX
开发日期:  2016年9月
版权信息: 无
********************************************************************/
#ifndef CVM_ASSIGNMENTS_ML_OF_CATEGORICAL_PARAMETERS_H
#define CVM_ASSIGNMENTS_ML_OF_CATEGORICAL_PARAMETERS_H

#include <vector>

using namespace std;

class ML_of_Categorical_Parameters {

public:

    int findBin(double target, int start, int end, vector<double> line);

    vector<double> randomSample(double max, int num, vector<double> weight);

    vector<double> mleOfCat(vector<double> input, int cat);

    void estimateError(vector<double> original, vector<double> predict);


};


#endif //CVM_ASSIGNMENTS_ML_OF_CATEGORICAL_PARAMETERS_H
