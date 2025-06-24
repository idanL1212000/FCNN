#include "MlpNetwork.h"

#define LAYER_1_NUM 0
#define LAYER_2_NUM 1
#define LAYER_3_NUM 2
#define LAYER_4_NUM 3
#define NUM_OF_MAT 4

MlpNetwork::MlpNetwork(const Matrix weights[NUM_OF_MAT] ,
                       const Matrix biases[NUM_OF_MAT])
: layer_1 (weights[LAYER_1_NUM],biases[LAYER_1_NUM],activation::relu),
layer_2 (weights[LAYER_2_NUM],biases[LAYER_2_NUM],activation::relu),
layer_3 (weights[LAYER_3_NUM],biases[LAYER_3_NUM],activation::relu),
layer_4 (weights[LAYER_4_NUM],biases[LAYER_4_NUM],activation::softmax){}

digit MlpNetwork::operator()(const Matrix& img) const
{
  Matrix input_mat = img;
  input_mat.vectorize();
  input_mat = layer_1(input_mat);
  input_mat = layer_2(input_mat);
  input_mat = layer_3(input_mat);
  input_mat = layer_4(input_mat);
  digit ans;
  ans.value = input_mat.argmax();
  ans.probability = input_mat[ans.value];
  return ans;
}
