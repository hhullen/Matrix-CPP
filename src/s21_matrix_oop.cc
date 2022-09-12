#include "s21_matrix_oop.h"

/*
  Public functions
*/
/**
 * @brief Construct a new S21Matrix::S21Matrix object
 *
 */
S21Matrix::S21Matrix() : rows_(4), cols_(4) { init_matrix(FILL_WITH_ZERO); }

/**
 * @brief Construct a new S21Matrix::S21Matrix object
 *
 * @param rows int type
 * @param cols int type
 */
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 && cols <= 0) {
    throw std::invalid_argument("Creation matrix with 0x0 size or less");
  }

  rows_ = rows;
  cols_ = cols;
  init_matrix(FILL_WITH_ZERO);
}

/**
 * @brief Construct a new S21Matrix::S21Matrix object
 *
 * @param other const S21Matrix& type
 */
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  init_matrix(NO_FILL);
  copy_data_other_to_this_matrix(other.matrix_);
}

/**
 * @brief Construct a new S21Matrix::S21Matrix object
 *
 * @param other S21Matrix&& type
 */
S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

/**
 * @brief Destroy the S21Matrix::S21Matrix object
 *
 */
S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (rows_ -= 1; rows_ >= 0; rows_ -= 1) {
      if (matrix_[rows_]) {
        delete[] matrix_[rows_];
        matrix_[rows_] = nullptr;
      }
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  cols_ = 0;
  rows_ = 0;
}

/**
 * @brief Compare matrix of this object with other
 *
 * @param other const S21Matrix& type
 * @return true
 * @return false
 */
bool S21Matrix::eq_matrix(const S21Matrix& other) {
  bool is_equal = true;

  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; is_equal && i < rows_; i += 1) {
      for (int j = 0; is_equal && j < cols_; j += 1) {
        is_equal = fabs(matrix_[i][j] - other.matrix_[i][j]) < ACCURACY;
      }
    }
  } else {
    is_equal = false;
  }

  return is_equal;
}

/**
 * @brief Summs this matrix with other
 *
 * @param other const S21Matrix& type
 */
void S21Matrix::sum_matrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Summation the matrix that is not square");
  }

  for (int i = 0; i < rows_; i += 1) {
    for (int j = 0; j < cols_; j += 1) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

/**
 * @brief Substracts this matrix with other
 *
 * @param other const S21Matrix& type
 */
void S21Matrix::sub_matrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Substraction the matrix that is not square");
  }

  for (int i = 0; i < rows_; i += 1) {
    for (int j = 0; j < cols_; j += 1) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

/**
 * @brief Multiplies every matrix element by "num" value
 *
 * @param num const double type
 */
void S21Matrix::mul_number(const double num) {
  for (int i = 0; i < rows_; i += 1) {
    for (int j = 0; j < cols_; j += 1) {
      matrix_[i][j] *= num;
    }
  }
}

/**
 * @brief Multiplies matrix of this object with other matrix with sizes m*k and
 * k*m
 *
 * @param other const S21Matrix& type
 */
void S21Matrix::mul_matrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Multiplication matrix with different cols and rows");
  }
  double* buffer_row = nullptr;

  for (int i = 0; i < rows_; i += 1) {
    buffer_row = new double[other.cols_];
    for (int j = 0; j < other.cols_; j += 1) {
      buffer_row[j] = 0;
      calculate_multiplied_matrix_element(other, i, j, &buffer_row[j]);
    }
    delete[] matrix_[i];
    matrix_[i] = buffer_row;
    buffer_row = nullptr;
  }
  cols_ = other.cols_;
}

/**
 * @brief Transposes matrix
 *
 * @return S21Matrix
 */
S21Matrix S21Matrix::transpose() {
  S21Matrix returnable(cols_, rows_);

  for (int i = 0; i < returnable.rows_; i += 1) {
    for (int j = 0; j < returnable.cols_; j += 1) {
      returnable.matrix_[i][j] = matrix_[j][i];
    }
  }

  return returnable;
}

/**
 * @brief Calculates algebraic additions matrix of this object
 *
 * @return S21Matrix
 */
S21Matrix S21Matrix::calc_complements() {
  if (cols_ != rows_) {
    throw std::invalid_argument(
        "Calculation complements of matrices with different cols and rows");
  }
  S21Matrix returnable(cols_, rows_);

  if (cols_ != 1 && rows_ != 1) {
    for (int i = 0; i < returnable.rows_; i += 1) {
      for (int j = 0; j < returnable.cols_; j += 1) {
        returnable.matrix_[i][j] =
            algebraic_addition(this, i, j) * (-1 + !((i + j) % 2) * 2);
      }
    }
  } else {
    returnable.matrix_[0][0] = 1;
  }

  return returnable;
}

/**
 * @brief Calculates determinant
 *
 * @return double
 */
