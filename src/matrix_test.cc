#include "matrix_test.h"

TEST(test_constructor, default_constructor) {
  Matrix<double> test(5, 5);

  run_through_matrix_num(test, 0.00000001);
}

TEST(test_constructor, pametrized_constructor) {
  Matrix<double> test(5, 5);

  run_through_matrix_num(test, 0.00000001);
  EXPECT_EQ(test.cols(), 5);
  EXPECT_EQ(test.rows(), 5);
}

TEST(test_constructor, copy_constructor) {
  Matrix<double> test_init(5, 5);
  fill_matrix(&test_init, 2);

  Matrix<double> test(test_init);

  run_through_matrix_num(test, 2);
  EXPECT_EQ(test.cols(), 5);
  EXPECT_EQ(test.rows(), 5);
}

TEST(test_constructor, move_constructor) {
  Matrix<double> test_init(5, 5);
  fill_matrix(&test_init, 2);

  Matrix<double> test(std::move(test_init));

  run_through_matrix_num(test, 2);
  EXPECT_EQ(test.cols(), 5);
  EXPECT_EQ(test.rows(), 5);
}

TEST(test_operations, IsEqual) {
  Matrix<double> test, test2;

  fill_matrix(&test, 2.00000001);
  fill_matrix(&test2, 2);
  EXPECT_TRUE(test == test2);
}

TEST(test_operations, Summarize) {
  Matrix<double> test, test2;

  fill_matrix(&test, 2.00000001);
  test += test;
  fill_matrix(&test2, 4);
  EXPECT_TRUE(test == test2);
}

TEST(test_operations, Substract) {
  Matrix<double> test, test2;

  fill_matrix(&test, 4.00000001);
  fill_matrix(&test2, 2);
  test -= test2;
  EXPECT_TRUE(test == test2);
}

TEST(test_operations, MultiplyNumber) {
  Matrix<double> test, test2;

  fill_matrix(&test, 4.00000001);
  fill_matrix(&test2, 16);
  test *= 4;
  EXPECT_TRUE(test == test2);
}

TEST(test_operations, Multiply) {
  Matrix<double> test(3, 2), test2(2, 3), result(3, 3);

  test.set(0, 0, 1);
  test.set(0, 1, 4);
  test.set(1, 0, 2);
  test.set(1, 1, 5);
  test.set(2, 0, 3);
  test.set(2, 1, 6);

  test2.set(0, 0, 1);
  test2.set(0, 1, -1);
  test2.set(0, 2, 1);
  test2.set(1, 0, 2);
  test2.set(1, 1, 3);
  test2.set(1, 2, 4);

  result.set(0, 0, 9);
  result.set(0, 1, 11);
  result.set(0, 2, 17);
  result.set(1, 0, 12);
  result.set(1, 1, 13);
  result.set(1, 2, 22);
  result.set(2, 0, 15);
  result.set(2, 1, 15);
  result.set(2, 2, 27);

  test *= test2;
  EXPECT_TRUE(test == result);
}

TEST(test_operations, Transpose) {
  Matrix<double> test(3, 2), result(2, 3);

  test.set(0, 0, 1);
  test.set(0, 1, 4);
  test.set(1, 0, 2);
  test.set(1, 1, 5);
  test.set(2, 0, 3);
  test.set(2, 1, 6);

  result.set(0, 0, 1);
  result.set(0, 1, 2);
  result.set(0, 2, 3);
  result.set(1, 0, 4);
  result.set(1, 1, 5);
  result.set(1, 2, 6);

  test = test.Transpose();
  EXPECT_TRUE(test == result);
}

TEST(test_accessors_mutators, set__get_element) {
  Matrix<double> test(3, 3);

  test.set(2, 2, 13.5);
  EXPECT_TRUE(test(2, 2) - 13.5 < kAccuracy);
}

