#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(EqMatrix, eq) {
  int size = 5;
  S21Matrix a(size, size), b(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = b(i, j) = j;
    }
  }
  ASSERT_EQ(a.EqMatrix(b), 1);
  ASSERT_EQ(b.EqMatrix(a), 1);
}

TEST(EqMatrix, eq2) {
  int size = 5;
  S21Matrix a(size, size), b(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = b(i, j) = i + j;
    }
  }
  ASSERT_EQ(a.EqMatrix(b), 1);
  ASSERT_EQ(b.EqMatrix(a), 1);
}

TEST(EqMatrix, eq3) {
  int size = 5;
  S21Matrix a(size, size), b(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = b(i, j) = (i + j) / 3;
    }
  }
  ASSERT_EQ(a.EqMatrix(b), 1);
  ASSERT_EQ(b.EqMatrix(a), 1);
}

TEST(EqMatrix, NotEqual) {
  int size = 5;
  S21Matrix a(size, size), b(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = i + j;
      b(i, j) = i + j + 1;
    }
  }
  ASSERT_EQ(a.EqMatrix(b), 0);
  ASSERT_EQ(b.EqMatrix(a), 0);
}

TEST(EqMatrix, PrecisionTest) {
  int size = 5;
  S21Matrix a(size, size), b(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = b(i, j) = (i + j) / 3;
    }
  }
  a(4, 3) -= 0.000002;
  ASSERT_EQ(a.EqMatrix(b), 0);
  ASSERT_EQ(b.EqMatrix(a), 0);
}

TEST(EqMatrix, DiffDimension) {
  int size = 4;
  S21Matrix a(size, size), b(size - 1, size - 1);
  ASSERT_EQ(a.EqMatrix(b), 0);
  ASSERT_EQ(b.EqMatrix(a), 0);
}

TEST(EqMatrix, EmptyMatrices) {
  int size = 9;
  S21Matrix a(size, size), b(size, size);
  ASSERT_EQ(a.EqMatrix(b), 1);
  ASSERT_EQ(b.EqMatrix(a), 1);
}

TEST(EqMatrix, Uninitialized) {
  S21Matrix a, b;
  ASSERT_EQ(a.EqMatrix(b), 1);
  ASSERT_EQ(b.EqMatrix(a), 1);
}

TEST(MulNumber, 1dMatrix) {
  S21Matrix source(1, 1);
  source(0, 0) = 3.141592;
  source.MulNumber(2.718281);
  S21Matrix expected(1, 1);
  expected(0, 0) = 8.53972984335;
  ASSERT_EQ(source.EqMatrix(expected), 1);
}

TEST(MulNumber, 3dMatrix) {
  S21Matrix source(3, 3);
  source(0, 0) = 1.3;
  source(1, 0) = 89.13;
  source(2, 0) = 1;
  source(0, 1) = 9.1;
  source(1, 1) = 7;
  source(2, 1) = 1389;
  source(0, 2) = 8.123;
  source(1, 2) = 0;
  source(2, 2) = 0.0004;
  source.MulNumber(1.234567);
  S21Matrix expected(3, 3);
  expected(0, 0) = 1.3 * 1.234567;
  expected(1, 0) = 89.13 * 1.234567;
  expected(2, 0) = 1 * 1.234567;
  expected(0, 1) = 9.1 * 1.234567;
  expected(1, 1) = 7 * 1.234567;
  expected(2, 1) = 1389 * 1.234567;
  expected(0, 2) = 8.123 * 1.234567;
  expected(1, 2) = 0 * 1.234567;
  expected(2, 2) = 0.0004 * 1.234567;
  ASSERT_EQ(source.EqMatrix(expected), 1);
}

TEST(Constructor, Constructor_null) {
  S21Matrix Matrix;
  EXPECT_EQ(Matrix.GetRows(), 1);
  EXPECT_EQ(Matrix.GetCols(), 1);
}

TEST(Constructor, Constructor_1) {
  int rows = 3;
  int columns = 4;
  S21Matrix Matrix(rows, columns);
  EXPECT_EQ(Matrix.GetCols(), columns);
  EXPECT_EQ(Matrix.GetRows(), rows);
}

TEST(Constructor, Constructor_Copy) {
  int rows = 3;
  int columns = 4;
  S21Matrix sample(rows, columns);
  S21Matrix expect(sample);
  EXPECT_EQ(sample.EqMatrix(expect), 1);
}

TEST(Constructors, Copy) {
  S21Matrix source(3, 3);
  source(0, 0) = 99;
  source(2, 2) = -99;
  source(1, 1) = 13;
  S21Matrix copy(source);
  ASSERT_EQ(source.EqMatrix(copy), 1);
}

TEST(Complements, 1) {
  S21Matrix source(3, 3);
  S21Matrix expected(3, 3);
  source(0, 0) = 1;
  source(0, 1) = 2;
  source(0, 2) = 3;
  source(1, 0) = 0;
  source(1, 1) = 4;
  source(1, 2) = 2;
  source(2, 0) = 5;
  source(2, 1) = 2;
  source(2, 2) = 1;
  expected(0, 0) = 0;
  expected(0, 1) = 10;
  expected(0, 2) = -20;
  expected(1, 0) = 4;
  expected(1, 1) = -14;
  expected(1, 2) = 8;
  expected(2, 0) = -8;
  expected(2, 1) = -2;
  expected(2, 2) = 4;
  S21Matrix result = source.CalcComplements();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Complements, 2) {
  S21Matrix source(3, 3);
  S21Matrix expected(3, 3);
  source(0, 0) = 1.0;
  source(0, 1) = 2.0;
  source(0, 2) = 3.0;
  source(1, 0) = 0.0;
  source(1, 1) = 4.0;
  source(1, 2) = 2.0;
  source(2, 0) = 5.0;
  source(2, 1) = 2.0;
  source(2, 2) = 1.0;
  expected(0, 0) = 0.0;
  expected(0, 1) = 10.0;
  expected(0, 2) = -20.0;
  expected(1, 0) = 4.0;
  expected(1, 1) = -14.0;
  expected(1, 2) = 8.0;
  expected(2, 0) = -8.0;
  expected(2, 1) = -2.0;
  expected(2, 2) = 4.0;
  S21Matrix result = source.CalcComplements();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Complements, 2d) {
  S21Matrix source(2, 2), expected(2, 2);
  source(0, 0) = 3;
  source(0, 1) = 1;
  source(1, 0) = 20;
  source(1, 1) = -2;
  expected(0, 0) = -2;
  expected(0, 1) = -20;
  expected(1, 0) = -1;
  expected(1, 1) = 3;
  S21Matrix result = source.CalcComplements();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Determinant, J) {
  int size = 5;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = j;
    }
  }
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, 0);
}

TEST(Determinant, iplj) {
  int size = 5;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = i + j;
    }
  }
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, 0);
}

TEST(Determinant, 3) {
  int size = 3;
  S21Matrix source(size, size);
  source(0, 0) = 2;
  source(0, 1) = 3;
  source(0, 2) = 1;
  source(1, 0) = 7;
  source(1, 1) = 4;
  source(1, 2) = 1;
  source(2, 0) = 9;
  source(2, 1) = -2;
  source(2, 2) = 1;
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, -32);
}

TEST(Determinant, 2) {
  int size = 2;
  S21Matrix source(size, size);
  source(0, 0) = -5;
  source(0, 1) = -4;
  source(1, 0) = -2;
  source(1, 1) = -3;
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, 7);
}

