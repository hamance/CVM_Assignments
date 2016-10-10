//
// Created by Mardo on 2016/9/26.
//

#ifndef CVM_ASSIGNMENTS_MAX_LIKELIHOOD_LEARNING_OF_NORMAL_DISTRIBUTION_H
#define CVM_ASSIGNMENTS_MAX_LIKELIHOOD_LEARNING_OF_NORMAL_DISTRIBUTION_H

#include <vector>

using namespace std;

class Max_Likelihood_Learning_of_Normal_Distribution {

private:
    const double original_mu = 5.0;
    const double original_var = 8.0;
    double mu;
    double var;

    double gaussRand(double E, double V);

public:

    Max_Likelihood_Learning_of_Normal_Distribution():mu(0), var(0) {};

    vector<double> getTrainData(int num=100);

    void maxLikelihoodLearning(vector<double>);

    void estimateError();

    double getMu();

    double getVar();




};

void testMaxLikelihoodLearning();

#endif //CVM_ASSIGNMENTS_MAX_LIKELIHOOD_LEARNING_OF_NORMAL_DISTRIBUTION_H
