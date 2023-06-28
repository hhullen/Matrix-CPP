#include "matrix.h"

namespace hhullen {

/*
  Public functions
*/
/**
 * @brief Construct a new Matrix::Matrix object
 *
 */
template <arithmetic Type>
Matrix<Type>::Matrix() : rows_(1), cols_(1) {
  init_matrix();
}

/**
 * @brief Construct a new Matrix::Matrix object
 *
 * @param rows size_t type
 * @param cols size_t type
 */
template <arithmetic Type>
Matrix<Type>::Matrix(size_t rows, size_t cols) {
  if (rows < 1 && cols < 1) {
    throw invalid_argument("Creation matrix with less than 1x1 size");
  }

  rows_ = rows;
  cols_ = cols;
  init_matrix();
}

/**
 * @brief Construct a new Matrix::Matrix object
 *
 * @param other const Matrix& type
 */
template <arithmetic Type>
Matrix<Type>::Matrix(const Matrix<Type>& other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (other != *this) {
    init_matrix();
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

/**
 * @brief Construct a new Matrix::Matrix object
 *
 * @param other Matrix&& type
 */
template <arithmetic Type>
Matrix<Type>::Matrix(Matrix<Type>&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.matrix_ = MatrixPtr(nullptr);
  other.cols_ = 0;
  other.rows_ = 0;
}

/**
 * @brief Destroy the Matrix::Matrix object
 *
 */
template <arithmetic Type>
Matrix<Type>::~Matrix() {
  cols_ = 0;
  rows_ = 0;
}

/**
 * @brief Load matrix from file
 *
 * @param file_path const Str& type
 */
template <arithmetic Type>
void Matrix<Type>::Load(const Str& file_path) {
  ifstream file(file_path);

  IsInputFileOpened(file);
  ReadMatrixSize(file);
  ReadMatrix(file);

  file.close();
}

/**
 * @brief Save matrix to file
 *
 * @param file_path const Str& type
 */
template <arithmetic Type>
void Matrix<Type>::Save(const Str& file_path) {
  ofstream file(file_path);

  IsOutputFileOpened(file);
  WriteMatrixSize(file);
  WriteMatrix(file);

  file.close();
}

/**
 * @brief Swaps two rows in places
 *
 * @param row_1 const size_t index of first row to swap
 * @param row_2 const size_t index of another row to be swaped with first
 */
template <arithmetic Type>
void Matrix<Type>::SwapRows(const size_t row_1, const size_t row_2) {
  if (row_1 < 0 || row_1 >= rows_ || row_2 < 0 || row_2 >= rows_) {
    throw out_of_range("The matrix rows indices that is out of matrix size");
  }

  matrix_[row_1].swap(matrix_[row_2]);
}

/**
 * @brief Apply lambda function to values of two rows for whole cols
 *
 * @param row_1 const size_t type index of first row
 * @param row_2 const size_t type index of secont row
 * @param lambda std::function<void(Type&, Type&)> type lambda function
 */
template <arithmetic Type>
void Matrix<Type>::ProcessRows(const size_t row_1, const size_t row_2,
                               std::function<void(Type&, Type&)>& lambda) {
  if (row_1 < 0 || row_1 >= rows_ || row_2 < 0 || row_2 >= rows_) {
    throw out_of_range("Matrix rows with indices that is out of matrix size");
  }

  for (size_t col = 0; col < cols_; ++col) {
    lambda(matrix_[row_2][col], matrix_[row_1][col]);
  }
}

/**
 * @brief Apply lambda function to values of row
 *
 * @param row const size_t type index of row
 * @param lambda std::function<void(Type&)> type lambda function
 */
template <arithmetic Type>
void Matrix<Type>::ProcessRow(const size_t row,
                              std::function<void(Type&)>& lambda) {
  if (row < 0 || row >= rows_) {
    throw out_of_range("Matrix rows with indices that is out of matrix size");
  }

  for (size_t col = 0; col < cols_; ++col) {
    lambda(matrix_[row][col], matrix_[row][col]);
  }
}

/**
 * @brief Apply lambda function to each values of matrix
 *
 * @param lambda std::function<void(Type&)> type lambda function
 */
template <arithmetic Type>
void Matrix<Type>::ProcessEach(std::function<void(Type&)>& lambda) {
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < cols_; ++j) {
      lambda(matrix_[i][j]);
    }
  }
}

// /**
//  * @brief Summs this matrix with other
//  *
//  * @param other const Matrix& type
//  */
// void Matrix::Summarize(const Matrix& other) {
//   if (rows_ != other.rows_ || cols_ != other.cols_) {
//     throw invalid_argument("Matrix that is not square");
//   }

//   for (int i = 0; i < rows_; ++i) {
//     for (int j = 0; j < cols_; ++j) {
//       matrix_[i][j] += other.matrix_[i][j];
//     }
//   }
// }

// /**
//  * @brief Summarize row on "base_row" index to row on "summ_row" index
//  *
//  * @param base_row const int type index of row have to be added to another
//  * @param summ_row const int type index of row to be simmarized with
//  another
//  */
// void Matrix::SummarizeRows(const int base_row, const int summ_row) {
//   if (base_row < 0 || base_row >= rows_ || summ_row < 0 || summ_row >= rows_)
//   {
//     throw out_of_range("Matrix rows with indices that is out of matrix
//     size");
//   }

//   for (int col = 0; col < cols_; ++col) {
//     matrix_[summ_row][col] += matrix_[base_row][col];
//   }
// }

// /**
//  * @brief Add to some row another row multiplied by any number
//  *
//  * @param base_row const int type index of row to multiply by number and
//  add to
//  * another
//  * @param num const double type number to multiply base_row on
//  * @param summ_row const int type index of row to be simmarized with
//  another
//  */
// void Matrix::AddRowMultiplyedByNumberToRow(const int base_row, const double
// num,
//                                            const int summ_row) {
//   if (base_row < 0 || base_row >= rows_ || summ_row < 0 || summ_row >=
//   rows_)
//   {
//     throw out_of_range("Matrix rows with indices that is out of matrix
//     size");
//   }

//   for (int col = 0; col < cols_; ++col) {
//     matrix_[summ_row][col] += matrix_[base_row][col] * num;
//   }
// }

// /**
//  * @brief Add to some row another row summarized with any number
//  *
//  * @param base_row const int type index of row to summarize with number and
//  add
//  * to another
//  * @param num const double type number to summarize base_row with
//  * @param summ_row const int type index of row to be simmarized with
//  another
//  */
// void Matrix::AddRowSummarizedByNumberToRow(const int base_row, const double
// num,
//                                            const int summ_row) {
//   if (base_row < 0 || base_row >= rows_ || summ_row < 0 || summ_row >=
//   rows_)
//   {
//     throw out_of_range("Matrix rows with indices that is out of matrix
//     size");
//   }

//   for (int col = 0; col < cols_; ++col) {
//     matrix_[summ_row][col] += matrix_[base_row][col] + num;
//   }
// }

// /**
//  * @brief Substracts this matrix with other
//  *
//  * @param other const Matrix& type
//  */
// void Matrix::Substract(const Matrix& other) {
//   if (rows_ != other.rows_ || cols_ != other.cols_) {
//     throw invalid_argument("Substraction the matrix that is not square");
//   }

//   for (int i = 0; i < rows_; ++i) {
//     for (int j = 0; j < cols_; ++j) {
//       matrix_[i][j] -= other.matrix_[i][j];
//     }
//   }
// }

// /**
//  * @brief Multiplies every matrix element by "num" value
//  *
//  * @param num const double type
//  */
// void Matrix::MultiplyNumber(const double num) {
//   for (int i = 0; i < rows_; ++i) {
//     for (int j = 0; j < cols_; ++j) {
//       matrix_[i][j] *= num;
//     }
//   }
// }

// /**
//  * @brief Multiplies matrix of this object with other matrix with sizes m*k
//  and
//  * k*m
//  *
//  * @param other const Matrix& type
//  */
// void Matrix::Multiply(const Matrix& other) {
//   if (cols_ != other.rows_) {
//     throw invalid_argument(
//         "Multiplication matrix with different cols and rows");
//   }
//   double* buffer_row = nullptr;

//   for (int i = 0; i < rows_; ++i) {
//     buffer_row = new double[other.cols_];
//     for (int j = 0; j < other.cols_; ++j) {
//       buffer_row[j] = 0;
//       calculate_multiplied_matrix_element(other, i, j, &buffer_row[j]);
//     }
//     delete[] matrix_[i];
//     matrix_[i] = buffer_row;
//     buffer_row = nullptr;
//   }
//   cols_ = other.cols_;
// }

// /**
//  * @brief Multiplies matrix row to number
//  *
//  * @param row const int type row index
//  * @param num const double number to multiply by
//  */
// void Matrix::MuliplyRowNumber(const int row, const double num) {
//   if (row < 0 || row >= rows_) {
//     throw out_of_range("Row index out of matrix size");
//   }

//   for (int col = 0; col < cols_; ++col) {
//     matrix_[row][col] *= num;
//   }
// }

/**
 * @brief Calculates elementwise product
 *
 * @param other const Matrix& type
 */
template <arithmetic Type>
void Matrix<Type>::HadamardProduct(const Matrix<Type>& other) {
  if (cols_ != other.cols_ || rows_ != other.rows_) {
    throw invalid_argument("Hadamatd product with different cols or rows");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= other.matrix_[i][j];
    }
  }
}