TEST(Determinant, 8) {
  int size = 8;
  S21Matrix source(size, size);
  source(0, 0) = 2;
  source(0, 1) = 8;
  source(0, 2) = 7;
  source(0, 3) = 4;
  source(0, 4) = 1;
  source(0, 5) = 8;
  source(0, 6) = 3;
  source(0, 7) = 9;
  source(1, 0) = 4;
  source(1, 1) = 2;
  source(1, 2) = 6;
  source(1, 3) = 2;
  source(1, 4) = 2;
  source(1, 5) = 1;
  source(1, 6) = 5;
  source(1, 7) = 8;
  source(2, 0) = 8;
  source(2, 1) = 6;
  source(2, 2) = 7;
  source(2, 3) = 7;
  source(2, 4) = 3;
  source(2, 5) = 4;
  source(2, 6) = 4;
  source(2, 7) = 1;
  source(3, 0) = 1;
  source(3, 1) = 7;
  source(3, 2) = 0;
  source(3, 3) = 4;
  source(3, 4) = 4;
  source(3, 5) = 3;
  source(3, 6) = 0;
  source(3, 7) = 5;
  source(4, 0) = 5;
  source(4, 1) = 7;
  source(4, 2) = 5;
  source(4, 3) = 6;
  source(4, 4) = 8;
  source(4, 5) = 3;
  source(4, 6) = 1;
  source(4, 7) = 9;
  source(5, 0) = 3;
  source(5, 1) = 7;
  source(5, 2) = 8;
  source(5, 3) = 0;
  source(5, 4) = 5;
  source(5, 5) = 7;
  source(5, 6) = 0;
  source(5, 7) = 2;
  source(6, 0) = 5;
  source(6, 1) = 8;
  source(6, 2) = 3;
  source(6, 3) = 5;
  source(6, 4) = 9;
  source(6, 5) = 1;
  source(6, 6) = 2;
  source(6, 7) = 0;
  source(7, 0) = 7;
  source(7, 1) = 8;
  source(7, 2) = 7;
  source(7, 3) = 4;
  source(7, 4) = 7;
  source(7, 5) = 9;
  source(7, 6) = 1;
  source(7, 7) = 5;
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, -616458);
}

TEST(Determinant, 1) {
  S21Matrix source(1, 1);
  source(0, 0) = 9;
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, 9);
}

TEST(Determinant, AllZero) {
  S21Matrix source(9, 9);
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, 0);
}

TEST(Determinant, 2dMatrix) {
  S21Matrix source(2, 2);
  source(0, 0) = 73;
  source(0, 1) = 16;
  source(1, 0) = 0;
  source(1, 1) = -4;
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, -292);
}

TEST(Mutators, Setter1) {
  int size = 9;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = i + j;
    }
  }
  size--;
  source.SetRows(size);
  ASSERT_EQ(source.GetRows(), size);
}

TEST(Mutators, Setter2) {
  int size = 9;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = i + j;
    }
  }
  size++;
  source.SetRows(size);
  ASSERT_EQ(source.GetRows(), size);
  ASSERT_DOUBLE_EQ(source(size - 1, size - 2), 0);
}

TEST(Mutators, Setter3) {
  int size = 9;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = i + j;
    }
  }
  size--;
  source.SetCols(size);
  ASSERT_EQ(source.GetCols(), size);
}

TEST(Mutators, Setter4) {
  int size = 9;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = i + j;
    }
  }
  size++;
  source.SetCols(size);
  ASSERT_EQ(source.GetCols(), size);
  ASSERT_DOUBLE_EQ(source(size - 2, size - 1), 0);
}

TEST(Overload, Sum) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  S21Matrix result = source1 + source2;

  expected(0, 0) = 352.412 + 352.412;
  expected(1, 0) = 1 + 1;
  expected(2, 0) = 1;
  expected(0, 1) = -1234.8234 + 1234.8234;
  expected(1, 1) = 0.00001 + 0.00001;
  expected(2, 1) = 352.412 + 123456789;
  expected(0, 2) = -0.00001 + 1234.8234;
  expected(1, 2) = 352.412 + 0.412;
  expected(2, 2) = 9 + 9;

  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Overload, Sub) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  S21Matrix result = source1 - source2;
  expected(0, 0) = 352.412 - 352.412;
  expected(1, 0) = 0;
  expected(2, 0) = 1;
  expected(0, 1) = 1234.8234 - -1234.8234;
  expected(1, 1) = 0.00001 - 0.00001;
  expected(2, 1) = 352.412 - 123456789;
  expected(0, 2) = 1234.8234 - -0.00001;
  expected(1, 2) = 352.412 - 0.412;
  expected(2, 2) = 0;
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Overload, MulNum1) {
  S21Matrix source(3, 3);
  source(0, 0) = 1.3;
  source(1, 0) = 89.13;
  source(2, 0) = 1;
  source(0, 1) = 9.1;
  source(1, 1) = 7;
  source(2, 1) = 1389;
  source(0, 2) = 8.123;
  source(1, 2) = 0;
  source(2, 2) = 0.0004;
  S21Matrix result = source * 1.234567;
  S21Matrix expected(3, 3);
  expected(0, 0) = 1.3 * 1.234567;
  expected(1, 0) = 89.13 * 1.234567;
  expected(2, 0) = 1 * 1.234567;
  expected(0, 1) = 9.1 * 1.234567;
  expected(1, 1) = 7 * 1.234567;
  expected(2, 1) = 1389 * 1.234567;
  expected(0, 2) = 8.123 * 1.234567;
  expected(1, 2) = 0 * 1.234567;
  expected(2, 2) = 0.0004 * 1.234567;
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Overload, MulNum2) {
  S21Matrix source(3, 3);
  source(0, 0) = 1.3;
  source(1, 0) = 89.13;
  source(2, 0) = 1;
  source(0, 1) = 9.1;
  source(1, 1) = 7;
  source(2, 1) = 1389;
  source(0, 2) = 8.123;
  source(1, 2) = 0;
  source(2, 2) = 0.0004;
  S21Matrix result = source * 1.234567;
  S21Matrix expected(3, 3);
  expected(0, 0) = 1.3 * 1.234567;
  expected(1, 0) = 89.13 * 1.234567;
  expected(2, 0) = 1 * 1.234567;
  expected(0, 1) = 9.1 * 1.234567;
  expected(1, 1) = 7 * 1.234567;
  expected(2, 1) = 1389 * 1.234567;
  expected(0, 2) = 8.123 * 1.234567;
  expected(1, 2) = 0 * 1.234567;
  expected(2, 2) = 0.0004 * 1.234567;
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Overload, MulMat) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 3;
  source1(0, 1) = 27;
  source1(0, 2) = 18;
  source1(1, 0) = 0;
  source1(1, 1) = 18;
  source1(1, 2) = 15;
  source1(2, 0) = 24;
  source1(2, 1) = 9;
  source1(2, 2) = 9;

  source2(0, 0) = 3;
  source2(0, 1) = 18;
  source2(0, 2) = 24;
  source2(1, 0) = 21;
  source2(1, 1) = 15;
  source2(1, 2) = 24;
  source2(2, 0) = 0;
  source2(2, 1) = 27;
  source2(2, 2) = 3;

  expected(0, 0) = 576;
  expected(0, 1) = 945;
  expected(0, 2) = 774;
  expected(1, 0) = 378;
  expected(1, 1) = 675;
  expected(1, 2) = 477;
  expected(2, 0) = 261;
  expected(2, 1) = 810;
  expected(2, 2) = 819;

  S21Matrix result = source1 * source2;
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Overload, SumCut) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  source1 += source2;
  expected(0, 0) = 352.412 + 352.412;
  expected(1, 0) = 1 + 1;
  expected(2, 0) = 1;
  expected(0, 1) = -1234.8234 + 1234.8234;
  expected(1, 1) = 0.00001 + 0.00001;
  expected(2, 1) = 352.412 + 123456789;
  expected(0, 2) = -0.00001 + 1234.8234;
  expected(1, 2) = 352.412 + 0.412;
  expected(2, 2) = 9 + 9;
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(Overload, SubCut) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  source1 -= source2;
  expected(0, 0) = 352.412 - 352.412;
  expected(1, 0) = 0;
  expected(2, 0) = 1;
  expected(0, 1) = 1234.8234 - -1234.8234;
  expected(1, 1) = 0.00001 - 0.00001;
  expected(2, 1) = 352.412 - 123456789;
  expected(0, 2) = 1234.8234 - -0.00001;
  expected(1, 2) = 352.412 - 0.412;
  expected(2, 2) = 0;
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(Overload, MulNum1Cut) {
  S21Matrix source(3, 3);
  source(0, 0) = 1.3;
  source(1, 0) = 89.13;
  source(2, 0) = 1;
  source(0, 1) = 9.1;
  source(1, 1) = 7;
  source(2, 1) = 1389;
  source(0, 2) = 8.123;
  source(1, 2) = 0;
  source(2, 2) = 0.0004;
  source *= 1.234567;
  S21Matrix expected(3, 3);
  expected(0, 0) = 1.3 * 1.234567;
  expected(1, 0) = 89.13 * 1.234567;
  expected(2, 0) = 1 * 1.234567;
  expected(0, 1) = 9.1 * 1.234567;
  expected(1, 1) = 7 * 1.234567;
  expected(2, 1) = 1389 * 1.234567;
  expected(0, 2) = 8.123 * 1.234567;
  expected(1, 2) = 0 * 1.234567;
  expected(2, 2) = 0.0004 * 1.234567;
  ASSERT_EQ(source.EqMatrix(expected), 1);
}

