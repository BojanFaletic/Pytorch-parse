#pragma once

#include "matrix.hpp"
#include <stdint.h>

class Linear {
public:
  char const *name;

private:
  uint32_t const n_in, n_out;
  matrix weights, biases;

public:
  Linear(char const *name, uint32_t n_in, uint32_t n_out);

  void init_params(float *weight, uint32_t w_size, float *biases,
                   uint32_t b_size);

  void init_params(float *weight, uint32_t w_size);

  void forward(matrix &in, matrix &out) const;
};