TEST(test_accessors_mutators, rows__cols) {
  Matrix<double> test(3, 6);

  EXPECT_TRUE(test.cols() == 6);
  EXPECT_TRUE(test.rows() == 3);
}

TEST(test_accessors_mutators, set_rows__set_cols) {
  Matrix<double> test(3, 3);

  test.set_cols(5);
  test.set_rows(10);

  fill_matrix(&test, 42.1);

  EXPECT_TRUE(test.cols() == 5);
  EXPECT_TRUE(test.rows() == 10);

  EXPECT_TRUE(test(0, 4) - 42.1 < kAccuracy);
  EXPECT_TRUE(test(9, 4) - 42.1 < kAccuracy);
}

TEST(test_operators, eq_eq) {
  Matrix<double> test(3, 3);

  fill_matrix(&test, 9.123);
  EXPECT_TRUE(test == test);
}

TEST(test_operators, plus) {
  Matrix<double> test(3, 3), result(3, 3);

  fill_matrix(&test, 7);
  fill_matrix(&result, 14);
  test = test + test;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, minus) {
  Matrix<double> test(3, 3), result(3, 3);

  fill_matrix(&test, 14);
  fill_matrix(&result, 7);
  test = test - result;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, multiply) {
  Matrix<double> test(3, 2), test2(2, 3), result(3, 3);

  test.set(0, 0, 1);
  test.set(0, 1, 4);
  test.set(1, 0, 2);
  test.set(1, 1, 5);
  test.set(2, 0, 3);
  test.set(2, 1, 6);

  test2.set(0, 0, 1);
  test2.set(0, 1, -1);
  test2.set(0, 2, 1);
  test2.set(1, 0, 2);
  test2.set(1, 1, 3);
  test2.set(1, 2, 4);

  result.set(0, 0, 9);
  result.set(0, 1, 11);
  result.set(0, 2, 17);
  result.set(1, 0, 12);
  result.set(1, 1, 13);
  result.set(1, 2, 22);
  result.set(2, 0, 15);
  result.set(2, 1, 15);
  result.set(2, 2, 27);

  test = test * test2;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, plus_eq) {
  Matrix<double> test(3, 3), result(3, 3);

  fill_matrix(&test, 7);
  fill_matrix(&result, 14);
  test += test;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, minus_eq) {
  Matrix<double> test(3, 3), result(3, 3);

  fill_matrix(&test, 14);
  fill_matrix(&result, 7);
  test -= result;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, multiply_eq) {
  Matrix<double> test(3, 2), test2(2, 3), result(3, 3);

  test.set(0, 0, 1);
  test.set(0, 1, 4);
  test.set(1, 0, 2);
  test.set(1, 1, 5);
  test.set(2, 0, 3);
  test.set(2, 1, 6);

  test2.set(0, 0, 1);
  test2.set(0, 1, -1);
  test2.set(0, 2, 1);
  test2.set(1, 0, 2);
  test2.set(1, 1, 3);
  test2.set(1, 2, 4);

  result.set(0, 0, 9);
  result.set(0, 1, 11);
  result.set(0, 2, 17);
  result.set(1, 0, 12);
  result.set(1, 1, 13);
  result.set(1, 2, 22);
  result.set(2, 0, 15);
  result.set(2, 1, 15);
  result.set(2, 2, 27);

  test *= test2;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, indexation) {
  Matrix<double> test(4, 4);

  fill_matrix(&test, 39.567);

  EXPECT_TRUE(test(0, 0) - 39.567 < kAccuracy);
  EXPECT_TRUE(test(1, 0) - 39.567 < kAccuracy);
  EXPECT_TRUE(test(0, 2) - 39.567 < kAccuracy);
  EXPECT_TRUE(test(2, 0) - 39.567 < kAccuracy);
  EXPECT_TRUE(test(1, 1) - 39.567 < kAccuracy);
  EXPECT_TRUE(test(2, 2) - 39.567 < kAccuracy);
  EXPECT_TRUE(test(3, 3) - 39.567 < kAccuracy);
}