/**
 * @brief Transposes matrix
 *
 * @return Matrix
 */
template <arithmetic Type>
Matrix<Type> Matrix<Type>::Transpose() const {
  Matrix<Type> returnable(cols_, rows_);

  for (int i = 0; i < returnable.rows_; ++i) {
    for (int j = 0; j < returnable.cols_; ++j) {
      returnable.matrix_[i][j] = matrix_[j][i];
    }
  }

  return returnable;
}

// /**
//  * @brief Calculates algebraic additions matrix of this object
//  *
//  * @return Matrix
//  */
// template <arithmetic Type>
// Matrix<Type> Matrix<Type>::CelculateComplements() {
//   if (cols_ != rows_) {
//     throw invalid_argument(
//         "Calculation complements of matrices with different cols and rows");
//   }
//   Matrix<Type> returnable(cols_, rows_);

//   if (cols_ != 1 && rows_ != 1) {
//     for (int i = 0; i < returnable.rows_; ++i) {
//       for (int j = 0; j < returnable.cols_; ++j) {
//         returnable.matrix_[i][j] =
//             algebraic_addition(this, i, j) * (-1 + !((i + j) % 2) * 2);
//       }
//     }
//   } else {
//     returnable.matrix_[0][0] = 1;
//   }

//   return returnable;
// }

