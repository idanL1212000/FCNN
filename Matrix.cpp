#include "Matrix.h"
#include <iostream>
#include <cmath>

#define DOT_ERROR_MESSAGE "dot is only define on same size mat"
#define OPERATOR_ERROR_MESSAGE "this operator is only define on same size mat"
#define OUT_OF_RANGE_ERROR_MESSAGE "index out of range"
#define FILE_ERROR_MESSAGE "need more input"
#define MATRIX_DIM_ERROR_MESSAGE "need postive val"

#define PRINT_NUM 0.1



Matrix::Matrix(int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {throw std::length_error(MATRIX_DIM_ERROR_MESSAGE);}
  _matrix_dims.rows = rows;
  _matrix_dims.cols = cols;
  _matrix_arr = new float[rows * cols];
  for (int i = 0; i < rows * cols; i++)
  { _matrix_arr[i] = 0;}
}

Matrix::Matrix() : Matrix(1,1){}

Matrix::Matrix(const Matrix& rhs): Matrix(rhs._matrix_dims.rows, rhs
._matrix_dims.cols)
{
  for (int i = 0; i < _matrix_dims.rows*_matrix_dims.cols; i++)
  { _matrix_arr[i] = rhs._matrix_arr[i];}
}

Matrix::~Matrix ()
{
  delete[] _matrix_arr;
}

int Matrix::get_cols() const {return _matrix_dims.cols;}

int Matrix::get_rows() const {return _matrix_dims.rows;}

Matrix& Matrix::transpose()
{
  Matrix matrix = *this;
  _matrix_dims.cols = matrix._matrix_dims.rows;
  _matrix_dims.rows = matrix._matrix_dims.cols;
  for (int i = 0; i < _matrix_dims.rows; ++i)
  {
    for (int j = 0; j < _matrix_dims.cols; ++j)
    {
      _matrix_arr[i*_matrix_dims.cols + j] = matrix
          ._matrix_arr[j*_matrix_dims.rows + i];
    }
  }
  return *this;
}

Matrix& Matrix::vectorize()
{
  _matrix_dims.rows = _matrix_dims.cols*_matrix_dims.rows;
  _matrix_dims.cols = 1;
  return *this;
}

void Matrix::plain_print() const
{
  for (int i = 0; i < _matrix_dims.rows; ++i)
  {
    for (int j = 0; j < _matrix_dims.cols; ++j)
    {
      std::cout << _matrix_arr[i * _matrix_dims.cols + j] << " ";
    }
    std::cout << std::endl;
  }
}

Matrix Matrix::dot(const Matrix& matrix) const
{
  if (_matrix_dims.cols != matrix._matrix_dims.cols || _matrix_dims.rows !=
                                                     matrix._matrix_dims.rows)
  {throw std::length_error(DOT_ERROR_MESSAGE);}
  Matrix new_mat = matrix;
  for (int i = 0; i < _matrix_dims.cols*_matrix_dims.rows; ++i)
  {
    new_mat._matrix_arr[i] *= _matrix_arr[i];
  }
  return new_mat;
}

float Matrix::norm() const
{
  Matrix matrix = this->dot(*this);
  return sqrtf (matrix.sum());
}

float Matrix::sum() const
{
  float sum = 0;
  for (int i = 0; i < _matrix_dims.cols*_matrix_dims.rows; ++i)
  {
    sum += _matrix_arr[i];
  }
  return sum;
}

int Matrix::argmax() const
{
  float max = *_matrix_arr;
  int max_index = 0;
  for (int i = 1; i < _matrix_dims.cols*_matrix_dims.rows; ++i)
  {
    if (max < _matrix_arr[i])
    {
      max = _matrix_arr[i];
      max_index = i;
    }
  }
  return max_index;
}

Matrix Matrix::operator+(const Matrix& rhs) const
{
  if (_matrix_dims.cols != rhs._matrix_dims.cols || _matrix_dims.rows !=
                                                     rhs._matrix_dims.rows)
  {throw std::length_error(OPERATOR_ERROR_MESSAGE);}

  Matrix new_mat = *this;
  for (int i = 0; i < _matrix_dims.cols*_matrix_dims.rows; ++i)
  {
    new_mat._matrix_arr[i] += rhs._matrix_arr[i];
  }
  return new_mat;
}

Matrix& Matrix::operator=(const Matrix& rhs)
    {
  float* old_mat_lhs = _matrix_arr;
  Matrix good_rhs = rhs;
  _matrix_arr = new float[rhs._matrix_dims.cols * rhs._matrix_dims.rows];
  _matrix_dims.cols = good_rhs._matrix_dims.cols;
  _matrix_dims.rows = good_rhs._matrix_dims.rows;
  for (int i = 0; i < _matrix_dims.rows*_matrix_dims.cols; i++)
  {_matrix_arr[i] = good_rhs._matrix_arr[i];}
  delete[] old_mat_lhs;
  return *this;
    }

Matrix& Matrix::operator+=(const Matrix& rhs)
    {
      if (_matrix_dims.cols != rhs._matrix_dims.cols || _matrix_dims.rows !=
                                                         rhs._matrix_dims.rows)
      {throw std::length_error(OPERATOR_ERROR_MESSAGE);}

      for (int i = 0; i < _matrix_dims.cols*_matrix_dims.rows; ++i)
      {
        _matrix_arr[i] += rhs._matrix_arr[i];
      }
      return *this;
    }

