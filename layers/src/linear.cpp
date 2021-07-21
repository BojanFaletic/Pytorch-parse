#include "linear.hpp"
#include <iostream>

Linear::Linear(char const *name, uint32_t n_in, uint32_t n_out)
    : name{name}, n_in{n_in}, n_out{n_out} {};

void Linear::init_params(float *weight, uint32_t w_size, float *biases,
                         uint32_t b_size) {
  uint32_t n = n_in;
  uint32_t m = n_out;
  if (w_size != n_in * n_out) {
    std::cerr << "Weight sizes not match\n";
    exit(1);
  }
  if (m != b_size) {
    std::cerr << "Bias sizes not match\n";
    exit(1);
  }

  this->weights = matrix(weight, n, m);
  this->biases = matrix(biases, m, 1);
}

void Linear::init_params(float *weight, uint32_t w_size) {
  uint32_t n = n_in;
  uint32_t m = n_out;
  if (w_size != n_in * n_out) {
    std::cerr << "Weight sizes not match\n";
    exit(1);
  }

  this->weights = matrix(weight, n, m);
  this->biases = matrix::zeros(n_out, 1);
}

void Linear::init_params() {
  weights = matrix::ones(n_in, n_out);
  biases = matrix::zeros(n_out, 1);
}

void Linear::forward(matrix &in, matrix &out) const {
  out = in.dot_sparse(weights) + biases;
}