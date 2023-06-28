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
  init_matrix(true);
}

/**
 * @brief Construct a new Matrix::Matrix object
 *
 * @param rows int type
 * @param cols int type
 */
template <arithmetic Type>
Matrix<Type>::Matrix(int rows, int cols) {
  if (rows < 1 && cols < 1) {
    throw invalid_argument("Creation matrix with less than 1x1 size");
  }

  rows_ = rows;
  cols_ = cols;
  init_matrix(true);
}

/**
 * @brief Construct a new Matrix::Matrix object
 *
 * @param other const Matrix& type
 */
template <arithmetic Type>
Matrix<Type>::Matrix(const Matrix<Type>& other) {
  if (other != *this) {
    *this = other;
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
  matrix_.swap(other.matrix_);

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
 * @param row_1 const int index of first row to swap
 * @param row_2 const int index of another row to be swaped with first
 */
template <arithmetic Type>
void Matrix<Type>::SwapRows(const int row_1, const int row_2) {
  if (row_1 < 0 || row_1 >= rows_ || row_2 < 0 || row_2 >= rows_) {
    throw out_of_range("The matrix rows indices that is out of matrix size");
  }

  matrix_[row_1].swap(matrix_[row_2]);
}

/**
 * @brief Apply lambda function to values of two rows for whole cols
 *
 * @param row_1 const int type index of first row
 * @param row_2 const int type index of secont row
 * @param lambda const std::function<void(Type&, Type&)> type lambda function
 */
template <arithmetic Type>
void Matrix<Type>::ProcessRows(
    const int row_1, const int row_2,
    const std::function<void(Type&, Type&)>& lambda) {
  if (row_1 < 0 || row_1 >= rows_ || row_2 < 0 || row_2 >= rows_) {
    throw out_of_range("Matrix rows with indices that is out of matrix size");
  }

  for (int col = 0; col < cols_; ++col) {
    lambda(matrix_[row_1][col], matrix_[row_2][col]);
  }
}

/**
 * @brief Apply lambda function to values of row
 *
 * @param row const int type index of row
 * @param lambda const std::function<void(Type&)> type lambda function
 */
template <arithmetic Type>
void Matrix<Type>::ProcessRow(const int row,
                              const std::function<void(Type&)>& lambda) {
  if (row < 0 || row >= rows_) {
    throw out_of_range("Matrix rows with indices that is out of matrix size");
  }

  for (int col = 0; col < cols_; ++col) {
    lambda(matrix_[row][col]);
  }
}

/**
 * @brief Apply lambda function to each values of matrix
 *
 * @param lambda const std::function<void(Type&)> type lambda function
 */
template <arithmetic Type>
void Matrix<Type>::ProcessEach(const std::function<void(Type&)>& lambda) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      lambda(matrix_[i][j]);
    }
  }
}

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

/**
 * @brief Sets "value" to matrix element in i*j position
 *
 * @param i int type
 * @param j int type
 * @param value double type
 */
template <arithmetic Type>
void Matrix<Type>::set(int i, int j, Type value) {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw out_of_range("Setting element that is out of matrix range");
  }

  matrix_[i][j] = value;
}

/**
 * @brief Returns amount of matrix rows
 *
 * @return int
 */
template <arithmetic Type>
int Matrix<Type>::rows() const {
  return rows_;
}

/**
 * @brief Returns amount of matrix columns
 *
 * @return int
 */
template <arithmetic Type>
int Matrix<Type>::cols() const {
  return cols_;
}

/**
 * @brief Sets new amount of matrix rows
 *
 * @param new_val int type
 */
