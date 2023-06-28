#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

using std::atof;
using std::getline;
using std::ifstream;
using std::invalid_argument;
using std::isdigit;
using std::memset;
using std::ofstream;
using std::out_of_range;
using std::sscanf;

namespace hhullen {
template <class T>
concept arithmetic = requires(T var) { std::is_arithmetic_v<T>; };

template <arithmetic Type>
class Matrix {
  using RowPtr = std::shared_ptr<Type[]>;
  using MatrixPtr = std::shared_ptr<RowPtr[]>;
  using Str = std::string;

 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix<Type>& other);
  Matrix(Matrix<Type>&& other);
  ~Matrix();

  void Load(const Str& file_path);
  void Save(const Str& file_path);

  int rows() const;
  int cols() const;
  void set_rows(int new_val);
  void set_cols(int new_val);

  void SwapRows(const int row_1, const int row_2);
  void ProcessRows(const int row_1, const int row_2,
                   const std::function<void(Type&, Type&)>& lambda);
  void ProcessRow(const int row, const std::function<void(Type&)>& lambda);
  void ProcessEach(const std::function<void(Type&)>& lambda);
  void HadamardProduct(const Matrix<Type>& other);
  Matrix<Type> Transpose() const;
  void set(int i, int j, Type value);

  bool operator==(const Matrix<Type>& other) const;
  bool operator!=(const Matrix<Type>& other) const;
  Matrix<Type>& operator=(const Matrix<Type>& other);
  Matrix<Type> operator+(const Matrix<Type>& other) const;
  Matrix<Type> operator-(const Matrix<Type>& other) const;
  Matrix<Type> operator*(const Matrix<Type>& other) const;
  template <arithmetic Val>
  Matrix<Type> operator*(const Val value) const;
  Matrix<Type> operator+=(const Matrix<Type>& other);
  Matrix<Type> operator-=(const Matrix<Type>& other);
  Matrix<Type> operator*=(const Matrix<Type>& other);
  template <arithmetic Val>
  Matrix<Type> operator*=(const Val value);
  Type& operator()(int i, int j);
  Type operator()(int i, int j) const;

 private:
  int rows_, cols_;
  MatrixPtr matrix_;
  const double kAccuracy = 0.000001 * std::is_floating_point_v<Type>;

  void init_matrix(bool fill_with_zero = false);
  void IsInputFileOpened(const ifstream& file);
  void IsOutputFileOpened(const ofstream& file);
  void ReadMatrixSize(ifstream& file);
  void ReadMatrix(ifstream& file);
  void ReadLineToMatrixRow(const Str& line, int row);
  void ShiftToNextNumber(const Str& line, int* i);
  bool IsNumberChar(char sym);
  void WriteMatrixSize(ofstream& file);
  void WriteMatrix(ofstream& file);
};

}  // namespace hhullen

#endif  // SRC_MATRIX_H_
