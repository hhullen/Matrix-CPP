# Matrix - simple matrix operations library in C++ language

### Matrix class structure

```c++
class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  void Load(const string& file_path);
  void Save(const string& file_path);
  bool IsEqual(const Matrix& other);
  void Summarize(const Matrix& other);
  void Substract(const Matrix& other);
  void MultiplyNumber(const double num);
  void Multiply(const Matrix& other);
  void MuliplyRowNumber(const int row, const double num);
  void HadamardProduct(const Matrix& other);
  Matrix Transpose();
  Matrix CelculateComplements();
  double Determinant();
  Matrix Inverse();
  double get_element(int i, int j);
  void set_element(int i, int j, double value);
  int get_rows();
  int get_cols();
  void set_rows(int new_val);
  void set_cols(int new_val);

  bool operator==(const Matrix& other);
  Matrix& operator=(const Matrix& other);
  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator+=(const Matrix& other);
  Matrix operator-=(const Matrix& other);
  Matrix operator*=(const Matrix& other);
  double operator()(int i, int j) const;
  double operator()(int i, int j);
  ...
};
```

### How to use
- You can make libraty using command `make matrix.a` from `src` directory and then include it to compilation command as `-L <path_to_libmatrix.a> -lmatrix` (example for g++ compiler)
- Possibly to use `matrix.h` and `matrix.cc` source files as alternative