TEST(Overload, MulMatCut) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 3;
  source1(0, 1) = 27;
  source1(0, 2) = 18;
  source1(1, 0) = 0;
  source1(1, 1) = 18;
  source1(1, 2) = 15;
  source1(2, 0) = 24;
  source1(2, 1) = 9;
  source1(2, 2) = 9;

  source2(0, 0) = 3;
  source2(0, 1) = 18;
  source2(0, 2) = 24;
  source2(1, 0) = 21;
  source2(1, 1) = 15;
  source2(1, 2) = 24;
  source2(2, 0) = 0;
  source2(2, 1) = 27;
  source2(2, 2) = 3;

  expected(0, 0) = 576;
  expected(0, 1) = 945;
  expected(0, 2) = 774;
  expected(1, 0) = 378;
  expected(1, 1) = 675;
  expected(1, 2) = 477;
  expected(2, 0) = 261;
  expected(2, 1) = 810;
  expected(2, 2) = 819;

  source1 *= source2;
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(Overload, Equity) {
  S21Matrix a(5, 5), b(5, 5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      a(i, j) = b(i, j) = i + j;
    }
  }
  ASSERT_EQ(a == b, 1);
  ASSERT_EQ(b == a, 1);
}

TEST(Overload, Constant) {
  int size = 5;
  S21Matrix a(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = i + j;
    }
  }
  S21Matrix b = a;
  ASSERT_DOUBLE_EQ(a(1, 1), b(1, 1));
}