double S21Matrix::determinant() {
  double returnable = NAN;

  if (cols_ != rows_) {
    throw std::invalid_argument(
        "Calculation determinant of matrix with different cols and rows");
  }

  if (rows_ == 1) {
    returnable = matrix_[0][0];
  } else if (rows_ == 2) {
    returnable = calculate_2d_determinant();
  } else if (rows_ == 3) {
    returnable = calculate_3d_determinant();
  } else {
    returnable = calculate_Gauss_determinant();
  }

  return returnable;
}

/**
 * @brief Calculates inverse matrix
 *
 * @return S21Matrix
 */
S21Matrix S21Matrix::inverse_matrix() {
  double det = this->determinant();

  if (fabs(det) < ACCURACY) {
    throw std::invalid_argument(
        "Inversion of matrix with determinant equals 0");
  }
  S21Matrix returnable(*this);

  returnable = returnable.calc_complements();
  returnable = returnable.transpose();
  returnable.mul_number(1 / det);

  return returnable;
}

/**
 * @brief Returns matrix element from i*j position
 *
 * @param i int type
 * @param j int type
 * @return double
 */
double S21Matrix::get_element(int i, int j) {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::out_of_range("Getting element that is out of matrix range");
  }

  return matrix_[i][j];
}

/**
 * @brief Sets "value" to matrix element in i*j position
 *
 * @param i int type
 * @param j int type
 * @param value double type
 */
void S21Matrix::set_element(int i, int j, double value) {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::out_of_range("Setting element that is out of matrix range");
  }

  matrix_[i][j] = value;
}

/**
 * @brief Returns amount of matrix rows
 *
 * @return int
 */
int S21Matrix::get_rows() { return rows_; }

/**
 * @brief Returns amount of matrix columns
 *
 * @return int
 */
int S21Matrix::get_cols() { return cols_; }

/**
 * @brief Sets new amount of matrix rows
 *
 * @param new_val int type
 */
void S21Matrix::set_rows(int new_val) {
  if (new_val <= 0) {
    throw std::invalid_argument(
        "Setting rows amount that is equal or less than 0");
  }
  double** buffer = new double*[new_val];

  if (new_val < rows_) {
    rows_ = new_val;
  }
  for (int i = 0; i < rows_; i += 1) {
    buffer[i] = matrix_[i];
  }
  delete[] this->matrix_;
  this->matrix_ = buffer;
  buffer = nullptr;

  for (int i = rows_; i < new_val; i += 1) {
    this->matrix_[i] = new double[cols_];
    fill_with_zeros(i);
  }
  rows_ = new_val;
}

/**
 * @brief Sets new amount of matrix cols
 *
 * @param new_val int type
 */
void S21Matrix::set_cols(int new_val) {
  if (new_val <= 0) {
    throw std::invalid_argument(
        "Setting cols amount that is equal or less than 0");
  }
  double* buffer = nullptr;

  if (new_val < cols_) {
    cols_ = new_val;
  }
  for (int i = 0; i < rows_; i += 1) {
    buffer = new double[new_val];
    for (int j = 0; j < cols_; j += 1) {
      buffer[j] = matrix_[i][j];
    }
    for (int j = cols_; j < new_val; j += 1) {
      buffer[j] = 0;
    }
    delete[] matrix_[i];
    matrix_[i] = buffer;
    buffer = nullptr;
  }
  cols_ = new_val;
}

/*
  Operators
*/
bool S21Matrix::operator==(const S21Matrix& other) {
  return this->eq_matrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  this->~S21Matrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  init_matrix(NO_FILL);
  copy_data_other_to_this_matrix(other.matrix_);

  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix returnable(*this);
  returnable.sum_matrix(other);

  return returnable;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix returnable(*this);
  returnable.sub_matrix(other);

  return returnable;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix returnable(*this);
  returnable.mul_matrix(other);

  return returnable;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  this->sum_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  this->sub_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  this->mul_matrix(other);
  return *this;
}

double S21Matrix::operator()(int i, int j) {
  if ((i < 0 || i > rows_) || j < 0 || j > cols_) {
    throw std::out_of_range("Setting element that is out of matrix range");
  }

  return matrix_[i][j];
}

/*
  Private functions
*/
void S21Matrix::init_matrix(bool fill) {
  matrix_ = new double*[rows_];
  if (matrix_) {
    for (int i = 0; i < rows_; i += 1) {
      matrix_[i] = new double[cols_];
      if (fill) fill_with_zeros(i);
    }
  }
}

void S21Matrix::copy_data_other_to_this_matrix(double** other_matrix) {
  for (int i = 0; i < rows_; i += 1) {
    for (int j = 0; j < cols_; j += 1) {
      matrix_[i][j] = other_matrix[i][j];
    }
  }
}

