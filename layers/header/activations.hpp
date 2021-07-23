#pragma once
#include "matrix3.hpp"

matrix3 ReLU(matrix3 const &in);
matrix3 max_pool2d(matrix3 const &in, uint32_t stride);