TEST(SumMatrix, 1dMatrix) {
  S21Matrix source1, source2, expected;
  source1(0, 0) = 352.412;
  source2(0, 0) = 1234.8234;
  source1.SumMatrix(source2);
  expected(0, 0) = 352.412 + 1234.8234;
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(SumMatrix, 3dMatrix) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  source1.SumMatrix(source2);
  expected(0, 0) = 352.412 + 352.412;
  expected(1, 0) = 1 + 1;
  expected(2, 0) = 1;
  expected(0, 1) = -1234.8234 + 1234.8234;
  expected(1, 1) = 0.00001 + 0.00001;
  expected(2, 1) = 352.412 + 123456789;
  expected(0, 2) = -0.00001 + 1234.8234;
  expected(1, 2) = 352.412 + 0.412;
  expected(2, 2) = 9 + 9;
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(SubMatrix, 1dMatrix) {
  S21Matrix source1, source2, expected;
  source1(0, 0) = 352.412;
  source2(0, 0) = 1234.8234;
  source1.SubMatrix(source2);
  expected(0, 0) = 352.412 - 1234.8234;
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(SubMatrix, 3dMatrix) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  source1.SubMatrix(source2);
  expected(0, 0) = 352.412 - 352.412;
  expected(1, 0) = 0;
  expected(2, 0) = 1;
  expected(0, 1) = 1234.8234 - -1234.8234;
  expected(1, 1) = 0.00001 - 0.00001;
  expected(2, 1) = 352.412 - 123456789;
  expected(0, 2) = 1234.8234 - -0.00001;
  expected(1, 2) = 352.412 - 0.412;
  expected(2, 2) = 0;
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(SumMatrix, Uninitialized) {
  S21Matrix source1, source2;
  ASSERT_EQ(source1.EqMatrix(source2), 1);
}

TEST(SubMatrix, Uninitialized) {
  S21Matrix source1, source2;
  ASSERT_EQ(source1.EqMatrix(source2), 1);
}

TEST(MulMatrix, 3dMatrices) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 1;
  source1(0, 1) = 1;
  source1(0, 2) = 2;
  source1(1, 0) = 2;
  source1(1, 1) = 4;
  source1(1, 2) = 5;
  source1(2, 0) = 12;
  source1(2, 1) = 13;
  source1(2, 2) = 14;

  source2(0, 0) = 1;
  source2(0, 1) = -4;
  source2(0, 2) = -4;
  source2(1, 0) = -7;
  source2(1, 1) = -7;
  source2(1, 2) = -16;
  source2(2, 0) = -16;
  source2(2, 1) = -17;
  source2(2, 2) = -17;

  expected(0, 0) = -38;
  expected(0, 1) = -45;
  expected(0, 2) = -54;
  expected(1, 0) = -106;
  expected(1, 1) = -121;
  expected(1, 2) = -157;
  expected(2, 0) = -303;
  expected(2, 1) = -377;
  expected(2, 2) = -494;

  source1.MulMatrix(source2);
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(MulMatrix, DifferentDimension) {
  S21Matrix source1(3, 3), source2(3, 1), expected(3, 1);
  source1(0, 0) = 5;
  source1(0, 1) = 8;
  source1(0, 2) = -4;
  source1(1, 0) = 6;
  source1(1, 1) = 9;
  source1(1, 2) = -5;
  source1(2, 0) = 4;
  source1(2, 1) = 7;
  source1(2, 2) = -2;

  source2(0, 0) = 2;
  source2(1, 0) = -3;
  source2(2, 0) = 1;

  expected(0, 0) = -18;
  expected(1, 0) = -20;
  expected(2, 0) = -15;

  source1.MulMatrix(source2);
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(MulMatrix, BigMatrices) {
  S21Matrix source1(2, 4), source2(4, 6), expected(2, 6);
  source1(0, 0) = 9;
  source1(0, 1) = 9;
  source1(0, 2) = 2;
  source1(0, 3) = 8;
  source1(1, 0) = 6;
  source1(1, 1) = 7;
  source1(1, 2) = 8;
  source1(1, 3) = 5;

  source2(0, 0) = 2;
  source2(0, 1) = 5;
  source2(0, 2) = 6;
  source2(0, 3) = 8;
  source2(0, 4) = 5;
  source2(0, 5) = 1;
  source2(1, 0) = 0;
  source2(1, 1) = 7;
  source2(1, 2) = 6;
  source2(1, 3) = 4;
  source2(1, 4) = 8;
  source2(1, 5) = 9;
  source2(2, 0) = 0;
  source2(2, 1) = 7;
  source2(2, 2) = 1;
  source2(2, 3) = 6;
  source2(2, 4) = 2;
  source2(2, 5) = 7;
  source2(3, 0) = 1;
  source2(3, 1) = 4;
  source2(3, 2) = 8;
  source2(3, 3) = 4;
  source2(3, 4) = 0;
  source2(3, 5) = 6;

  expected(0, 0) = 26;
  expected(0, 1) = 154;
  expected(0, 2) = 174;
  expected(0, 3) = 152;
  expected(0, 4) = 121;
  expected(0, 5) = 152;
  expected(1, 0) = 17;
  expected(1, 1) = 155;
  expected(1, 2) = 126;
  expected(1, 3) = 144;
  expected(1, 4) = 102;
  expected(1, 5) = 155;

  source1.MulMatrix(source2);
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(MulMatrix, 3dMatrices2) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 3;
  source1(0, 1) = 27;
  source1(0, 2) = 18;
  source1(1, 0) = 0;
  source1(1, 1) = 18;
  source1(1, 2) = 15;
  source1(2, 0) = 24;
  source1(2, 1) = 9;
  source1(2, 2) = 9;

  source2(0, 0) = 3;
  source2(0, 1) = 18;
  source2(0, 2) = 24;
  source2(1, 0) = 21;
  source2(1, 1) = 15;
  source2(1, 2) = 24;
  source2(2, 0) = 0;
  source2(2, 1) = 27;
  source2(2, 2) = 3;

  expected(0, 0) = 576;
  expected(0, 1) = 945;
  expected(0, 2) = 774;
  expected(1, 0) = 378;
  expected(1, 1) = 675;
  expected(1, 2) = 477;
  expected(2, 0) = 261;
  expected(2, 1) = 810;
  expected(2, 2) = 819;

  source1.MulMatrix(source2);
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(MulMatrix, EmptyMatrices) {
  S21Matrix source1(19, 9), source2(9, 14), expected(19, 14);
  source1.MulMatrix(source2);
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(Transpose, 1dMatrix) {
  S21Matrix source, expected;
  source(0, 0) = 123;
  expected(0, 0) = 123;
  S21Matrix result = source.Transpose();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Transpose, 3dMatrix) {
  S21Matrix source(3, 3), expected(3, 3);
  source(0, 0) = 352.412;
  source(1, 0) = 1;
  source(2, 0) = 1;
  source(0, 1) = 1234.8234;
  source(1, 1) = 0.00001;
  source(2, 1) = 352.412;
  source(0, 2) = 1234.8234;
  source(1, 2) = 352.412;
  source(2, 2) = 9;
  expected(0, 0) = 352.412;
  expected(0, 1) = 1;
  expected(0, 2) = 1;
  expected(1, 0) = 1234.8234;
  expected(1, 1) = 0.00001;
  expected(1, 2) = 352.412;
  expected(2, 0) = 1234.8234;
  expected(2, 1) = 352.412;
  expected(2, 2) = 9;
  S21Matrix result = source.Transpose();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Transpose, 3x4Matrix) {
  S21Matrix source(3, 4), expected(4, 3);
  source(0, 0) = 352.412;
  source(1, 0) = 1;
  source(2, 0) = 1;
  source(0, 1) = 1234.8234;
  source(1, 1) = 0.00001;
  source(2, 1) = 352.412;
  source(0, 2) = 1234.8234;
  source(1, 2) = 352.412;
  source(2, 2) = 9;
  source(0, 3) = 13;
  source(1, 3) = 32.42;
  source(2, 3) = 0.9;
  expected(0, 0) = 352.412;
  expected(0, 1) = 1;
  expected(0, 2) = 1;
  expected(1, 0) = 1234.8234;
  expected(1, 1) = 0.00001;
  expected(1, 2) = 352.412;
  expected(2, 0) = 1234.8234;
  expected(2, 1) = 352.412;
  expected(2, 2) = 9;
  expected(3, 0) = 13;
  expected(3, 1) = 32.42;
  expected(3, 2) = 0.9;
  ASSERT_EQ(source.Transpose().EqMatrix(expected), 1);
}

TEST(Transpose, 4x3Matrix) {
  S21Matrix source(4, 3), expected(3, 4);
  source(0, 0) = 352.412;
  source(1, 0) = 1;
  source(2, 0) = 1;
  source(3, 0) = 1234.8234;
  source(0, 1) = 0.00001;
  source(1, 1) = 352.412;
  source(2, 1) = 1234.8234;
  source(3, 1) = 352.412;
  source(0, 2) = 9;
  source(1, 2) = 13;
  source(2, 2) = 32.42;
  source(3, 2) = 0.9;
  expected(0, 0) = 352.412;
  expected(0, 1) = 1;
  expected(0, 2) = 1;
  expected(0, 3) = 1234.8234;
  expected(1, 0) = 0.00001;
  expected(1, 1) = 352.412;
  expected(1, 2) = 1234.8234;
  expected(1, 3) = 352.412;
  expected(2, 0) = 9;
  expected(2, 1) = 13;
  expected(2, 2) = 32.42;
  expected(2, 3) = 0.9;
  ASSERT_EQ(source.Transpose().EqMatrix(expected), 1);
}

TEST(Complements, SizeError) {
  S21Matrix source(2, 1);
  EXPECT_THROW(source.CalcComplements(), std::logic_error);
}

TEST(Complements, EmptyMatrix) {
  S21Matrix source;
  EXPECT_THROW(source.CalcComplements(), std::logic_error);
}

TEST(Determinant, WrongSize) {
  S21Matrix source(3, 9);
  EXPECT_THROW(source.Determinant(), std::logic_error);
}

TEST(InverseMatrix, Uninitialized) {
  S21Matrix source;
  EXPECT_THROW(source.InverseMatrix(), std::logic_error);
}

TEST(InverseMatrix, AllZero) {
  S21Matrix source(4, 4);
  EXPECT_THROW(source.InverseMatrix(), std::logic_error);
}

TEST(InverseMatrix, WrongSize) {
  S21Matrix source(10, 9);
  EXPECT_THROW(source.InverseMatrix(), std::logic_error);
}

TEST(MulMatrix, Size_error) {
  S21Matrix source1(2, 2), source2(5, 5);
  EXPECT_THROW(source1.MulMatrix(source2), std::logic_error);
}

TEST(Index, OutOfRange) {
  S21Matrix source1(3, 3);
  EXPECT_THROW(source1(12, 4), std::logic_error);
}

TEST(Seter, LessThanRows) {
  S21Matrix source;
  EXPECT_THROW(source.SetRows(-3), std::invalid_argument);
}

TEST(Seter, LessThanCols) {
  S21Matrix source;
  EXPECT_THROW(source.SetCols(-3), std::invalid_argument);
}

TEST(Constructors, WrongIndex) {
  EXPECT_THROW(S21Matrix source(-1, -1), std::invalid_argument);
}

TEST(Overload, WrongIndex) {
  const S21Matrix a(9, 9);
  S21Matrix b;
  b = a;
  EXPECT_EQ(b.EqMatrix(a), 1);
}

TEST(MoveAssignmentOperator, MoveAssignmentOperator) {
  S21Matrix matrix(3, 4);
  S21Matrix other(2, 2);

  other = std::move(matrix);

  EXPECT_EQ(other.GetRows(), 3);
  EXPECT_EQ(other.GetCols(), 4);

  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 2);
}

TEST(SumMatrix, DiffSize) {
  S21Matrix source1(3, 2), source2(2, 3);
  EXPECT_THROW(source1.SumMatrix(source2), std::logic_error);
  EXPECT_THROW(source2.SumMatrix(source1), std::logic_error);
}

TEST(SubMatrix, DiffSize) {
  S21Matrix source1(3, 2), source2(2, 3);
  EXPECT_THROW(source1.SubMatrix(source2), std::logic_error);
  EXPECT_THROW(source2.SubMatrix(source1), std::logic_error);
}

TEST(Inverse, Uncorrect) {
  S21Matrix source1(3, 2);
  EXPECT_THROW(source1.InverseMatrix(), std::logic_error);
}

TEST(Inverse, Uncorrect_1) {
  S21Matrix source1(3, 12);
  EXPECT_THROW(source1.InverseMatrix(), std::logic_error);
}

TEST(Constructors, Move) {
  S21Matrix source(3, 3);
  source(0, 0) = 99;
  source(2, 2) = -99;
  source(1, 1) = 13;
  S21Matrix moved_matrix(std::move(source));
  ASSERT_EQ(moved_matrix(0, 0), 99);
  ASSERT_EQ(moved_matrix(1, 1), 13);
  ASSERT_EQ(moved_matrix(2, 2), -99);
}

TEST(InverseMatrix, BigMatrix) {
  int size = 8;
  S21Matrix source(size, size), expected(size, size);
  source(0, 0) = 2;
  source(0, 1) = 8;
  source(0, 2) = 7;
  source(0, 3) = 4;
  source(0, 4) = 1;
  source(0, 5) = 8;
  source(0, 6) = 3;
  source(0, 7) = 9;
  source(1, 0) = 4;
  source(1, 1) = 2;
  source(1, 2) = 6;
  source(1, 3) = 2;
  source(1, 4) = 2;
  source(1, 5) = 1;
  source(1, 6) = 5;
  source(1, 7) = 8;
  source(2, 0) = 8;
  source(2, 1) = 6;
  source(2, 2) = 7;
  source(2, 3) = 7;
  source(2, 4) = 3;
  source(2, 5) = 4;
  source(2, 6) = 4;
  source(2, 7) = 1;
  source(3, 0) = 1;
  source(3, 1) = 7;
  source(3, 2) = 0;
  source(3, 3) = 4;
  source(3, 4) = 4;
  source(3, 5) = 3;
  source(3, 6) = 0;
  source(3, 7) = 5;
  source(4, 0) = 5;
  source(4, 1) = 7;
  source(4, 2) = 5;
  source(4, 3) = 6;
  source(4, 4) = 8;
  source(4, 5) = 3;
  source(4, 6) = 1;
  source(4, 7) = 9;
  source(5, 0) = 3;
  source(5, 1) = 7;
  source(5, 2) = 8;
  source(5, 3) = 0;
  source(5, 4) = 5;
  source(5, 5) = 7;
  source(5, 6) = 0;
  source(5, 7) = 2;
  source(6, 0) = 5;
  source(6, 1) = 8;
  source(6, 2) = 3;
  source(6, 3) = 5;
  source(6, 4) = 9;
  source(6, 5) = 1;
  source(6, 6) = 2;
  source(6, 7) = 0;
  source(7, 0) = 7;
  source(7, 1) = 8;
  source(7, 2) = 7;
  source(7, 3) = 4;
  source(7, 4) = 7;
  source(7, 5) = 9;
  source(7, 6) = 1;
  source(7, 7) = 5;

  expected(0, 0) = -0.5349902183;
  expected(0, 1) = 0.2894503762;
  expected(0, 2) = 0.2648128502;
  expected(0, 3) = 0.6295578936;
  expected(0, 4) = -0.1684575429;
  expected(0, 5) = 0.2471263249;
  expected(0, 6) = -0.3773947292;
  expected(0, 7) = 0.0217143747;
  expected(1, 0) = -0.3358379646;
  expected(1, 1) = 0.2037511071;
  expected(1, 2) = 0.2032547229;
  expected(1, 3) = 0.6234293334;
  expected(1, 4) = -0.1799149334;
  expected(1, 5) = 0.3295114996;
  expected(1, 6) = -0.2254070837;
  expected(1, 7) = -0.1935314328;
  expected(2, 0) = 0.09452225456;
  expected(2, 1) = -0.09221066155;
  expected(2, 2) = 0.03813722914;
  expected(2, 3) = -0.2190871073;
  expected(2, 4) = 0.1695573745;
  expected(2, 5) = 0.1092580516;
  expected(2, 6) = 0.007715043036;
  expected(2, 7) = -0.1600498331;
  expected(3, 0) = 0.3630563639;
  expected(3, 1) = -0.3052665388;
  expected(3, 2) = -0.04656927155;
  expected(3, 3) = -0.4771776828;
  expected(3, 4) = 0.2389343637;
  expected(3, 5) = -0.2685487089;
  expected(3, 6) = 0.1928760759;
  expected(3, 7) = -0.001245826966;
  expected(4, 0) = 0.2619837848;
  expected(4, 1) = -0.133556544;
  expected(4, 2) = -0.2495968906;
  expected(4, 3) = -0.4562289726;
  expected(4, 4) = 0.1044612934;
  expected(4, 5) = -0.2245895097;
  expected(4, 6) = 0.3128420752;
  expected(4, 7) = 0.1500734843;
  expected(5, 0) = 0.2992174649;
  expected(5, 1) = -0.1560300945;
  expected(5, 2) = -0.1850280149;
  expected(5, 3) = -0.3646314915;
  expected(5, 4) = -0.02339656554;
  expected(5, 5) = -0.2701059926;
  expected(5, 6) = 0.1915783395;
  expected(5, 7) = 0.2628500238;
  expected(6, 0) = 0.3028673486;
  expected(6, 1) = 0.0418714657;
  expected(6, 2) = -0.2001336669;
  expected(6, 3) = -0.3106910771;
  expected(6, 4) = -0.1692459178;
  expected(6, 5) = -0.2826713255;
  expected(6, 6) = 0.3477738954;
  expected(6, 7) = 0.1562734201;
  expected(7, 0) = -0.1023914038;
  expected(7, 1) = 0.1015348978;
  expected(7, 2) = 0.0104305565;
  expected(7, 3) = 0.1667915738;
  expected(7, 4) = 0.02489382894;
  expected(7, 5) = 0.04583280613;
  expected(7, 6) = -0.1284726616;
  expected(7, 7) = -0.01017100922;

  S21Matrix result = source.InverseMatrix();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(InverseMatrix, 3dMatrix) {
  int size = 3;
  S21Matrix source(size, size), expected(size, size);
  source(0, 0) = 3;
  source(0, 1) = 27;
  source(0, 2) = 18;
  source(1, 0) = 0;
  source(1, 1) = 18;
  source(1, 2) = 15;
  source(2, 0) = 24;
  source(2, 1) = 9;
  source(2, 2) = 9;

  expected(0, 0) = 0.01333333333;
  expected(0, 1) = -0.04;
  expected(0, 2) = 0.04;
  expected(1, 0) = 0.1777777778;
  expected(1, 1) = -0.2;
  expected(1, 2) = -0.02222222222;
  expected(2, 0) = -0.2133333333;
  expected(2, 1) = 0.3066666667;
  expected(2, 2) = 0.02666666667;

  S21Matrix result = source.InverseMatrix();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(InverseMatrix, 3dMatrix2) {
  int size = 3;
  S21Matrix source(size, size), expected(size, size);
  source(0, 0) = 4;
  source(0, 1) = 6;
  source(0, 2) = 8;
  source(1, 0) = 9;
  source(1, 1) = 2;
  source(1, 2) = 7;
  source(2, 0) = 9;
  source(2, 1) = 1;
  source(2, 2) = 0;

  expected(0, 0) = -0.02517985612;
  expected(0, 1) = 0.02877697842;
  expected(0, 2) = 0.09352517986;
  expected(1, 0) = 0.226618705;
  expected(1, 1) = -0.2589928058;
  expected(1, 2) = 0.1582733813;
  expected(2, 0) = -0.03237410072;
  expected(2, 1) = 0.1798561151;
  expected(2, 2) = -0.1654676259;

  S21Matrix result = source.InverseMatrix();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(InverseMatrix, 8dMatrix) {
  int size = 8;
  S21Matrix source(size, size), expected(size, size);
  source(0, 0) = 2;
  source(0, 1) = 8;
  source(0, 2) = 7;
  source(0, 3) = 4;
  source(0, 4) = 1;
  source(0, 5) = 8;
  source(0, 6) = 3;
  source(0, 7) = 9;
  source(1, 0) = 4;
  source(1, 1) = 2;
  source(1, 2) = 6;
  source(1, 3) = 2;
  source(1, 4) = 2;
  source(1, 5) = 1;
  source(1, 6) = 5;
  source(1, 7) = 8;
  source(2, 0) = 8;
  source(2, 1) = 6;
  source(2, 2) = 7;
  source(2, 3) = 7;
  source(2, 4) = 3;
  source(2, 5) = 4;
  source(2, 6) = 4;
  source(2, 7) = 1;
  source(3, 0) = 1;
  source(3, 1) = 7;
  source(3, 2) = 0;
  source(3, 3) = 4;
  source(3, 4) = 4;
  source(3, 5) = 3;
  source(3, 6) = 0;
  source(3, 7) = 5;
  source(4, 0) = 5;
  source(4, 1) = 7;
  source(4, 2) = 5;
  source(4, 3) = 6;
  source(4, 4) = 8;
  source(4, 5) = 3;
  source(4, 6) = 1;
  source(4, 7) = 9;
  source(5, 0) = 3;
  source(5, 1) = 7;
  source(5, 2) = 8;
  source(5, 3) = 0;
  source(5, 4) = 5;
  source(5, 5) = 7;
  source(5, 6) = 0;
  source(5, 7) = 2;
  source(6, 0) = 5;
  source(6, 1) = 8;
  source(6, 2) = 3;
  source(6, 3) = 5;
  source(6, 4) = 9;
  source(6, 5) = 1;
  source(6, 6) = 2;
  source(6, 7) = 0;
  source(7, 0) = 7;
  source(7, 1) = 8;
  source(7, 2) = 7;
  source(7, 3) = 4;
  source(7, 4) = 7;
  source(7, 5) = 9;
  source(7, 6) = 1;
  source(7, 7) = 5;

  expected(0, 0) = -0.5349902183;
  expected(0, 1) = 0.2894503762;
  expected(0, 2) = 0.2648128502;
  expected(0, 3) = 0.6295578936;
  expected(0, 4) = -0.1684575429;
  expected(0, 5) = 0.2471263249;
  expected(0, 6) = -0.3773947292;
  expected(0, 7) = 0.0217143747;
  expected(1, 0) = -0.3358379646;
  expected(1, 1) = 0.2037511071;
  expected(1, 2) = 0.2032547229;
  expected(1, 3) = 0.6234293334;
  expected(1, 4) = -0.1799149334;
  expected(1, 5) = 0.3295114996;
  expected(1, 6) = -0.2254070837;
  expected(1, 7) = -0.1935314328;
  expected(2, 0) = 0.09452225456;
  expected(2, 1) = -0.09221066155;
  expected(2, 2) = 0.03813722914;
  expected(2, 3) = -0.2190871073;
  expected(2, 4) = 0.1695573745;
  expected(2, 5) = 0.1092580516;
  expected(2, 6) = 0.007715043036;
  expected(2, 7) = -0.1600498331;
  expected(3, 0) = 0.3630563639;
  expected(3, 1) = -0.3052665388;
  expected(3, 2) = -0.04656927155;
  expected(3, 3) = -0.4771776828;
  expected(3, 4) = 0.2389343637;
  expected(3, 5) = -0.2685487089;
  expected(3, 6) = 0.1928760759;
  expected(3, 7) = -0.001245826966;
  expected(4, 0) = 0.2619837848;
  expected(4, 1) = -0.133556544;
  expected(4, 2) = -0.2495968906;
  expected(4, 3) = -0.4562289726;
  expected(4, 4) = 0.1044612934;
  expected(4, 5) = -0.2245895097;
  expected(4, 6) = 0.3128420752;
  expected(4, 7) = 0.1500734843;
  expected(5, 0) = 0.2992174649;
  expected(5, 1) = -0.1560300945;
  expected(5, 2) = -0.1850280149;
  expected(5, 3) = -0.3646314915;
  expected(5, 4) = -0.02339656554;
  expected(5, 5) = -0.2701059926;
  expected(5, 6) = 0.1915783395;
  expected(5, 7) = 0.2628500238;
  expected(6, 0) = 0.3028673486;
  expected(6, 1) = 0.0418714657;
  expected(6, 2) = -0.2001336669;
  expected(6, 3) = -0.3106910771;
  expected(6, 4) = -0.1692459178;
  expected(6, 5) = -0.2826713255;
  expected(6, 6) = 0.3477738954;
  expected(6, 7) = 0.1562734201;
  expected(7, 0) = -0.1023914038;
  expected(7, 1) = 0.1015348978;
  expected(7, 2) = 0.0104305565;
  expected(7, 3) = 0.1667915738;
  expected(7, 4) = 0.02489382894;
  expected(7, 5) = 0.04583280613;
  expected(7, 6) = -0.1284726616;
  expected(7, 7) = -0.01017100922;

  S21Matrix result = source.InverseMatrix();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

// Тестирование оператора сложения матриц
TEST(OperatorPlus, OperatorPlus) {
  // Создаем две матрицы для сложения
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  // Устанавливаем значения для матриц
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  matrix2(0, 0) = 9;
  matrix2(0, 1) = 8;
  matrix2(0, 2) = 7;
  matrix2(1, 0) = 6;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 4;
  matrix2(2, 0) = 3;
  matrix2(2, 1) = 2;
  matrix2(2, 2) = 1;

  // Выполняем операцию сложения матриц
  S21Matrix result = matrix1 + matrix2;

  // Проверяем результат сложения
  EXPECT_EQ(result(0, 0), 10);
  EXPECT_EQ(result(0, 1), 10);
  EXPECT_EQ(result(0, 2), 10);
  EXPECT_EQ(result(1, 0), 10);
  EXPECT_EQ(result(1, 1), 10);
  EXPECT_EQ(result(1, 2), 10);
  EXPECT_EQ(result(2, 0), 10);
  EXPECT_EQ(result(2, 1), 10);
  EXPECT_EQ(result(2, 2), 10);
}

// Тестирование оператора вычитания матриц
TEST(OperatorMinus, OperatorMinus) {
  // Создаем две матрицы для вычитания
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  // Устанавливаем значения для матриц
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  matrix2(0, 0) = 9;
  matrix2(0, 1) = 8;
  matrix2(0, 2) = 7;
  matrix2(1, 0) = 6;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 4;
  matrix2(2, 0) = 3;
  matrix2(2, 1) = 2;
  matrix2(2, 2) = 1;

  // Выполняем операцию вычитания матриц
  S21Matrix result = matrix1 - matrix2;

  // Проверяем результат вычитания
  EXPECT_EQ(result(0, 0), -8);
  EXPECT_EQ(result(0, 1), -6);
  EXPECT_EQ(result(0, 2), -4);
  EXPECT_EQ(result(1, 0), -2);
  EXPECT_EQ(result(1, 1), 0);
  EXPECT_EQ(result(1, 2), 2);
  EXPECT_EQ(result(2, 0), 4);
  EXPECT_EQ(result(2, 1), 6);
  EXPECT_EQ(result(2, 2), 8);
}

// Тестирование оператора умножения матриц
TEST(OperatorMultiply, OperatorMultiply) {
  // Создаем две матрицы для умножения
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);

  // Устанавливаем значения для матриц
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 9;
  matrix2(0, 1) = 8;
  matrix2(1, 0) = 6;
  matrix2(1, 1) = 5;
  matrix2(2, 0) = 3;
  matrix2(2, 1) = 2;

  // Выполняем операцию умножения матриц
  S21Matrix result = matrix1 * matrix2;

  // Проверяем результат умножения
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_EQ(result(0, 0), 30);
  EXPECT_EQ(result(0, 1), 24);
  EXPECT_EQ(result(1, 0), 84);
  EXPECT_EQ(result(1, 1), 69);
}

TEST(move, testleak) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix2 = std::move(matrix1);
}

TEST(move, testleak1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(std::move(matrix1));
}

/* Тесты для конструкторов */

// 	'EXPECT_ANY_THROW' истинно, если выражение бросает любое исключение

TEST(ParametrizedConstructor, test1) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(3, 0); });
}

TEST(ParametrizedConstructor, test2) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(3, -2); });
}

