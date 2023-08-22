# Matrix - simple matrix operations library in C++ language
С++20

### Matrix class structure

```c++
template <arithmetic Type>
class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  int rows() const;
  int cols() const;
  void set_rows(int new_val);
  void set_cols(int new_val);
  void set(int i, int j, Type value);

  void SwapRows(const int row_1, const int row_2);
  void ProcessRows(const int row_1, const int row_2,
                   const std::function<void(Type&, Type&)>& lambda);
  void ProcessRow(const int row, const std::function<void(Type&)>& lambda);
  void ProcessEach(const std::function<void(Type&)>& lambda);
  void HadamardProduct(const Matrix<Type>& other);
  Matrix<Type> Transpose() const;

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
  ...
};
```

```c++
// matrix file format: (first line is size, next is matrix)
5 5
1 3 4 5 6
2 4 6 7 8
4 5 6 7 8
9 0 8 7 6
5 5 6 7 8.95
```

### How to use
- You can make libraty using command `make matrix.a` from `src` directory and then include it to compilation command as `-L <path_to_libmatrix_dir.a> -lmatrix` (example for g++ compiler)
- Possibly to use `matrix.h` and `matrix.cc` source files as alternative
