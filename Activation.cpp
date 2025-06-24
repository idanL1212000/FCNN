#include "Matrix.h"
#include "Activation.h"
#include <cmath>



Matrix activation::relu (const Matrix& matrix)
{
  Matrix out_put_mat = matrix;
  for (int i = 0; i < matrix.get_cols(); ++i)
  {
    for (int j = 0; j < matrix.get_rows(); ++j)
    {
      if (matrix(j,i) < 0){out_put_mat(j,i) = 0;}
    }
  }
  return out_put_mat;
}

Matrix activation::softmax (const Matrix & matrix)
{
  Matrix out_put_mat = matrix;
  float sum = 0;
  for (int i = 0; i < matrix.get_cols(); ++i)
  {
    for (int j = 0; j < matrix.get_rows(); ++j)
    {
      out_put_mat(j,i) = std::exp (matrix(j,i));
      sum += std::exp (matrix(j,i));
    }
  }
  out_put_mat = (1/sum)*out_put_mat;
  return out_put_mat;
}


