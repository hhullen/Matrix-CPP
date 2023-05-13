#include "matrix_test.h"

TEST(test_constructor, default_constructor) {
  Matrix test;

  run_through_matrix_num(test, 0.00000001);
}

TEST(test_constructor, pametrized_constructor) {
  Matrix test(5, 5);

  run_through_matrix_num(test, 0.00000001);
  EXPECT_EQ(test.get_cols(), 5);
  EXPECT_EQ(test.get_rows(), 5);
}

TEST(test_constructor, copy_constructor) {
  Matrix test_init(5, 5);
  fill_matrix(&test_init, 2);

  Matrix test(test_init);

  run_through_matrix_num(test, 2);
  EXPECT_EQ(test.get_cols(), 5);
  EXPECT_EQ(test.get_rows(), 5);
}

TEST(test_constructor, move_constructor) {
  Matrix test_init(5, 5);
  fill_matrix(&test_init, 2);

  Matrix test(std::move(test_init));

  run_through_matrix_num(test, 2);
  EXPECT_EQ(test.get_cols(), 5);
  EXPECT_EQ(test.get_rows(), 5);
}

TEST(test_operations, IsEqual) {
  Matrix test, test2;

  fill_matrix(&test, 2.00000001);
  fill_matrix(&test2, 2);
  EXPECT_TRUE(test.IsEqual(test2));
}

TEST(test_operations, Summarize) {
  Matrix test, test2;

  fill_matrix(&test, 2.00000001);
  test.Summarize(test);
  fill_matrix(&test2, 4);
  EXPECT_TRUE(test.IsEqual(test2));
}

TEST(test_operations, Substract) {
  Matrix test, test2;

  fill_matrix(&test, 4.00000001);
  fill_matrix(&test2, 2);
  test.Substract(test2);
  EXPECT_TRUE(test.IsEqual(test2));
}

TEST(test_operations, MultiplyNumber) {
  Matrix test, test2;

  fill_matrix(&test, 4.00000001);
  fill_matrix(&test2, 16);
  test.MultiplyNumber(4);
  EXPECT_TRUE(test.IsEqual(test2));
}

TEST(test_operations, Multiply) {
  Matrix test(3, 2), test2(2, 3), result(3, 3);

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 4);
  test.set_element(1, 0, 2);
  test.set_element(1, 1, 5);
  test.set_element(2, 0, 3);
  test.set_element(2, 1, 6);

  test2.set_element(0, 0, 1);
  test2.set_element(0, 1, -1);
  test2.set_element(0, 2, 1);
  test2.set_element(1, 0, 2);
  test2.set_element(1, 1, 3);
  test2.set_element(1, 2, 4);

  result.set_element(0, 0, 9);
  result.set_element(0, 1, 11);
  result.set_element(0, 2, 17);
  result.set_element(1, 0, 12);
  result.set_element(1, 1, 13);
  result.set_element(1, 2, 22);
  result.set_element(2, 0, 15);
  result.set_element(2, 1, 15);
  result.set_element(2, 2, 27);

  test.Multiply(test2);
  EXPECT_TRUE(test.IsEqual(result));
}

TEST(test_operations, Transpose) {
  Matrix test(3, 2), result(2, 3);

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 4);
  test.set_element(1, 0, 2);
  test.set_element(1, 1, 5);
  test.set_element(2, 0, 3);
  test.set_element(2, 1, 6);

  result.set_element(0, 0, 1);
  result.set_element(0, 1, 2);
  result.set_element(0, 2, 3);
  result.set_element(1, 0, 4);
  result.set_element(1, 1, 5);
  result.set_element(1, 2, 6);

  test = test.Transpose();
  EXPECT_TRUE(test.IsEqual(result));
}

