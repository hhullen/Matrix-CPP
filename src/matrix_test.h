#ifndef SRC_MATRIX_TEST_H_
#define SRC_MATRIX_TEST_H_

#include <gtest/gtest.h>

#include "matrix.h"
using hhullen::Matrix;

void run_through_matrix_num(Matrix test, double value);
void fill_matrix(Matrix* test, double value);

#endif  // SRC_MATRIX_TEST_H_
