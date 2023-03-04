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

  bool IsEqual(const Matrix& other);
  void Summarize(const Matrix& other);
  void Substract(const Matrix& other);
  void MultiplyNumber(const double num);
  void Multiply(const Matrix& other);
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
  double operator()(int i, int j);
};
```