TEST(ParametrizedConstructor, test3) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(0, 0); });
}

TEST(ParametrizedConstructor, test4) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(-1, 0); });
}

TEST(ParametrizedConstructor, test5) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(-1, 4); });
}

TEST(ParametrizedConstructor, test6) {
  EXPECT_NO_THROW({
    S21Matrix test = S21Matrix(3, 4);
    EXPECT_EQ(test.GetCols(), 4);
    EXPECT_EQ(test.GetRows(), 3);
  });
}

TEST(CopyConstructor, test1) {
  EXPECT_NO_THROW({
    S21Matrix first = S21Matrix(3, 3);
    for (int i = 0; i < first.GetRows(); i++) {
      for (int j = 0; j < first.GetCols(); j++) {
        first(i, j) = i + j;
      }
    }
    S21Matrix second(first);
    for (int i = 0; i < first.GetRows(); i++) {
      for (int j = 0; j < first.GetCols(); j++) {
        EXPECT_EQ(first(i, j), second(i, j));
      }
    }
  });
}

TEST(CopyConstructor, test2) {
  EXPECT_NO_THROW({
    S21Matrix first = S21Matrix(3, 4);
    S21Matrix second(first);
    EXPECT_EQ(first.GetRows(), second.GetRows());
    EXPECT_EQ(first.GetCols(), second.GetCols());
  });
}