void S21Matrix::copy_data_this_to_other_matrix(double** other_matrix) {
  for (int i = 0; i < rows_; i += 1) {
    for (int j = 0; j < cols_; j += 1) {
      other_matrix[i][j] = matrix_[i][j];
    }
  }
}

void S21Matrix::calculate_multiplied_matrix_element(const S21Matrix& other,
                                                    int i, int j, double* res) {
  for (int k = 0; k < cols_; k += 1) {
    *res += matrix_[i][k] * other.matrix_[k][j];
  }
}

void S21Matrix::fill_with_zeros(int current_row) {
  for (int i = 0; i < cols_; i += 1) {
    matrix_[current_row][i] = 0;
  }
}

double S21Matrix::calculate_2d_determinant() {
  return matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
}

double S21Matrix::calculate_3d_determinant() {
  double returnable = 0.0;

  returnable += matrix_[0][0] *
                (matrix_[1][1] * matrix_[2][2] - matrix_[2][1] * matrix_[1][2]);
  returnable -= matrix_[0][1] *
                (matrix_[1][0] * matrix_[2][2] - matrix_[2][0] * matrix_[1][2]);
  returnable += matrix_[0][2] *
                (matrix_[1][0] * matrix_[2][1] - matrix_[2][0] * matrix_[1][1]);

  return returnable;
}

double S21Matrix::calculate_Gauss_determinant() {
  S21Matrix buffer(cols_, rows_);
  double returnable = 0.0;
  int row_constrain = 0;
  bool is_det_zero = false;

  copy_data_this_to_other_matrix(buffer.matrix_);
  for (int i = 0; !is_det_zero && i < buffer.cols_; i += 1) {
    for (int j = buffer.rows_ - 1; !is_det_zero && j > row_constrain; j -= 1) {
      process_the_row(&buffer, j, i, &is_det_zero);
    }
    row_constrain += 1;
  }
  if (!is_det_zero) {
    returnable = multiply_diagonal(&buffer);
  } else {
    returnable = 0.0;
  }

  return returnable;
}

double S21Matrix::multiply_diagonal(S21Matrix* buffer) {
  double returnable = 1.0;

  for (int i = 0; i < buffer->cols_; i += 1) {
    returnable *= buffer->matrix_[i][i];
  }

  return returnable;
}

void S21Matrix::process_the_row(S21Matrix* buffer, int row, int col,
                                bool* is_det_zero) {
  double prew_row_n = buffer->matrix_[row - 1][col];
  double row_n = buffer->matrix_[row][col] * -1;

  for (int k = col; k < buffer->cols_ && !*is_det_zero; k += 1) {
    if (prew_row_n != 0) {
      buffer->matrix_[row][k] =
          (row_n / prew_row_n) * buffer->matrix_[row - 1][k] +
          buffer->matrix_[row][k];
    } else {
      scan_column_to_find_nonzero_num(buffer, row - 1, k, is_det_zero);
      prew_row_n = buffer->matrix_[row - 1][col];
      buffer->matrix_[row][k] =
          (row_n / prew_row_n) * buffer->matrix_[row - 1][k] +
          buffer->matrix_[row][k];
    }
  }
  buffer->matrix_[row][col] = 0;
}

void S21Matrix::scan_column_to_find_nonzero_num(S21Matrix* buffer,
                                                const int row, const int col,
                                                bool* is_det_zero) {
  bool found = false;

  for (int i = buffer->rows_ - 1; !found && i >= 0; i--) {
    if (fabs(buffer->matrix_[i][col]) >= ACCURACY) {
      summ_rows(buffer, i, row);
      found = true;
    } else if (i == 0) {
      *is_det_zero = true;
    }
  }
}

void S21Matrix::summ_rows(S21Matrix* buffer, const int row_num,
                          const int row_zero) {
  for (int i = 0; i < buffer->cols_; i += 1) {
    buffer->matrix_[row_zero][i] += buffer->matrix_[row_num][i];
  }
}

double S21Matrix::algebraic_addition(S21Matrix* initial_matrix, int row,
                                     int col) {
  double returnable = 0.0;
  S21Matrix minor(initial_matrix->rows_ - 1, initial_matrix->cols_ - 1);

  make_matrix_minor(initial_matrix, row, col, &minor);
  returnable = minor.determinant();

  return returnable;
}

void S21Matrix::make_matrix_minor(S21Matrix* initial_matrix, int row, int col,
                                  S21Matrix* minor) {
  int i = 0, j = 0;

  for (int im = 0; im < minor->rows_; im += 1) {
    for (int jm = 0; jm < minor->rows_; jm += 1) {
      if (i == row) i += 1;
      if (j == col) j += 1;
      minor->matrix_[im][jm] = initial_matrix->matrix_[i][j];
      i += 1;
    }
    i = 0;
    j += 1;
  }
}
