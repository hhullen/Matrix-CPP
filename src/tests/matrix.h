#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <fstream>
#include <functional>
#include <memory>
#include <string>

using std::atof;
using std::getline;
using std::ifstream;
using std::invalid_argument;
using std::isdigit;
using std::ofstream;
using std::out_of_range;
using std::sscanf;

namespace hhullen {

template <class T>
concept arithmetic = requires(T var) { std::is_arithmetic_v<T>; };

template <arithmetic Type>
class Matrix {
  using RowPtr = std::unique_ptr<Type[]>;
  using MatrixPtr = std::unique_ptr<RowPtr[]>;
  using Str = std::string;

 public:
  Matrix();
  Matrix(size_t rows, size_t cols);
  Matrix(const Matrix<Type>& other);
  Matrix(Matrix<Type>&& other);
  ~Matrix();

  void Load(const Str& file_path);
  void Save(const Str& file_path);

  size_t rows() const;
  size_t cols() const;
  void set_rows(size_t new_val);
  void set_cols(size_t new_val);

  void SwapRows(const size_t row_1, const size_t row_2);
  void ProcessRows(const size_t row_1, const size_t row_2,
                   std::function<void(Type&, Type&)>& lambda);
  void ProcessRow(const size_t row, std::function<void(Type&)>& lambda);
  void ProcessEach(std::function<void(Type&)>& lambda);
  void HadamardProduct(const Matrix<Type>& other);
  Matrix<Type> Transpose() const;
  void set(size_t i, size_t j, Type value);

  bool operator==(const Matrix<Type>& other) const;
  Matrix<Type>& operator=(const Matrix<Type>& other);
  Matrix<Type> operator+(const Matrix<Type>& other) const;
  Matrix<Type> operator-(const Matrix<Type>& other) const;
  Matrix<Type> operator*(const Matrix<Type>& other) const;
  Matrix<Type> operator+=(const Matrix<Type>& other);
  Matrix<Type> operator-=(const Matrix<Type>& other);
  Matrix<Type> operator*=(const Matrix<Type>& other);
  Type& operator()(size_t i, size_t j);
  Type operator()(size_t i, size_t j) const;

 private:
  size_t rows_, cols_;
  MatrixPtr matrix_;
  const double kAccuracy = 0.000001 * std::is_floating_point_v<Type>;

  void init_matrix();
  void IsInputFileOpened(const ifstream& file);
  void IsOutputFileOpened(const ofstream& file);
  void ReadMatrixSize(ifstream& file);
  void ReadMatrix(ifstream& file);
  void ReadLineToMatrixRow(const Str& line, size_t row);
  void ShiftToNextNumber(const Str& line, size_t* i);
  bool IsNumberChar(char sym);
  void WriteMatrixSize(ofstream& file);
  void WriteMatrix(ofstream& file);
};

// class Matrix {
//  public:

//  private:
//   int rows_, cols_;
//   double** matrix_;

// void init_matrix(bool fill);
//   void copy_data_other_to_this_matrix(double** other_matrix);
//   void calculate_multiplied_matrix_element(const Matrix& other, int i, int j,
//                                            double* res);
//   void fill_with_zeros(int current_row);
//   double calculate_2d_Determinant();
//   double calculate_3d_Determinant();
//   double calculate_Gauss_Determinant();
//   double multiply_diagonal(Matrix* buffer);
//   void process_the_row(Matrix* buffer, int row, int col, bool* is_det_zero);
//   void scan_column_to_find_nonzero_num(Matrix* buffer, const int row,
//                                        const int col, bool* is_det_zero);
//   void summ_rows(Matrix* buffer, const int row_num, const int row_zero);
//   double algebraic_addition(Matrix* initial_matrix, int row, int col);
//   void make_matrix_minor(Matrix* initial_matrix, int row, int col,
//                          Matrix* minor);

// };

}  // namespace hhullen

#endif  // SRC_MATRIX_H_
