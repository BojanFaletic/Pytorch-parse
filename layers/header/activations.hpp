#pragma once
#include "matrix3.hpp"

void ReLU(matrix3 const &in, matrix3 &out);
void max_pool2d(matrix3 const &in, matrix3 &out, uint32_t stride);