TEST(CopyConstructor, test3) {
  S21Matrix first(3, 3);
  S21Matrix second;
  EXPECT_NO_THROW({ second = S21Matrix(first); });
  EXPECT_FALSE(&second == &first);
}

// TEST(CopyConstructor, test4) {
//   S21Matrix matrix(3, 3);
//   EXPECT_ANY_THROW(S21Matrix matrix(matrix));
// }

/* тесты для Геттеров и Сеттеров */

TEST(Getter, test1) {
  S21Matrix test(3, 3);
  EXPECT_EQ(test.GetRows(), 3);
  EXPECT_EQ(test.GetCols(), 3);
}

TEST(Getter, test2) {
  S21Matrix test(2, 4);
  EXPECT_EQ(test.GetRows(), 2);
  EXPECT_EQ(test.GetCols(), 4);
}

TEST(Getter, test3) {
  S21Matrix test(5, 1);
  EXPECT_EQ(test.GetRows(), 5);
  EXPECT_EQ(test.GetCols(), 1);
}

// TEST(Getter, test4) {
//   S21Matrix test = S21Matrix();
//   EXPECT_EQ(test.GetRows(), 0);
//   EXPECT_EQ(test.GetCols(), 0);
// }

TEST(Getter, test5) {
  S21Matrix test(100, 100);
  EXPECT_EQ(test.GetRows(), 100);
  EXPECT_EQ(test.GetCols(), 100);
}

