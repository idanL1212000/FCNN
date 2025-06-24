
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

typedef Matrix my_func(const Matrix& matrix);
typedef Matrix (*activation_func_pointer)(const Matrix& matrix);

// Insert Activation class here...
namespace activation
{
    my_func relu;
    my_func softmax;
}

#endif //ACTIVATION_H