// /**
//  * @brief Calculates Determinant
//  *
//  * @return double
//  */
// Type Matrix<Type>::Determinant() {
//   Type returnable = 0;

//   if (cols_ != rows_) {
//     throw invalid_argument(
//         "Calculation Determinant of matrix with different cols and rows");
//   }

//   if (rows_ == 1) {
//     returnable = matrix_[0][0];
//   } else if (rows_ == 2) {
//     returnable = calculate_2d_Determinant();
//   } else if (rows_ == 3) {
//     returnable = calculate_3d_Determinant();
//   } else {
//     returnable = calculate_Gauss_Determinant();
//   }

//   return returnable;
// }

// /**
//  * @brief Calculates inverse matrix
//  *
//  * @return Matrix
//  */
// Matrix Matrix::Inverse() {
//   double det = this->Determinant();

//   if (fabs(det) < kAccuracy) {
//     throw invalid_argument("Inversion of matrix with Determinant equals
//     0");
//   }
//   Matrix returnable(*this);

//   returnable = returnable.CelculateComplements();
//   returnable = returnable.Transpose();
//   returnable.MultiplyNumber(1 / det);

//   return returnable;
// }

// /**
//  * @brief Returns matrix element from i*j position
//  *
//  * @param i int type
//  * @param j int type
//  * @return double
//  */
// double Matrix::get_element(int i, int j) const {
//   if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
//     throw out_of_range("Getting element that is out of matrix range");
//   }

//   return matrix_[i][j];
// }

/**
 * @brief Sets "value" to matrix element in i*j position
 *
 * @param i size_t type
 * @param j size_t type
 * @param value double type
 */
