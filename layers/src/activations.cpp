#include "activations.hpp"

void ReLU(matrix &in, matrix &out) {
  for (uint32_t i = 0; i < in.n; i++) {
    for (uint32_t j = 0; j < in.m; j++) {
      out(i, j) = std::max(in(i, j), 0.F);
    }
  }
}