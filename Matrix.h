// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>


/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;

// Insert Matrix class here...
class Matrix
{
  matrix_dims _matrix_dims;
  float* _matrix_arr;


 public:
  Matrix(int rows, int cols);
  Matrix();
  Matrix(const Matrix& rhs);
  ~Matrix();
  int get_rows() const;
  int get_cols() const;
  Matrix& transpose();
  Matrix& vectorize();
  void plain_print() const;
  Matrix dot(const Matrix& matrix) const;
  float norm() const;
  float sum() const;

  int argmax() const;


  Matrix operator+(const Matrix& rhs) const;
  Matrix& operator=(const Matrix& rhs);
  Matrix& operator+=(const Matrix& rhs);
  Matrix operator*(const Matrix& rhs) const;
  Matrix operator*(const float& rhs) const;
  friend Matrix operator*(const float& c,const Matrix& matrix);
  float& operator()(const int& row,const int& col) const;
  float& operator[](const int& index) const;
  float& operator()(const int& row,const int& col);
  float& operator[](const int& index);
  friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
  friend std::istream& operator>>(std::istream& is, Matrix& matrix);

  Matrix rref() const;
};
#endif //MATRIX_H