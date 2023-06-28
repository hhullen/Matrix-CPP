#ifndef SRC_MATRIX_TEST_H_
#define SRC_MATRIX_TEST_H_

#include <gtest/gtest.h>

#include "matrix.cc"

using hhullen::Matrix;
using std::string;

void run_through_matrix_num(Matrix<double>& test, double value);
void fill_matrix(Matrix<double>* test, double value);

const double kAccuracy = 0.000001;

#endif  // SRC_MATRIX_TEST_H_
