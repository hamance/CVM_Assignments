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
    m << 1,2,3,4,5,6,7,8,9;
    cout<<m<<endl;
    cout<<m.row(2).head(2);
}