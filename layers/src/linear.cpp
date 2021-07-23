#include "linear.hpp"
#include <iostream>

Linear::Linear(char const *name, uint32_t n_in, uint32_t n_out) : name{name} {
  weights = matrix::random(n_in, n_out);
  biases = matrix::random(1, n_out);
}

Linear::Linear(char const *name, matrix const &weights, matrix1 const &biases)
    : name{name} {
  this->weights = weights;
  this->biases = biases.unsqueeze(0);
}


void Linear::forward(matrix &in, matrix &out) const {
  out = in.dot_sparse(weights) + biases;
}