TEST(test_operations, CelculateComplements) {
  Matrix test(3, 3), result(3, 3);

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 2);
  test.set_element(0, 2, 3);
  test.set_element(1, 0, 0);
  test.set_element(1, 1, 4);
  test.set_element(1, 2, 2);
  test.set_element(2, 0, 5);
  test.set_element(2, 1, 2);
  test.set_element(2, 2, 1);

  result.set_element(0, 0, 0);
  result.set_element(0, 1, 10);
  result.set_element(0, 2, -20);
  result.set_element(1, 0, 4);
  result.set_element(1, 1, -14);
  result.set_element(1, 2, 8);
  result.set_element(2, 0, -8);
  result.set_element(2, 1, -2);
  result.set_element(2, 2, 4);

  test = test.CelculateComplements();
  EXPECT_TRUE(test.IsEqual(result));
}

TEST(test_operations, Determinant) {
  Matrix test(3, 3);
  double det = 0.0;

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 2);
  test.set_element(0, 2, 3);
  test.set_element(1, 0, 0);
  test.set_element(1, 1, 4);
  test.set_element(1, 2, 2);
  test.set_element(2, 0, 5);
  test.set_element(2, 1, 2);
  test.set_element(2, 2, 1);

  det = test.Determinant();
  EXPECT_TRUE(det - (-40) < kACCURACY);
}

TEST(test_operations, Inverse) {
  Matrix test(3, 3), result(3, 3);

  test.set_element(0, 0, 2);
  test.set_element(0, 1, 5);
  test.set_element(0, 2, 7);
  test.set_element(1, 0, 6);
  test.set_element(1, 1, 3);
  test.set_element(1, 2, 4);
  test.set_element(2, 0, 5);
  test.set_element(2, 1, -2);
  test.set_element(2, 2, -3);

  result.set_element(0, 0, 1);
  result.set_element(0, 1, -1);
  result.set_element(0, 2, 1);
  result.set_element(1, 0, -38);
  result.set_element(1, 1, 41);
  result.set_element(1, 2, -34);
  result.set_element(2, 0, 27);
  result.set_element(2, 1, -29);
  result.set_element(2, 2, 24);

  test = test.Inverse();
  EXPECT_TRUE(test.IsEqual(result));
}

TEST(test_accessors_mutators, set_element__get_element) {
  Matrix test(3, 3);

  test.set_element(2, 2, 13.5);
  EXPECT_TRUE(test.get_element(2, 2) - 13.5 < kACCURACY);
}

TEST(test_accessors_mutators, get_rows__get_cols) {
  Matrix test(3, 6);

  EXPECT_TRUE(test.get_cols() - 6 < kACCURACY);
  EXPECT_TRUE(test.get_rows() - 3 < kACCURACY);
}

TEST(test_accessors_mutators, set_rows__set_cols) {
  Matrix test(3, 3);

  test.set_cols(5);
  test.set_rows(10);

  fill_matrix(&test, 42.1);

  EXPECT_TRUE(test.get_cols() - 5 < kACCURACY);
  EXPECT_TRUE(test.get_rows() - 10 < kACCURACY);

  EXPECT_TRUE(test.get_element(0, 4) - 42.1 < kACCURACY);
  EXPECT_TRUE(test.get_element(9, 4) - 42.1 < kACCURACY);
}

TEST(test_operators, eq_eq) {
  Matrix test(3, 3);

  fill_matrix(&test, 9.123);
  EXPECT_TRUE(test == test);
}

TEST(test_operators, plus) {
  Matrix test(3, 3), result(3, 3);

  fill_matrix(&test, 7);
  fill_matrix(&result, 14);
  test = test + test;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, minus) {
  Matrix test(3, 3), result(3, 3);

  fill_matrix(&test, 14);
  fill_matrix(&result, 7);
  test = test - result;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, multiply) {
  Matrix test(3, 2), test2(2, 3), result(3, 3);

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 4);
  test.set_element(1, 0, 2);
  test.set_element(1, 1, 5);
  test.set_element(2, 0, 3);
  test.set_element(2, 1, 6);

  test2.set_element(0, 0, 1);
  test2.set_element(0, 1, -1);
  test2.set_element(0, 2, 1);
  test2.set_element(1, 0, 2);
  test2.set_element(1, 1, 3);
  test2.set_element(1, 2, 4);

  result.set_element(0, 0, 9);
  result.set_element(0, 1, 11);
  result.set_element(0, 2, 17);
  result.set_element(1, 0, 12);
  result.set_element(1, 1, 13);
  result.set_element(1, 2, 22);
  result.set_element(2, 0, 15);
  result.set_element(2, 1, 15);
  result.set_element(2, 2, 27);

  test = test * test2;
  EXPECT_TRUE(test.IsEqual(result));
}

