cmake_minimum_required(VERSION 3.6)
project(CVM_Assignments)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Algo_4.1/Max_Likelihood_Learning_of_Normal_Distribution.cpp Algo_4.1/Max_Likelihood_Learning_of_Normal_Distribution.h Algo_4.2/MAP_of_Univariate_Normal_Parameters.cpp Algo_4.2/MAP_of_Univariate_Normal_Parameters.h Algo_4.3/Bayesian_to_Univariate_Normal_Distribution.cpp Algo_4.3/Bayesian_to_Univariate_Normal_Distribution.h Algo_4.4/ML_of_Categorical_Parameters.cpp Algo_4.4/ML_of_Categorical_Parameters.h main.h)
add_executable(CVM_Assignments ${SOURCE_FILES} main.cpp Algo_4.1/Max_Likelihood_Learning_of_Normal_Distribution.cpp Algo_4.1/Max_Likelihood_Learning_of_Normal_Distribution.h Algo_4.2/MAP_of_Univariate_Normal_Parameters.cpp Algo_4.2/MAP_of_Univariate_Normal_Parameters.h Algo_4.3/Bayesian_to_Univariate_Normal_Distribution.cpp Algo_4.3/Bayesian_to_Univariate_Normal_Distribution.h Algo_4.4/ML_of_Categorical_Parameters.cpp Algo_4.4/ML_of_Categorical_Parameters.h)