template <arithmetic Type>
void Matrix<Type>::set(size_t i, size_t j, Type value) {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw out_of_range("Setting element that is out of matrix range");
  }

  matrix_[i][j] = value;
}

/**
 * @brief Returns amount of matrix rows
 *
 * @return size_t
 */
template <arithmetic Type>
size_t Matrix<Type>::rows() const {
  return rows_;
}

/**
 * @brief Returns amount of matrix columns
 *
 * @return size_t
 */
template <arithmetic Type>
size_t Matrix<Type>::cols() const {
  return cols_;
}

/**
 * @brief Sets new amount of matrix rows
 *
 * @param new_val size_t type
 */
template <arithmetic Type>
void Matrix<Type>::set_rows(size_t new_val) {
  if (new_val < 1) {
    throw invalid_argument("Setting rows amount that is equal or less than 0");
  }
  MatrixPtr buffer = MatrixPtr(new RowPtr[new_val]);

  if (new_val < rows_) {
    rows_ = new_val;
  }
  for (size_t i = 0; i < rows_; ++i) {
    buffer[i].swap(matrix_[i]);
  }
  matrix_.swap(buffer);

  for (size_t i = rows_; i < new_val; ++i) {
    matrix_[i] = RowPtr(new Type[cols_]);
  }
  rows_ = new_val;
}

/**
 * @brief Sets new amount of matrix cols
 *
 * @param new_val size_t type
 */
template <arithmetic Type>
void Matrix<Type>::set_cols(size_t new_val) {
  if (new_val <= 0) {
    throw invalid_argument("Setting cols amount that is equal or less than 0");
  }
  RowPtr buffer(nullptr);

  if (new_val < cols_) {
    cols_ = new_val;
  }
  for (size_t i = 0; i < rows_; ++i) {
    buffer.reset(new Type[new_val]);
    for (size_t j = 0; j < cols_; ++j) {
      buffer[j] = matrix_[i][j];
    }
    matrix_[i].swap(buffer);
  }
  cols_ = new_val;
}

/*
  Operators
*/
template <arithmetic Type>
bool Matrix<Type>::operator==(const Matrix<Type>& other) const {
  bool is_equal = true;

  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; is_equal && i < rows_; ++i) {
      for (int j = 0; is_equal && j < cols_; ++j) {
        is_equal = fabs(matrix_[i][j] - other.matrix_[i][j]) < kAccuracy;
      }
    }
  } else {
    is_equal = false;
  }

  return is_equal;
}

template <arithmetic Type>
Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type>& other) {
  this->~Matrix();
  *this = Matrix<Type>(other);

  return *this;
}

template <arithmetic Type>
Matrix<Type> Matrix<Type>::operator+(const Matrix<Type>& other) const {
  Matrix<Type> returnable(*this);
  return returnable += other;
}

template <arithmetic Type>
Matrix<Type> Matrix<Type>::operator-(const Matrix<Type>& other) const {
  Matrix<Type> returnable(*this);
  return returnable -= other;
}

template <arithmetic Type>
Matrix<Type> Matrix<Type>::operator*(const Matrix<Type>& other) const {
  Matrix returnable(*this);
  return returnable *= other;
}

template <arithmetic Type>
Matrix<Type> Matrix<Type>::operator+=(const Matrix<Type>& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw invalid_argument("Matrix that is not square");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }

  return *this;
}

template <arithmetic Type>
Matrix<Type> Matrix<Type>::operator-=(const Matrix<Type>& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw invalid_argument("Substraction the matrix that is not square");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }

  return *this;
}

