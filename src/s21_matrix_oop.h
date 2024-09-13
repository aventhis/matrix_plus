// s21_matrix_oop.h
#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <stdexcept>  // для подключения std::invalid_argument
#include <utility>
using namespace std;

#define EPS 1e-7

class S21Matrix {
 private:
  // Attributes
  int rows_ = 0, cols_ = 0;  // Rows and columns
  double** matrix_ =
      nullptr;  // Pointer to the memory where the matrix is allocated

 public:
  // Constructors
  S21Matrix();
  // Параметризированный конструктор с количеством строк и столбцов.
  S21Matrix(int rows, int cols);
  // Конструктор копирования.
  S21Matrix(const S21Matrix& other);
  // Конструктор переноса.
  S21Matrix(S21Matrix&& other);

  // Destructor
  ~S21Matrix();

  // Accessors
  int GetRows() const;
  int GetCols() const;

  // Mutators
  void SetRows(int rows);
  void SetCols(int cols);

  // Other methods
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // void PrintMatrix() const;
  // void GetPointerMatrix() const;
  // void FillMatrix();

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double num) const;
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);
  double& operator()(int i, int j);

  void initMatrix(int rows, int cols);
  void copyMatrix(const S21Matrix& other);
  void deleteMatrix();
};

#endif  // S21_MATRIX_OOP_H