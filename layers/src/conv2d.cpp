#include "conv2d.hpp"
#include <iostream>

Conv2d::Conv2d(const char *name, uint32_t in_channels, uint32_t out_channels,
               uint32_t kernel)
    : name{name} {
  weights = matrix4::random(out_channels, in_channels, kernel, kernel);
  biases = matrix1::random(out_channels);
}

Conv2d::Conv2d(const char *name, matrix4 const &weights, matrix1 const &biases)
    : name{name} {
  this->weights = weights;
  this->biases = biases;
}

void Conv2d::forward(matrix3 const &in, matrix3 &out) {
  uint32_t const kernel_x = weights.y;
  uint32_t const kernel_y = weights.z;
  uint32_t const in_channels = weights.n;
  uint32_t const out_channels = weights.m;
  uint32_t const image_y = in.n;
  uint32_t const image_x = in.m;

  uint32_t const kernel_border = kernel_y - 1;

  for (uint32_t y = 0; y < image_y - kernel_border; y++) {
    for (uint32_t x = 0; x < image_x - kernel_border; x++) {
      for (uint32_t co = 0; co < out_channels; co++) {
        float acc = biases(co);
        for (uint32_t ci = 0; ci < in_channels; ci++) {
          for (uint32_t ky = 0; ky < kernel_y; ky++) {
            for (uint32_t kx = 0; kx < kernel_x; kx++) {
              acc += weights(co, ci, ky + y, kx + x) * in(ci, y, x);
            }
          }
        }
        out(co, y, x) = acc;
      }
    }
  }
}