Matrix Matrix::operator*(const Matrix& rhs) const
{
  if (_matrix_dims.cols != rhs._matrix_dims.rows)
  {throw std::length_error(OPERATOR_ERROR_MESSAGE);}

  Matrix new_mat(_matrix_dims.rows, rhs._matrix_dims.cols);
  for (int i = 0; i < new_mat._matrix_dims.rows; ++i)
  {
    for (int j = 0; j < new_mat._matrix_dims.cols; ++j)
    {
      float new_value = 0;
      for (int k = 0; k < _matrix_dims.cols; ++k)
      {
        new_value += _matrix_arr[i * _matrix_dims.cols + k] * rhs
            ._matrix_arr[k * rhs._matrix_dims.cols + j];
      }
      new_mat._matrix_arr[i*new_mat._matrix_dims.cols + j] = new_value;
    }
  }
  return new_mat;
}

Matrix Matrix::operator*(const float& rhs) const
{
  Matrix new_mat = *this;
  for (int i = 0; i < _matrix_dims.cols*_matrix_dims.rows; ++i)
  {
    new_mat._matrix_arr[i] *= rhs;
  }
  return new_mat;
}

Matrix operator*(const float& c,const Matrix& matrix)
{
  Matrix new_mat = matrix;
  for (int i = 0; i < matrix._matrix_dims.cols*matrix._matrix_dims.rows; ++i)
  {
    new_mat._matrix_arr[i] *= c;
  }
  return new_mat;
}

float& Matrix::operator()(const int& row,const int& col) const
{
  if (row >= _matrix_dims.rows || col >= _matrix_dims.cols || row < 0
  || col < 0)
  {throw std::out_of_range(OUT_OF_RANGE_ERROR_MESSAGE);}
  return _matrix_arr[row*_matrix_dims.cols + col];
}

float& Matrix::operator[](const int& index) const
{
  if (index < 0 || index >= _matrix_dims.rows*_matrix_dims.cols)
  {throw std::out_of_range(OUT_OF_RANGE_ERROR_MESSAGE);}
  return _matrix_arr[index];
}

float& Matrix::operator()(const int& row,const int& col)
{
  if (row >= _matrix_dims.rows || col >= _matrix_dims.cols || row < 0
      || col < 0)
  {throw std::out_of_range(OUT_OF_RANGE_ERROR_MESSAGE);}
  return _matrix_arr[row*_matrix_dims.cols + col];
}

float& Matrix::operator[](const int& index)
{
  if (index < 0 || index >= _matrix_dims.rows*_matrix_dims.cols)
  {throw std::out_of_range(OUT_OF_RANGE_ERROR_MESSAGE);}
  return _matrix_arr[index];
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
  for (int i = 0; i < matrix._matrix_dims.rows; ++i)
  {
    for (int j = 0; j < matrix._matrix_dims.cols; ++j)
    {
      if (matrix._matrix_arr[i * matrix._matrix_dims.cols + j] > PRINT_NUM)
      {os << "**";}
      else
      {os << "  ";}
    }
    os << std::endl;
  }
  return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix)
{
  Matrix old_mat = matrix;
  int i = 0;
  for (;i < matrix.get_rows() * matrix.get_cols() && is.good(); ++i)
  {
    is.read ((char *) &matrix._matrix_arr[i], sizeof (float ));
  }
  if (i !=  matrix.get_rows() * matrix.get_cols())
  {
    matrix = old_mat;
    throw std::runtime_error(FILE_ERROR_MESSAGE);
  }
  return is;
}




Matrix Matrix::rref () const
{
  Matrix matrix = *this;
  for (int i = 0; i < _matrix_dims.rows; ++i)
  {
    int j=i;
    for (; j < _matrix_dims.rows &&
    matrix._matrix_arr[j*_matrix_dims.cols + i] == 0; ++j)
    {}
    if (j < _matrix_dims.rows)
    {
      float mult = matrix._matrix_arr[j*_matrix_dims.cols + i];
      for (int k = i; k < _matrix_dims.cols; ++k)
      {
        matrix._matrix_arr[j*_matrix_dims.cols + k] /= mult;
        float temp = matrix._matrix_arr[j*_matrix_dims.cols + k];
        matrix._matrix_arr[j*_matrix_dims.cols + k] = matrix
            ._matrix_arr[i*_matrix_dims.cols + k];
        matrix._matrix_arr[i*_matrix_dims.cols + k] = temp;
      }
      for (int k = 0; k < _matrix_dims.rows; ++k)
      {
        if (matrix._matrix_arr[k * _matrix_dims.cols + i]!=0 && k!=i)
        {
          float mult = matrix._matrix_arr[k * _matrix_dims.cols + i];
          for (int l = i; l < _matrix_dims.cols; ++l)
          {
            matrix.plain_print();
            matrix._matrix_arr[k * _matrix_dims.cols + l] -= mult *
                matrix._matrix_arr[i * _matrix_dims.cols + l];
          }
        }
      }
    }
  }
  return matrix;
}





