#include "Dense.h"

Dense::Dense( Matrix weights, Matrix bias,
             activation_func_pointer activation_function):
             _weights(weights),
             _bias(bias),
             _activation_func(activation_function)
{}

const Matrix& Dense::get_weights() const
{return _weights;}

const Matrix& Dense::get_bias() const
{return _bias;}

activation_func_pointer Dense::get_activation() const
{return _activation_func;}

Matrix Dense::operator()(const Matrix& input_vec) const
{
  Matrix out_put = (_weights * input_vec) +_bias;
  return _activation_func(out_put);
}