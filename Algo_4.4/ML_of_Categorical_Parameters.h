//
// Created by Mardo on 2016/9/27.
//

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