TEST(test_operators, plus_eq) {
  Matrix test(3, 3), result(3, 3);

  fill_matrix(&test, 7);
  fill_matrix(&result, 14);
  test += test;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, minus_eq) {
  Matrix test(3, 3), result(3, 3);

  fill_matrix(&test, 14);
  fill_matrix(&result, 7);
  test -= result;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, multiply_eq) {
  Matrix test(3, 2), test2(2, 3), result(3, 3);

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 4);
  test.set_element(1, 0, 2);
  test.set_element(1, 1, 5);
  test.set_element(2, 0, 3);
  test.set_element(2, 1, 6);

  test2.set_element(0, 0, 1);
  test2.set_element(0, 1, -1);
  test2.set_element(0, 2, 1);
  test2.set_element(1, 0, 2);
  test2.set_element(1, 1, 3);
  test2.set_element(1, 2, 4);

  result.set_element(0, 0, 9);
  result.set_element(0, 1, 11);
  result.set_element(0, 2, 17);
  result.set_element(1, 0, 12);
  result.set_element(1, 1, 13);
  result.set_element(1, 2, 22);
  result.set_element(2, 0, 15);
  result.set_element(2, 1, 15);
  result.set_element(2, 2, 27);

  test *= test2;
  EXPECT_TRUE(test.IsEqual(result));
}

TEST(test_operators, indexation) {
  Matrix test(4, 4);

  fill_matrix(&test, 39.567);

  EXPECT_TRUE(test(0, 0) - 39.567 < kACCURACY);
  EXPECT_TRUE(test(1, 0) - 39.567 < kACCURACY);
  EXPECT_TRUE(test(0, 2) - 39.567 < kACCURACY);
  EXPECT_TRUE(test(2, 0) - 39.567 < kACCURACY);
  EXPECT_TRUE(test(1, 1) - 39.567 < kACCURACY);
  EXPECT_TRUE(test(2, 2) - 39.567 < kACCURACY);
  EXPECT_TRUE(test(3, 3) - 39.567 < kACCURACY);
}

TEST(test_operators, hadamart_product) {
  Matrix test(4, 1);
  Matrix test2(4, 1);

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
  Matrix test;
  string path = string("datasets/marix_correct.txt");

  test.Load(path);

  EXPECT_EQ(test.get_rows(), 5);
  EXPECT_EQ(test.get_cols(), 5);

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
  EXPECT_EQ(test(4, 4), 8);
}

TEST(test_supports, load_from_file_incorrect) {
  Matrix test;
  string path = string("datasets/marix_incorrect.txt");

  test.Load(path);

  EXPECT_EQ(test.get_rows(), 5);
  EXPECT_EQ(test.get_cols(), 5);

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
  Matrix test;
  string path = string("datasets/marix_correct.txt");
  test.Load(path);

  test.Save("matrix_output.txt");
  test.Load("matrix_output.txt");

  EXPECT_EQ(test.get_rows(), 5);
  EXPECT_EQ(test.get_cols(), 5);

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
  EXPECT_EQ(test(4, 4), 8);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void run_through_matrix_num(Matrix test, double value) {
  for (int i = 0; i < test.get_rows(); i += 1) {
    for (int j = 0; j < test.get_cols(); j += 1) {
      EXPECT_NEAR(test(i, j), value, kACCURACY);
    }
  }
}

void fill_matrix(Matrix* test, double value) {
  for (int i = 0; i < test->get_rows(); i += 1) {
    for (int j = 0; j < test->get_cols(); j += 1) {
      test->set_element(i, j, value);
    }
  }
}
