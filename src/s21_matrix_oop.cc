// s21_matrix_oop.cpp

#include "s21_matrix_oop.h"

// Default constructor
S21Matrix::S21Matrix() : rows_(1), cols_(1) { initMatrix(rows_, cols_); }

// Параметризированный конструктор
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  initMatrix(rows_, cols_);
}

// Конструктор копирования.
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  initMatrix(rows_, cols_);
  copyMatrix(other);
}

// Конструктор переноса.
S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// Destructor
S21Matrix::~S21Matrix() { deleteMatrix(); }

void S21Matrix::initMatrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw invalid_argument("Rows and cols should be > 0");
  }
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols]{};
  }
}

void S21Matrix::copyMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::deleteMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i]) delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

// Accessors
int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

// Mutators
void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw invalid_argument("Rows should be > 0");
  }
  if (rows_ != rows) {
    int minRows = min(rows, rows_);
    S21Matrix temp(rows, cols_);
    for (int i = 0; i < minRows; i++) {
      for (int j = 0; j < cols_; j++) temp.matrix_[i][j] = this->matrix_[i][j];
    }
    deleteMatrix();
    *this = temp;
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw invalid_argument("Cols should be > 0");
  }
  if (cols_ != cols) {
    int minCols = min(cols, cols_);
    S21Matrix temp(rows_, cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < minCols; j++)
        temp.matrix_[i][j] = this->matrix_[i][j];
    }
    // Освобождаем ресурсы текущей матрицы
    deleteMatrix();
    *this = temp;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool res = true;

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  }

  for (int i = 0; i < rows_ && res == true; i++) {
    for (int j = 0; j < cols_ && res == true; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
        res = false;
      } else
        res = true;
    }
  }

  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw logic_error("Wrong matrix size");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw logic_error("Wrong matrix size");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw logic_error("cols_ first matrix != rows_ second matrix");
  }

  S21Matrix Temp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double sum = 0;
      for (int k = 0; k < other.rows_; k++) {
        sum = sum + matrix_[i][k] * other.matrix_[k][j];
      }
      Temp.matrix_[i][j] = sum;
    }
  }
  swap(Temp.matrix_, this->matrix_);
  swap(Temp.rows_, this->rows_);
  swap(Temp.cols_, this->cols_);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix Temp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      Temp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return Temp;
}

double S21Matrix::Determinant() {
  double res = 0;

  int sign = 1;

  if (cols_ != rows_) {
    throw logic_error("The matrix is ​​not square");
  }

  if (cols_ == 1) {
    res = matrix_[0][0];
  } else if (cols_ == 2) {
    res = matrix_[0][0] * matrix_[1][1] - (matrix_[0][1] * matrix_[1][0]);
  } else {
    for (int i = 0; i < rows_; i++) {
      S21Matrix Temp(rows_ - 1, cols_ - 1);
      double temp = 0;
      int l = 0;

      for (int m = 0; m < cols_; m++) {
        int k = 0;
        for (int n = 0; n < cols_; n++) {
          if (n != i && m != 0) {
            Temp.matrix_[l][k] = matrix_[m][n];
            k++;
          }
        }
        if (k) l++;
      }

      temp = Temp.Determinant();
      res += matrix_[0][i] * pow(-1, sign + 1) * temp;

      temp = 0;
      sign++;
    }
  }

  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) {
    throw logic_error("The matrix is ​​not square");
  }

  S21Matrix Result(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix Temp(rows_ - 1, cols_ - 1);

      int l = 0;

      for (int m = 0; m < cols_; m++) {
        int k = 0;
        for (int n = 0; n < cols_; n++) {
          if (n != j && m != i) {
            Temp.matrix_[l][k] = matrix_[m][n];
            k++;
          }
        }
        if (k) l++;
      }

      double temp = Temp.Determinant();

      Result.matrix_[i][j] = temp * pow(-1, i + j);
    }
  }

  return Result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (cols_ != rows_) {
    throw logic_error("The matrix is ​​not square");
  }

  double determinant = Determinant();

  if (fabs(determinant) < EPS) {
    throw logic_error("Determinant value can't be equal to 0");
  }

  S21Matrix Temp = CalcComplements();
  S21Matrix Temp2 = Temp.Transpose();
  Temp2.MulNumber(1.0 / determinant);

  return Temp2;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix ResultMatrix(*this);
  ResultMatrix.SumMatrix(other);
  return ResultMatrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix ResultMatrix(*this);
  ResultMatrix.SubMatrix(other);
  return ResultMatrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix ResultMatrix(*this);
  ResultMatrix.MulMatrix(other);
  return ResultMatrix;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix ResultMatrix(*this);
  ResultMatrix.MulNumber(num);
  ;
  return ResultMatrix;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  deleteMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  initMatrix(rows_, cols_);
  copyMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    // Нет необходимости в deleteMatrix() для rvalue ссылки
    swap(other.matrix_, this->matrix_);
    swap(other.rows_, this->rows_);
    swap(other.cols_, this->cols_);
  }

  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_) {
    throw out_of_range("Index out of bounds");
  }
  return matrix_[i][j];
}

// void S21Matrix::PrintMatrix() const {
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//       cout << matrix_[i][j] << "\t";
//     }
//     cout << endl;
//   }
// }