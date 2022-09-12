# s21_matrix - simple matrix operations library in C++ language

### Matrix class structure

```c++
class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  bool eq_matrix(const S21Matrix& other);
  void sum_matrix(const S21Matrix& other);
  void sub_matrix(const S21Matrix& other);
  void mul_number(const double num);
  void mul_matrix(const S21Matrix& other);
  S21Matrix transpose();
  S21Matrix calc_complements();
  double determinant();
  S21Matrix inverse_matrix();
  double get_element(int i, int j);
  void set_element(int i, int j, double value);
  int get_rows();
  int get_cols();
  void set_rows(int new_val);
  void set_cols(int new_val);

  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  double operator()(int i, int j);

 private:
  int rows_, cols_;
  double** matrix_;

  void init_matrix(bool fill);
  void copy_data_other_to_this_matrix(double** other_matrix);
  void copy_data_this_to_other_matrix(double** other_matrix);
  void calculate_multiplied_matrix_element(const S21Matrix& other, int i, int j,
                                           double* res);
  void fill_with_zeros(int current_row);
  double calculate_2d_determinant();
  double calculate_3d_determinant();
  double calculate_Gauss_determinant();
  double multiply_diagonal(S21Matrix* buffer);
  void process_the_row(S21Matrix* buffer, int row, int col, bool* is_det_zero);
  void scan_column_to_find_nonzero_num(S21Matrix* buffer, const int row,
                                       const int col, bool* is_det_zero);
  void summ_rows(S21Matrix* buffer, const int row_num, const int row_zero);
  double algebraic_addition(S21Matrix* initial_matrix, int row, int col);
  void make_matrix_minor(S21Matrix* initial_matrix, int row, int col,
                         S21Matrix* minor);
};
```
