//
// Created by hamance on 2016/10/13.
//

#include "test.h"

#include <iostream>
#include "lib/Eigen/Dense"

using Eigen::Matrix3f;
using namespace std;

void testEigen() {
    Matrix3f m;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m.col(i)<< m;
        }
    }
    cout<<m;
}