TEST(test_operators, hadamart_product) {
  Matrix<double> test(4, 1);
  Matrix<double> test2(4, 1);

  test(0, 0) = 2;
  test(1, 0) = 3;
  test(2, 0) = 4;
  test(3, 0) = 5;

  test2(0, 0) = 2;
  test2(1, 0) = 3;
  test2(2, 0) = 4;
  test2(3, 0) = 5;

  test.HadamardProduct(test2);

  EXPECT_EQ(test(0, 0), 4);
  EXPECT_EQ(test(1, 0), 9);
  EXPECT_EQ(test(2, 0), 16);
  EXPECT_EQ(test(3, 0), 25);
}

TEST(test_supports, load_from_file_correct) {
  Matrix<double> test;
  string path = string("datasets/marix_correct.txt");

  test.Load(path);

  EXPECT_EQ(test.rows(), 5);
  EXPECT_EQ(test.cols(), 5);

  EXPECT_EQ(test(0, 0), 1);
  EXPECT_EQ(test(1, 0), 2);
  EXPECT_EQ(test(2, 0), 4);
  EXPECT_EQ(test(3, 0), 9);
  EXPECT_EQ(test(4, 0), 5);

  EXPECT_EQ(test(0, 1), 3);
  EXPECT_EQ(test(1, 1), 4);
  EXPECT_EQ(test(2, 1), 5);
  EXPECT_EQ(test(3, 1), 0);
  EXPECT_EQ(test(4, 1), 5);

  EXPECT_EQ(test(0, 2), 4);
  EXPECT_EQ(test(1, 2), 6);
  EXPECT_EQ(test(2, 2), 6);
  EXPECT_EQ(test(3, 2), 8);
  EXPECT_EQ(test(4, 2), 6);

  EXPECT_EQ(test(0, 3), 5);
  EXPECT_EQ(test(1, 3), 7);
  EXPECT_EQ(test(2, 3), 7);
  EXPECT_EQ(test(3, 3), 7);
  EXPECT_EQ(test(4, 3), 7);

  EXPECT_EQ(test(0, 4), 6);
  EXPECT_EQ(test(1, 4), 8);
  EXPECT_EQ(test(2, 4), 8);
  EXPECT_EQ(test(3, 4), 6);
  EXPECT_EQ(test(4, 4), 8.95);
}

TEST(test_supports, load_from_file_incorrect) {
  Matrix<double> test;
  string path = string("datasets/marix_incorrect.txt");

  test.Load(path);

  EXPECT_EQ(test.rows(), 5);
  EXPECT_EQ(test.cols(), 5);

  EXPECT_EQ(test(0, 0), 1);
  EXPECT_EQ(test(1, 0), 2);
  EXPECT_EQ(test(2, 0), 4);
  EXPECT_EQ(test(3, 0), 9);
  EXPECT_EQ(test(4, 0), 5);

  EXPECT_EQ(test(0, 1), 3);
  EXPECT_EQ(test(1, 1), 4);
  EXPECT_EQ(test(2, 1), 5);
  EXPECT_EQ(test(3, 1), 0);
  EXPECT_EQ(test(4, 1), 5);

  EXPECT_EQ(test(0, 2), 4);
  EXPECT_EQ(test(1, 2), 0);
  EXPECT_EQ(test(2, 2), 7);
  EXPECT_EQ(test(3, 2), 8);
  EXPECT_EQ(test(4, 2), 6);

  EXPECT_EQ(test(0, 3), 5);
  EXPECT_EQ(test(1, 3), 0);
  EXPECT_EQ(test(2, 3), 8);
  EXPECT_EQ(test(3, 3), 7);
  EXPECT_EQ(test(4, 3), 0);

  EXPECT_EQ(test(0, 4), 6);
  EXPECT_EQ(test(1, 4), 0);
  EXPECT_EQ(test(2, 4), 0);
  EXPECT_EQ(test(3, 4), 6);
  EXPECT_EQ(test(4, 4), 0);
}

