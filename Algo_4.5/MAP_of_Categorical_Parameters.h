//
// Created by hamance on 2016/10/10.
//

#ifndef CVM_ASSIGNMENTS_MAP_OF_CATEGORICAL_PARAMETERS_H
#define CVM_ASSIGNMENTS_MAP_OF_CATEGORICAL_PARAMETERS_H

#include <vector>

using namespace std;

class MAP_of_Categorical_Parameters {

public:

    vector<double> randomSample(int max, int num, vector<double> weight);

    vector<double> mapOfCat(vector<double> input, vector<double> alpha);

    void estimateError(vector<double> original, vector<double> predict);


};

void testMAPofCat();

#endif //CVM_ASSIGNMENTS_MAP_OF_CATEGORICAL_PARAMETERS_H
