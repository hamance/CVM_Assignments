//
// Created by Mardo on 2016/9/26.
//

#ifndef CVM_ASSIGNMENTS_MAP_OF_UNIVARIATE_NORMAL_PARAMETERS_H
#define CVM_ASSIGNMENTS_MAP_OF_UNIVARIATE_NORMAL_PARAMETERS_H

#include <vector>

using namespace std;


class MAP_of_Univariate_Normal_Parameters {

private:

    const double original_mu = 5.0;

    const double original_var = 8.0;

    double mu;

    double var;

public:

    MAP_of_Univariate_Normal_Parameters(): mu(0), var(0) {};

    vector<double> getTrainData(int num=1000000);

    void mapLearning(vector<double>, double alpha, double beta, double gamma, double delta);

    void estimateError();


};


void testMapLearning();

#endif //CVM_ASSIGNMENTS_MAP_OF_UNIVARIATE_NORMAL_PARAMETERS_H