TEST(test_supports, write_file) {
  Matrix<double> test;
  string path = string("datasets/marix_correct.txt");
  test.Load(path);

  test.Save("matrix_output.txt");
  test.Load("matrix_output.txt");

  EXPECT_EQ(test.rows(), 5);
  EXPECT_EQ(test.cols(), 5);

  EXPECT_EQ(test(0, 0), 1);
  EXPECT_EQ(test(1, 0), 2);
  EXPECT_EQ(test(2, 0), 4);
  EXPECT_EQ(test(3, 0), 9);
  EXPECT_EQ(test(4, 0), 5);

  EXPECT_EQ(test(0, 1), 3);
  EXPECT_EQ(test(1, 1), 4);
  EXPECT_EQ(test(2, 1), 5);
  EXPECT_EQ(test(3, 1), 0);
  EXPECT_EQ(test(4, 1), 5);

  EXPECT_EQ(test(0, 2), 4);
  EXPECT_EQ(test(1, 2), 6);
  EXPECT_EQ(test(2, 2), 6);
  EXPECT_EQ(test(3, 2), 8);
  EXPECT_EQ(test(4, 2), 6);

  EXPECT_EQ(test(0, 3), 5);
  EXPECT_EQ(test(1, 3), 7);
  EXPECT_EQ(test(2, 3), 7);
  EXPECT_EQ(test(3, 3), 7);
  EXPECT_EQ(test(4, 3), 7);

  EXPECT_EQ(test(0, 4), 6);
  EXPECT_EQ(test(1, 4), 8);
  EXPECT_EQ(test(2, 4), 8);
  EXPECT_EQ(test(3, 4), 6);
  EXPECT_EQ(test(4, 4), 8.95);
}

TEST(test_supports, multiply_row_to_number) {
  Matrix<double> test;
  string path = string("datasets/marix_correct.txt");
  test.Load(path);

  test.ProcessRow(2, [](double& value) { value *= 3; });

  EXPECT_EQ(test.rows(), 5);
  EXPECT_EQ(test.cols(), 5);

  EXPECT_EQ(test(0, 0), 1);
  EXPECT_EQ(test(1, 0), 2);
  EXPECT_EQ(test(2, 0), 12);
  EXPECT_EQ(test(3, 0), 9);
  EXPECT_EQ(test(4, 0), 5);

  EXPECT_EQ(test(0, 1), 3);
  EXPECT_EQ(test(1, 1), 4);
  EXPECT_EQ(test(2, 1), 15);
  EXPECT_EQ(test(3, 1), 0);
  EXPECT_EQ(test(4, 1), 5);

  EXPECT_EQ(test(0, 2), 4);
  EXPECT_EQ(test(1, 2), 6);
  EXPECT_EQ(test(2, 2), 18);
  EXPECT_EQ(test(3, 2), 8);
  EXPECT_EQ(test(4, 2), 6);

  EXPECT_EQ(test(0, 3), 5);
  EXPECT_EQ(test(1, 3), 7);
  EXPECT_EQ(test(2, 3), 21);
  EXPECT_EQ(test(3, 3), 7);
  EXPECT_EQ(test(4, 3), 7);

  EXPECT_EQ(test(0, 4), 6);
  EXPECT_EQ(test(1, 4), 8);
  EXPECT_EQ(test(2, 4), 24);
  EXPECT_EQ(test(3, 4), 6);
  EXPECT_EQ(test(4, 4), 8.95);
}

