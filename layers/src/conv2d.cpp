#include "conv2d.hpp"
#include <iostream>

Conv2d::Conv2d() {}

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

Conv2d::~Conv2d() {}

matrix3 Conv2d::operator()(matrix3 const &in) {

  uint32_t const kernel_x = weights.m;
  uint32_t const kernel_y = weights.n;
  uint32_t const in_channels = weights.z;
  uint32_t const out_channels = weights.y;
  uint32_t const image_y = in.n;
  uint32_t const image_x = in.m;

  uint32_t kernel_offset = kernel_x / 2;
  matrix3 out = matrix3::zeros(out_channels, image_y - kernel_offset*2,
                               image_x - kernel_offset*2);

  for (uint32_t y = kernel_offset; y < image_y - kernel_offset; y++) {
    for (uint32_t x = kernel_offset; x < image_x - kernel_offset; x++) {
      for (uint32_t co = 0; co < out_channels; co++) {
        float acc = biases(co);
        for (uint32_t ci = 0; ci < in_channels; ci++) {
          for (uint32_t ky = 0; ky < kernel_y; ky++) {
            for (uint32_t kx = 0; kx < kernel_x; kx++) {
              acc += weights(co, ci, ky, kx) * in(ci, y + ky, x + kx);
            }
          }
        }
        out(co, y - kernel_offset, x - kernel_offset) = 1;
      }
    }
  }
  return out;
}
