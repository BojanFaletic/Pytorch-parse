#pragma once

#include "matrix.hpp"
#include "matrix1.hpp"

#include <stdint.h>

class Linear {
public:
  char const *name;

private:
  matrix weights;
  matrix biases;

public:
  Linear(char const *name, uint32_t n_in, uint32_t n_out);
  Linear(char const *name, matrix const &weights, matrix1 const &biases);

  void forward(matrix &in, matrix &out) const;
};