TEST(test_supports, exchqnge_rows) {
  Matrix<double> test;
  string path = string("datasets/marix_correct.txt");
  test.Load(path);

  test.ProcessRow(2, [](double& value) { value *= 3; });
  test.SwapRows(0, 2);

  EXPECT_EQ(test.rows(), 5);
  EXPECT_EQ(test.cols(), 5);

  EXPECT_EQ(test(0, 0), 12);
  EXPECT_EQ(test(1, 0), 2);
  EXPECT_EQ(test(2, 0), 1);
  EXPECT_EQ(test(3, 0), 9);
  EXPECT_EQ(test(4, 0), 5);

  EXPECT_EQ(test(0, 1), 15);
  EXPECT_EQ(test(1, 1), 4);
  EXPECT_EQ(test(2, 1), 3);
  EXPECT_EQ(test(3, 1), 0);
  EXPECT_EQ(test(4, 1), 5);

  EXPECT_EQ(test(0, 2), 18);
  EXPECT_EQ(test(1, 2), 6);
  EXPECT_EQ(test(2, 2), 4);
  EXPECT_EQ(test(3, 2), 8);
  EXPECT_EQ(test(4, 2), 6);

  EXPECT_EQ(test(0, 3), 21);
  EXPECT_EQ(test(1, 3), 7);
  EXPECT_EQ(test(2, 3), 5);
  EXPECT_EQ(test(3, 3), 7);
  EXPECT_EQ(test(4, 3), 7);

  EXPECT_EQ(test(0, 4), 24);
  EXPECT_EQ(test(1, 4), 8);
  EXPECT_EQ(test(2, 4), 6);
  EXPECT_EQ(test(3, 4), 6);
  EXPECT_EQ(test(4, 4), 8.95);
}

TEST(test_supports, summarize_rows) {
  Matrix<double> test;
  string path = string("datasets/marix_correct.txt");
  test.Load(path);

  test.ProcessRow(2, [](double& value) { value *= 3; });
  test.SwapRows(0, 2);
  test.ProcessRows(0, 2, [](double& v_1, double& v_2) { v_2 += v_1; });

  EXPECT_EQ(test.rows(), 5);
  EXPECT_EQ(test.cols(), 5);

  EXPECT_EQ(test(0, 0), 12);
  EXPECT_EQ(test(1, 0), 2);
  EXPECT_EQ(test(2, 0), 13);
  EXPECT_EQ(test(3, 0), 9);
  EXPECT_EQ(test(4, 0), 5);

  EXPECT_EQ(test(0, 1), 15);
  EXPECT_EQ(test(1, 1), 4);
  EXPECT_EQ(test(2, 1), 18);
  EXPECT_EQ(test(3, 1), 0);
  EXPECT_EQ(test(4, 1), 5);

  EXPECT_EQ(test(0, 2), 18);
  EXPECT_EQ(test(1, 2), 6);
  EXPECT_EQ(test(2, 2), 22);
  EXPECT_EQ(test(3, 2), 8);
  EXPECT_EQ(test(4, 2), 6);

  EXPECT_EQ(test(0, 3), 21);
  EXPECT_EQ(test(1, 3), 7);
  EXPECT_EQ(test(2, 3), 26);
  EXPECT_EQ(test(3, 3), 7);
  EXPECT_EQ(test(4, 3), 7);

  EXPECT_EQ(test(0, 4), 24);
  EXPECT_EQ(test(1, 4), 8);
  EXPECT_EQ(test(2, 4), 30);
  EXPECT_EQ(test(3, 4), 6);
  EXPECT_EQ(test(4, 4), 8.95);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void run_through_matrix_num(Matrix<double>& test, double value) {
  for (int i = 0; i < test.rows(); ++i) {
    for (int j = 0; j < test.cols(); ++j) {
      EXPECT_NEAR(test(i, j), value, 0.0000001);
    }
  }
}

void fill_matrix(Matrix<double>* test, double value) {
  for (int i = 0; i < test->rows(); ++i) {
    for (int j = 0; j < test->cols(); ++j) {
      test->set(i, j, value);
    }
  }
}