template <arithmetic Type>
Matrix<Type> Matrix<Type>::operator*=(const Matrix<Type>& other) {
  if (cols_ != other.rows_) {
    throw invalid_argument(
        "Multiplication matrix with different cols and rows");
  }
  RowPtr buffer_row(nullptr);

  for (int i = 0; i < rows_; ++i) {
    buffer_row.reset(new Type[other.cols_]);
    for (int j = 0; j < other.cols_; ++j) {
      buffer_row[j] = 0;
      for (size_t k = 0; k < cols_; k += 1) {
        buffer_row[j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
    matrix_[i].reset(buffer_row);
  }
  cols_ = other.cols_;

  return *this;
}

template <arithmetic Type>
Type& Matrix<Type>::operator()(size_t i, size_t j) {
  if ((i < 0 || i > rows_) || j < 0 || j > cols_) {
    throw out_of_range("Setting element that is out of matrix range");
  }

  return matrix_[i][j];
}

template <arithmetic Type>
Type Matrix<Type>::operator()(size_t i, size_t j) const {
  if ((i < 0 || i > rows_) || j < 0 || j > cols_) {
    throw out_of_range("Setting element that is out of matrix range");
  }

  return matrix_[i][j];
}

/*
  Private functions
*/
template <arithmetic Type>
void Matrix<Type>::init_matrix() {
  matrix_ = MatrixPtr(new RowPtr[rows_]);
  for (size_t i = 0; i < rows_; ++i) {
    matrix_[i] = RowPtr(new Type[cols_]);
  }
}

// void Matrix::copy_data_other_to_this_matrix(double** other_matrix) {
//   for (int i = 0; i < rows_; ++i) {
//     for (int j = 0; j < cols_; ++j) {
//       matrix_[i][j] = other_matrix[i][j];
//     }
//   }
// }

// template <arithmetic Type>
// void Matrix<Type>::calculate_multiplied_matrix_element(const Matrix& other,
//                                                        size_t i, size_t j,
//                                                        Type* res) {
//   for (size_t k = 0; k < cols_; k += 1) {
//     *res += matrix_[i][k] * other.matrix_[k][j];
//   }
// }

// double Matrix::calculate_2d_Determinant() {
//   return matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
// }

// double Matrix::calculate_3d_Determinant() {
//   double returnable = 0.0;

//   returnable += matrix_[0][0] *
//                 (matrix_[1][1] * matrix_[2][2] - matrix_[2][1] *
//                 matrix_[1][2]);
//   returnable -= matrix_[0][1] *
//                 (matrix_[1][0] * matrix_[2][2] - matrix_[2][0] *
//                 matrix_[1][2]);
//   returnable += matrix_[0][2] *
//                 (matrix_[1][0] * matrix_[2][1] - matrix_[2][0] *
//                 matrix_[1][1]);

//   return returnable;
// }

// double Matrix::calculate_Gauss_Determinant() {
//   Matrix buffer(*this);
//   double returnable = 0.0;
//   int row_constrain = 0;
//   bool is_det_zero = false;

//   for (int i = 0; !is_det_zero && i < buffer.cols_; ++i) {
//     for (int j = buffer.rows_ - 1; !is_det_zero && j > row_constrain; j -=
//     1)
//     {
//       process_the_row(&buffer, j, i, &is_det_zero);
//     }
//     row_constrain += 1;
//   }
//   if (!is_det_zero) {
//     returnable = multiply_diagonal(&buffer);
//   }

//   return returnable;
// }

// double Matrix::multiply_diagonal(Matrix* buffer) {
//   double returnable = 1.0;

//   for (int i = 0; i < buffer->cols_; ++i) {
//     returnable *= buffer->matrix_[i][i];
//   }

//   return returnable;
// }

// void Matrix::process_the_row(Matrix* buffer, int row, int col,
//                              bool* is_det_zero) {
//   double prew_row_n = buffer->matrix_[row - 1][col];
//   double row_n = buffer->matrix_[row][col] * -1;

//   for (int k = col; k < buffer->cols_ && !*is_det_zero; k += 1) {
//     if (prew_row_n != 0) {
//       buffer->matrix_[row][k] =
//           (row_n / prew_row_n) * buffer->matrix_[row - 1][k] +
//           buffer->matrix_[row][k];
//     } else {
//       scan_column_to_find_nonzero_num(buffer, row - 1, k, is_det_zero);
//       prew_row_n = buffer->matrix_[row - 1][col];
//       buffer->matrix_[row][k] =
//           (row_n / prew_row_n) * buffer->matrix_[row - 1][k] +
//           buffer->matrix_[row][k];
//     }
//   }
//   buffer->matrix_[row][col] = 0;
// }

// void Matrix::scan_column_to_find_nonzero_num(Matrix* buffer, const int row,
//                                              const int col, bool*
//                                              is_det_zero) {
//   bool found = false;

//   for (int i = buffer->rows_ - 1; !found && i >= 0; i--) {
//     if (fabs(buffer->matrix_[i][col]) >= kAccuracy) {
//       summ_rows(buffer, i, row);
//       found = true;
//     } else if (i == 0) {
//       *is_det_zero = true;
//     }
//   }
// }

// void Matrix::summ_rows(Matrix* buffer, const int row_num, const int
// row_zero)
// {
//   for (int i = 0; i < buffer->cols_; ++i) {
//     buffer->matrix_[row_zero][i] += buffer->matrix_[row_num][i];
//   }
// }
// template <arithmetic Type>
// Type Matrix<Type>::algebraic_addition(Matrix<Type>* initial_matrix, size_t
// row,
//                                       size_t col) {
//   Type returnable = 0.0;
//   Matrix<Type> minor(initial_matrix->rows_ - 1, initial_matrix->cols_ - 1);

//   make_matrix_minor(initial_matrix, row, col, &minor);
//   returnable = minor.Determinant();

//   return returnable;
// }

// template <arithmetic Type>
// void Matrix<Type>::make_matrix_minor(Matrix<Type>* initial_matrix, size_t
// row,
//                                      size_t col, Matrix<Type>* minor) {
//   size_t i = 0, j = 0;

//   for (size_t im = 0; im < minor->rows_; ++im) {
//     for (size_t jm = 0; jm < minor->rows_; ++jm) {
//       if (i == row) ++i;
//       if (j == col) ++j;
//       minor->matrix_[im][jm] = initial_matrix->matrix_[i][j];
//       ++i;
//     }
//     i = 0;
//     ++j;
//   }
// }

template <arithmetic Type>
void Matrix<Type>::IsInputFileOpened(const ifstream& file) {
  if (!file.is_open()) {
    throw invalid_argument("File cuold not be opened.");
  }
}

template <arithmetic Type>
void Matrix<Type>::IsOutputFileOpened(const ofstream& file) {
  if (!file.is_open()) {
    throw invalid_argument("File could not be opened.");
  }
}

template <arithmetic Type>
void Matrix<Type>::ReadMatrixSize(ifstream& file) {
  Str line;
  getline(file, line, '\n');
  int rows = 0, cols = 0;
  sscanf(line.data(), "%d %d", &rows, &cols);

  if (rows < 1 || cols < 1) {
    file.close();
    throw invalid_argument("Incorrect matrix size");
  }
  set_rows(rows);
  set_cols(cols);
}

template <arithmetic Type>
void Matrix<Type>::ReadMatrix(ifstream& file) {
  Str line;
  size_t row = 0;
  size_t rows = this->rows();
  while (getline(file, line, '\n') && row < rows) {
    ReadLineToMatrixRow(line, row);
    ++row;
  }
}

template <arithmetic Type>
void Matrix<Type>::ReadLineToMatrixRow(const Str& line, size_t row) {
  size_t col = 0;
  for (size_t i = 0; i < line.size(); ++i) {
    const char* number = &(line.data())[i];
    this->operator()(row, col) = atof(number);
    ++col;
    ShiftToNextNumber(line, &i);
  }
}

template <arithmetic Type>
void Matrix<Type>::ShiftToNextNumber(const Str& line, size_t* i) {
  while (IsNumberChar(line.data()[*i]) && *i < line.size()) {
    ++(*i);
  }
  while (!IsNumberChar(line.data()[*i]) && *i < line.size()) {
    ++(*i);
  }
  --(*i);
}

template <arithmetic Type>
bool Matrix<Type>::IsNumberChar(char sym) {
  return isdigit(sym) || sym == '.' || sym == '-' || sym == '+' || sym == 'e';
}

template <arithmetic Type>
void Matrix<Type>::WriteMatrixSize(ofstream& file) {
  file << rows() << " " << cols() << "\n";
}

template <arithmetic Type>
void Matrix<Type>::WriteMatrix(ofstream& file) {
  for (int i = 0; i < rows(); ++i) {
    for (int j = 0; j < cols(); ++j) {
      if (this->operator()(i, j) == 0) {
        this->operator()(i, j) = 0;
      }
      file << this->operator()(i, j) << " ";
    }
    file << "\n";
  }
}

}  // namespace hhullen