template <arithmetic Type>
void Matrix<Type>::set_rows(int new_val) {
  if (new_val < 1) {
    throw invalid_argument("Setting rows amount that is equal or less than 0");
  }
  MatrixPtr buffer = MatrixPtr(new RowPtr[new_val]);

  if (new_val < rows_) {
    rows_ = new_val;
  }
  for (int i = 0; i < rows_; ++i) {
    buffer[i].swap(matrix_[i]);
  }
  matrix_.swap(buffer);

  for (int i = rows_; i < new_val; ++i) {
    matrix_[i] = RowPtr(new Type[cols_]);
    memset(matrix_[i].get(), 0, sizeof(Type) * static_cast<size_t>(cols_));
  }
  rows_ = new_val;
}

/**
 * @brief Sets new amount of matrix cols
 *
 * @param new_val int type
 */
template <arithmetic Type>
void Matrix<Type>::set_cols(int new_val) {
  if (new_val <= 0) {
    throw invalid_argument("Setting cols amount that is equal or less than 0");
  }
  RowPtr buffer(nullptr);

  if (new_val < cols_) {
    cols_ = new_val;
  }
  for (int i = 0; i < rows_; ++i) {
    buffer.reset(new Type[new_val]);
    for (int j = 0; j < cols_; ++j) {
      buffer[j] = matrix_[i][j];
    }
    for (int j = cols_; j < new_val; ++j) {
      buffer[j] = 0;
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
bool Matrix<Type>::operator!=(const Matrix<Type>& other) const {
  return !(*this == other);
}

template <arithmetic Type>
Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type>& other) {
  if (other != *this) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    init_matrix(false);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }

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
template <arithmetic Val>
Matrix<Type> Matrix<Type>::operator*(const Val value) const {
  Matrix returnable(*this);
  return returnable *= value;
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
      for (int k = 0; k < cols_; k += 1) {
        buffer_row[j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
    matrix_[i].swap(buffer_row);
  }
  cols_ = other.cols_;

  return *this;
}

template <arithmetic Type>
template <arithmetic Val>
Matrix<Type> Matrix<Type>::operator*=(const Val value) {
  ProcessEach([value](Type& val) { val *= value; });
  return *this;
}

template <arithmetic Type>
Type& Matrix<Type>::operator()(int i, int j) {
  if ((i < 0 || i > rows_) || j < 0 || j > cols_) {
    throw out_of_range("Setting element that is out of matrix range");
  }

  return matrix_[i][j];
}

template <arithmetic Type>
Type Matrix<Type>::operator()(int i, int j) const {
  if ((i < 0 || i > rows_) || j < 0 || j > cols_) {
    throw out_of_range("Setting element that is out of matrix range");
  }

  return matrix_[i][j];
}

/*
  Private functions
*/
template <arithmetic Type>
void Matrix<Type>::init_matrix(bool fill_with_zero) {
  matrix_ = MatrixPtr(new RowPtr[rows_]);
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = RowPtr(new Type[cols_]);
    memset(matrix_[i].get(), 0, sizeof(Type) * static_cast<size_t>(cols_));
  }
}

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
  set_rows(static_cast<int>(rows));
  set_cols(static_cast<int>(cols));
}

template <arithmetic Type>
void Matrix<Type>::ReadMatrix(ifstream& file) {
  Str line;
  int row = 0;
  int rows = this->rows();
  while (getline(file, line, '\n') && row < rows) {
    ReadLineToMatrixRow(line, row);
    ++row;
  }
}

template <arithmetic Type>
void Matrix<Type>::ReadLineToMatrixRow(const Str& line, int row) {
  int col = 0;
  for (int i = 0; i < static_cast<int>(line.size()); ++i) {
    const char* number = &(line.data())[i];
    this->operator()(row, col) = atof(number);
    ++col;
    ShiftToNextNumber(line, &i);
  }
}

template <arithmetic Type>
void Matrix<Type>::ShiftToNextNumber(const Str& line, int* i) {
  while (IsNumberChar(line.data()[*i]) && *i < static_cast<int>(line.size())) {
    ++(*i);
  }
  while (!IsNumberChar(line.data()[*i]) && *i < static_cast<int>(line.size())) {
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