TEST(Setter, test1) {
  EXPECT_ANY_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetRows(0);
  });
}

TEST(Setter, test2) {
  EXPECT_ANY_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetRows(-1);
  });
}

TEST(Setter, test3) {
  EXPECT_ANY_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetCols(-1);
  });
}

TEST(Setter, test4) {
  S21Matrix test = S21Matrix(2, 2);
  for (int i = 0; i < test.GetRows(); i++) {
    for (int j = 0; j < test.GetCols(); j++) {
      test(i, j) = i + j;
    }
  }
  test.SetCols(1);
  double result[2][1] = {{0}, {1}};
  EXPECT_EQ(test.GetCols(), 1);
  for (int i = 0; i < test.GetRows(); i++) {
    for (int j = 0; j < test.GetCols(); j++) {
      EXPECT_NO_THROW({ EXPECT_EQ(test(i, j), result[i][j]); });
    }
  }
}

TEST(Setter, test5) {
  S21Matrix test(3, 3);
  for (int i = 0; i < test.GetRows(); i++) {
    for (int j = 0; j < test.GetCols(); j++) {
      test(i, j) = i + j;
    }
  }
  test.SetRows(2);
  test.SetCols(2);
  double result[2][2] = {{0, 1}, {1, 2}};
  EXPECT_EQ(test.GetRows(), 2);
  EXPECT_EQ(test.GetCols(), 2);
  for (int i = 0; i < test.GetRows(); i++) {
    for (int j = 0; j < test.GetCols(); j++) {
      EXPECT_NO_THROW({ EXPECT_EQ(test(i, j), result[i][j]); });
    }
  }
}

/* Тесты для методов */
TEST(EqMatrixTest, EqualMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_TRUE(mat1.EqMatrix(mat2));
  EXPECT_TRUE(mat2.EqMatrix(mat1));
}

TEST(EqMatrixTest, UnequalMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(mat1.EqMatrix(mat2));
  EXPECT_FALSE(mat2.EqMatrix(mat1));
}

TEST(EqMatrixTest, UnequalSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 3);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(mat1.EqMatrix(mat2));
  EXPECT_FALSE(mat2.EqMatrix(mat1));
}

TEST(SumMatrixTest, Addition) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};
  double result[2][2] = {{6, 8}, {10, 12}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SumMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), result[i][j]);
    }
  }
}

TEST(SumMatrixTest, DifferentSizes) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{7, 8}, {9, 10}, {11, 12}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW(mat1.SumMatrix(mat2), std::logic_error);
}

TEST(SumMatrixTest, EmptyMatrix) {
  double matrix[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix();

  EXPECT_THROW(mat1.SumMatrix(mat2), std::logic_error);
}

TEST(SubMatrixTest, SubtractMatrix) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 1}, {1, 2}};
  double expected[2][2] = {{-1, 1}, {2, 2}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SubMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(SubMatrixTest, DifferentSizes) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{7, 8}, {9, 10}, {11, 12}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW(mat1.SubMatrix(mat2), std::logic_error);
}

TEST(SubMatrixTest, EmptyMatrix) {
  double matrix[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix();

  EXPECT_THROW(mat1.SubMatrix(mat2), std::logic_error);
}

TEST(MulNumberTest, MultiplyNumber) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = 2;
  double expected[2][2] = {{2, 4}, {6, 8}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumberZero) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double num = 0;
  double expected[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumberNegative) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = -1;
  double expected[2][2] = {{-1, -2}, {-3, -4}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumberFraction) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = 0.5;
  double expected[2][2] = {{0.5, 1}, {1.5, 2}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulMatrixTest, MultiplyMatrixIdentity) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double identity[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix identityMat = S21Matrix(3, 3);
  for (int i = 0; i < identityMat.GetRows(); i++) {
    for (int j = 0; j < identityMat.GetCols(); j++) {
      identityMat(i, j) = identity[i][j];
    }
  }

  mat.MulMatrix(identityMat);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), matrix[i][j]);
    }
  }
}

TEST(MulMatrixTest, MultiplyMatrixArbitrary) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{2, 0}, {0, 2}, {1, 1}};
  double expected[2][2] = {{5, 7}, {14, 16}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.MulMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(MulMatrixTest, MultiplyMatrixThrow) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[4][2] = {{2, 0}, {0, 2}, {1, 1}, {3, 3}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(4, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_ANY_THROW({ mat1.MulMatrix(mat2); });
}

TEST(TransposeTest, SquareMatrix) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double expected[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.GetRows(); i++) {
    for (int j = 0; j < transposed.GetCols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(TransposeTest, RectangularMatrix) {
  double matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double expected[3][2] = {{1, 4}, {2, 5}, {3, 6}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.GetRows(); i++) {
    for (int j = 0; j < transposed.GetCols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(TransposeTest, SingleElementMatrix) {
  double matrix[1][1] = {{42}};
  double expected[1][1] = {{42}};

  S21Matrix mat = S21Matrix(1, 1);
  mat(0, 0) = matrix[0][0];

  S21Matrix transposed = mat.Transpose();

  EXPECT_EQ(transposed.GetRows(), 1);
  EXPECT_EQ(transposed.GetCols(), 1);
  EXPECT_EQ(transposed(0, 0), expected[0][0]);
}

TEST(TransposeTest, NonSquareMatrix) {
  double matrix[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  double expected[2][3] = {{1, 3, 5}, {2, 4, 6}};

  S21Matrix mat = S21Matrix(3, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.GetRows(); i++) {
    for (int j = 0; j < transposed.GetCols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(CalcComplementsTest, SquareMatrix) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double expected[3][3] = {{-3, 6, -3}, {6, -12, 6}, {-3, 6, -3}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix complements = mat.CalcComplements();

  for (int i = 0; i < complements.GetRows(); i++) {
    for (int j = 0; j < complements.GetCols(); j++) {
      EXPECT_EQ(complements(i, j), expected[i][j]);
    }
  }
}

TEST(CalcComplementsTest, NonSquareMatrix) {
  double matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  EXPECT_THROW(S21Matrix complements = mat.CalcComplements(), std::logic_error);
}

TEST(CalcComplementsTest, ThrowsLogicErrorWhenSizeIsLessThan2) {
  // Создаем матрицу размером 1x1
  S21Matrix matrix(1, 1);

  // Ожидаем, что при вызове CalcComplements() будет выброшено исключение
  // std::logic_error
  EXPECT_THROW(matrix.CalcComplements(), std::logic_error);
}

TEST(DeterminantTest, SingleElementMatrix) {
  double matrix[1][1] = {{5}};

  S21Matrix mat = S21Matrix(1, 1);
  mat(0, 0) = matrix[0][0];

  double determinant = mat.Determinant();

  EXPECT_EQ(determinant, matrix[0][0]);
}

TEST(DeterminantTest, SquareMatrix) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
      // std::cout << mat(i, j) << ' ';
    }
    // std::cout << std::endl;
  }

  double determinant = mat.Determinant();
  // std::cout << '\n';

  EXPECT_EQ(determinant, 0);
}

//// FAIL
TEST(DeterminantTest, SpecificNonZeroDeterminant) {
  double matrix[3][3] = {{1, 2, 2}, {4, 5, 5}, {7, 8, 9}};
  double expectedDeterminant = -3;

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  double determinant = mat.Determinant();
  EXPECT_EQ(determinant, expectedDeterminant);
}

TEST(DeterminantTest, NonSquareMatrix) {
  double matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  EXPECT_THROW(mat.Determinant(), std::logic_error);
}

TEST(InverseMatrixTest, inverese_3x3_3) {
  const int size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);

  given(0, 0) = 2;
  given(0, 1) = 5;
  given(0, 2) = 7;
  given(1, 0) = 6;
  given(1, 1) = 3;
  given(1, 2) = 4;
  given(2, 0) = 5;
  given(2, 1) = -2;
  given(2, 2) = -3;

  expected(0, 0) = 1;
  expected(0, 1) = -1;
  expected(0, 2) = 1;
  expected(1, 0) = -38;
  expected(1, 1) = 41;
  expected(1, 2) = -34;
  expected(2, 0) = 27;
  expected(2, 1) = -29;
  expected(2, 2) = 24;
  ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(InverseMatrixTest, ThrowsLogicErrorWhenDeterminantIsZero) {
  S21Matrix matrix(2, 2);
  // Здесь можно установить значения матрицы так, чтобы определитель был равен 0
  matrix(0, 0) = 0;
  matrix(0, 1) = 0;
  matrix(1, 0) = 0;
  matrix(1, 1) = 0;
  // Ожидаем, что при вызове InverseMatrix() будет выброшено исключение
  // std::logic_error
  EXPECT_THROW(matrix.InverseMatrix(), std::logic_error);
}

/* Тесты для перезагрузки операторов */

TEST(OperatorEqual, test1) {
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix(3, 4);
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = i + j;
      }
    }
    S21Matrix result = S21Matrix();
    result = check;
    EXPECT_EQ(result.GetRows(), check.GetRows());
    EXPECT_EQ(result.GetCols(), check.GetCols());
    for (int i = 0; i < result.GetRows(); i++) {
      for (int j = 0; j < result.GetCols(); j++) {
        EXPECT_EQ(result(i, j), check(i, j));
      }
    }
  });
}

TEST(OperatorEqual, test2) {
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix();
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = i + j;
      }
    }
    S21Matrix result = S21Matrix(2, 2);
    result = check;
    EXPECT_EQ(result.GetRows(), check.GetRows());
    EXPECT_EQ(result.GetCols(), check.GetCols());
    for (int i = 0; i < result.GetRows(); i++) {
      for (int j = 0; j < result.GetCols(); j++) {
        EXPECT_EQ(result(i, j), check(i, j));
      }
    }
  });
}

