#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

// Insert Dense class here...
class Dense
{
  Matrix _weights;
  Matrix _bias;
  activation_func_pointer _activation_func;
 public:
  Dense( Matrix weights, Matrix bias,
        activation_func_pointer activation_function);
  const Matrix& get_weights() const;
  const Matrix& get_bias() const;
  activation_func_pointer get_activation() const;
  Matrix operator()(const Matrix& input_vec) const;
};

#endif //DENSE_H
