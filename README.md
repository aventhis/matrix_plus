# s21_matrix_plus

## Introduction

`s21_matrix_plus` is a custom C++ library designed to perform various matrix operations. This project demonstrates object-oriented design principles and operator overloading to create an intuitive interface for handling matrices. The library allows you to work with matrices of arbitrary size and perform common operations such as addition, subtraction, multiplication, and more.

### Features

- Matrix creation and initialization.
- Addition, subtraction, and multiplication of matrices.
- Transposition and inversion of matrices.
- Calculation of determinants and matrix minors.
- Operator overloading for an intuitive API (e.g., `+`, `-`, `*`, `==`, etc.).
- Support for scalar multiplication and comparison.

## Matrix Operations Overview

| No. | Function | Description |
| --- | -------- | ----------- |
| 1 | `Matrix operator+(const Matrix &other)` | Adds two matrices |
| 2 | `Matrix operator-(const Matrix &other)` | Subtracts one matrix from another |
| 3 | `Matrix operator*(const Matrix &other)` | Multiplies two matrices |
| 4 | `Matrix operator==(const Matrix &other)` | Checks if two matrices are equal |
| 5 | `Matrix transpose()` | Returns the transposed matrix |
| 6 | `Matrix inverse()` | Returns the inverse of the matrix |
| 7 | `double determinant()` | Calculates the determinant of the matrix |
| 8 | `Matrix calcMinor(int row, int col)` | Calculates the minor of the matrix |
| 9 | `Matrix operator*(double scalar)` | Multiplies the matrix by a scalar |

## Part 1. Implementation Details

The library was developed in C++ following OOP principles to provide clear and reusable code. Below are some key details:

- The code adheres to the C++11 standard.
- The core logic is implemented in the `src` directory.
- The solution uses operator overloading to allow intuitive operations with matrices (e.g., `+`, `-`, `*`).
- The library handles dynamic memory allocation and ensures proper resource management (RAII).
- Full unit tests are provided to ensure the correctness of all matrix operations.
- A Makefile is provided to automate the build process and testing.

## Build Instructions

To build and run the project, follow these steps:

1. Clone the repository and navigate to the project folder:

    ```bash
    git clone <repository_url>
    cd <project_folder>
    ```

2. Use the provided Makefile to build the project:

    ```bash
    make all
    ```

## Makefile Targets

- **make all**: This target compiles all source files and builds the matrix library.
- **make clean**: This target removes all generated object files and executables.
- **make test**: This target compiles and runs unit tests to validate the functionality of the library.
- **make gcov_report**: This target generates a code coverage report in HTML format using `gcov`.

## Conclusion

The `s21_matrix_plus` project provides a robust and intuitive interface for matrix operations, demonstrating the power of C++ and OOP design principles. The operator overloading features make matrix manipulations easy and natural for developers.
