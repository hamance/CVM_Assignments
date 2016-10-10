//
// Created by Mardo on 2016/9/26.
//

#ifndef CVM_ASSIGNMENTS_BAYESIAN_TO_UNIVARIATE_NORMAL_DISTRIBUTION_H
#define CVM_ASSIGNMENTS_BAYESIAN_TO_UNIVARIATE_NORMAL_DISTRIBUTION_H

#include <vector>

using namespace std;

class Bayesian_to_Univariate_Normal_Distribution {

private:
    const double original_mu = 5.0;
    const double original_var = 8.0;
    double mu;
    double var;

public:

    Bayesian_to_Univariate_Normal_Distribution():mu(0), var(0) {};

    vector<double> getTrainData(int num=50);

    vector<double> BayesianApproach(vector<double>, double alpha, double beta, double gamma, double delta, vector<double>test);

    void estimateError();
};


#endif //CVM_ASSIGNMENTS_BAYESIAN_TO_UNIVARIATE_NORMAL_DISTRIBUTION_H
