cmake_minimum_required(VERSION 3.6)
project(CVM_Assignments)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(OpenCV_LIB_PATH D:/Documents/OpenCV/3.0.0/opencv/build/x64/vc12/lib)
set(OpenCV_LIB_DIR D:/Documents/OpenCV/3.0.0/opencv/build/x64/vc12/lib)
set(OpenCV_LIBS D:/Documents/OpenCV/3.0.0/opencv/build/x64/vc12/lib)
set(CMAKE_PREFIX_PATH D:/Documents/OpenCV/3.0.0/opencv/build)
set(OpenCV_DIR D:/Documents/OpenCV/3.0.0/opencv/build/x64/vc12)

include_directories(D:/Documents/OpenCV/3.0.0/opencv/build/include)

FIND_PACKAGE(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp Algo_4.1/Max_Likelihood_Learning_of_Normal_Distribution.cpp Algo_4.1/Max_Likelihood_Learning_of_Normal_Distribution.h Algo_4.2/MAP_of_Univariate_Normal_Parameters.cpp Algo_4.2/MAP_of_Univariate_Normal_Parameters.h Algo_4.3/Bayesian_to_Univariate_Normal_Distribution.cpp Algo_4.3/Bayesian_to_Univariate_Normal_Distribution.h Algo_4.4/ML_of_Categorical_Parameters.cpp Algo_4.4/ML_of_Categorical_Parameters.h main.h Algo_4.5/MAP_of_Categorical_Parameters.cpp Algo_4.5/MAP_of_Categorical_Parameters.h Algo_6.1/Basic_Generative_Classifier.cpp Algo_6.1/Basic_Generative_Classifier.h Algo_6.1/Basic_Generative_Classifier_Eigen.cpp Algo_6.1/Basic_Generative_Classifier_Eigen.h test.cpp test.h Algo_7.1/Fitting_Mixture_of_Gaussians.cpp Algo_7.1/Fitting_Mixture_of_Gaussians.h Algo_7.2/Fitting_the_t_distribution.cpp Algo_7.2/Fitting_the_t_distribution.h Algo_7.1/Eigen_multivariate_normal_distribution.cpp Algo_7.1/Eigen_multivariate_normal_distribution.h)
add_executable(CVM_Assignments ${SOURCE_FILES} main.cpp Algo_4.1/Max_Likelihood_Learning_of_Normal_Distribution.cpp Algo_4.1/Max_Likelihood_Learning_of_Normal_Distribution.h Algo_4.2/MAP_of_Univariate_Normal_Parameters.cpp Algo_4.2/MAP_of_Univariate_Normal_Parameters.h Algo_4.3/Bayesian_to_Univariate_Normal_Distribution.cpp Algo_4.3/Bayesian_to_Univariate_Normal_Distribution.h Algo_4.4/ML_of_Categorical_Parameters.cpp Algo_4.4/ML_of_Categorical_Parameters.h Algo_6.1/Basic_Generative_Classifier.cpp)

target_link_libraries(CVM_Assignments ${OpenCV_LIBS})