TEST(OperatorPlus, test1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;

  ASSERT_TRUE((matrix_a + matrix_b) == result);
}

TEST(OperatorPlus, test2) {
  EXPECT_ANY_THROW({
    S21Matrix check = S21Matrix(3, 4);
    S21Matrix result = S21Matrix(3, 3);
    S21Matrix result2 = result + check;
  });
}

TEST(OperatorMinus, test1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

  ASSERT_TRUE((matrix_a - matrix_b) == result);
}

TEST(OperatorMinus, test2) {
  EXPECT_ANY_THROW({
    S21Matrix check = S21Matrix(3, 4);
    S21Matrix result = S21Matrix(3, 3);
    result = result - check;
  });
}

TEST(OperatorMultNum, test1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((matrix_a * 10) == result);
}

TEST(OperatorMultNum, test2) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((matrix_a * 10.0) == result);
}

TEST(OperatorMultMatrix, test1) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 58.0);
  EXPECT_EQ(matrix1(0, 1), 64.0);
  EXPECT_EQ(matrix1(1, 0), 139.0);
  EXPECT_EQ(matrix1(1, 1), 154.0);
}

TEST(OperatorMultMatrix, test3) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  ASSERT_TRUE((matrix_a * matrix_b) == result);
}

TEST(OperatorMultMatrix, test2) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][2] = {{2, 0}, {0, 2}, {0, 2}};
  EXPECT_ANY_THROW({
    S21Matrix check1 = S21Matrix(2, 2);
    for (int i = 0; i < check1.GetRows(); i++) {
      for (int j = 0; j < check1.GetCols(); j++) {
        check1(i, j) = matrix1[i][j];
      }
    }
    S21Matrix check2 = S21Matrix(3, 2);
    for (int i = 0; i < check2.GetRows(); i++) {
      for (int j = 0; j < check2.GetCols(); j++) {
        check2(i, j) = matrix2[i][j];
      }
    }
    check1 = check1 * check2;
  });
}

TEST(OperatorEquality, EqualMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {3, 4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_TRUE(matrixA == matrixB);
  EXPECT_TRUE(matrixB == matrixA);
}

TEST(OperatorEquality, DifferentMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {4, 3}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(matrixA == matrixB);
  EXPECT_FALSE(matrixB == matrixA);
}

TEST(OperatorEquality, DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(matrixA == matrixB);
  EXPECT_FALSE(matrixB == matrixA);
}

TEST(OperatorAssignment, Assignment) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  matrixB = matrixA;

  EXPECT_EQ(matrixB.GetRows(), matrixA.GetRows());
  EXPECT_EQ(matrixB.GetCols(), matrixA.GetCols());

  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      EXPECT_EQ(matrixB(i, j), matrixA(i, j));
    }
  }
}

// TEST(OperatorAssignment, SelfAssignment) {
//   double matrix1[2][2] = {{1, 2}, {3, 4}};

//   S21Matrix matrixA = S21Matrix(2, 2);
//   for (int i = 0; i < matrixA.GetRows(); i++) {
//     for (int j = 0; j < matrixA.GetCols(); j++) {
//       matrixA(i, j) = matrix1[i][j];
//     }
//   }

//   matrixA = matrixA;

//   EXPECT_EQ(matrixA.GetRows(), 2);
//   EXPECT_EQ(matrixA.GetCols(), 2);

//   for (int i = 0; i < matrixA.GetRows(); i++) {
//     for (int j = 0; j < matrixA.GetCols(); j++) {
//       EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
//     }
//   }
// }

TEST(OperatorAssignment, DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixB = matrixA;

  EXPECT_EQ(matrixB.GetRows(), matrixA.GetRows());
  EXPECT_EQ(matrixB.GetCols(), matrixA.GetCols());

  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      EXPECT_EQ(matrixB(i, j), matrixA(i, j));
    }
  }
}

// TEST(OperatorMoveAssignment, SelfMoveAssignment) {
//   double matrix1[2][2] = {{1, 2}, {3, 4}};

//   S21Matrix matrixA = S21Matrix(2, 2);
//   for (int i = 0; i < matrixA.GetRows(); i++) {
//     for (int j = 0; j < matrixA.GetCols(); j++) {
//       matrixA(i, j) = matrix1[i][j];
//     }
//   }

//   matrixA = std::move(matrixA);

//   EXPECT_EQ(matrixA.GetRows(), 2);
//   EXPECT_EQ(matrixA.GetCols(), 2);

//   for (int i = 0; i < matrixA.GetRows(); i++) {
//     for (int j = 0; j < matrixA.GetCols(); j++) {
//       EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
//     }
//   }
// }

TEST(OperatorPlusEqual, PlusEqual) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 3}, {4, 5}};
  double result[2][2] = {{3, 5}, {7, 9}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixA += matrixB;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorPlusEqual, PlusEqual_DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW({ matrixA += matrixB; }, std::logic_error);

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
    }
  }
}

TEST(OperatorMinusEqual, MinusEqual) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 3}, {4, 5}};
  double result[2][2] = {{-1, -1}, {-1, -1}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixA -= matrixB;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 3}, {4, 5}};
  double result[2][2] = {{10, 13}, {22, 29}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixA *= matrixB;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW({ matrixA *= matrixB; }, std::logic_error);

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_Scalar) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double scalar = 2;
  double result[2][2] = {{2, 4}, {6, 8}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= scalar;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_Scalar_Zero) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double scalar = 0;
  double result[2][2] = {{0, 0}, {0, 0}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= scalar;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_Scalar_Negative) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double scalar = -1;
  double result[2][2] = {{-1, -2}, {-3, -4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= scalar;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorParentheses, test1) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix matrixA = S21Matrix(3, 3);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix[i][j]);
    }
  }
}

TEST(OperatorParentheses, ThrowsOutOfRangeWhenIndexIsOutOfRange) {
  S21Matrix matrix(2, 2);

  // Ожидаем, что при попытке доступа к элементу с недопустимым индексом
  // будет выброшено исключение std::out_of_range
  EXPECT_THROW(matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, -1), std::out_of_range);
  EXPECT_THROW(matrix(2, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, 2), std::out_of_range);
}

// TEST(ConstMatrixTest, ConstMatrices) {
//   const S21Matrix mat = S21Matrix(3, 3);
//   EXPECT_EQ(mat(1, 1), 0);
// }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}