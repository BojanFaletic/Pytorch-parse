#include "conv2d.hpp"
#include <iostream>

conv2d::conv2d(const char *name, conv_cfg const param)
    : name{name}, param{param} {}

void conv2d::init_parameters() {
  uint32_t size_w =
      param.in_channels * param.out_channels * param.kernel_y * param.kernel_x;

  weights = new float[size_w];
  biases = new float[param.out_channels];
}

void conv2d::convolve(float *in, float *out) {
  uint32_t img_size = param.image_y * param.image_x;
  uint32_t kern_size = param.kernel_y * param.kernel_x;
  uint32_t kernel_border = param.kernel_y - 1;

  for (uint32_t y = 0; y < param.image_y - kernel_border; y++) {
    for (uint32_t x = 0; x < param.image_x - kernel_border; x++) {
      for (uint32_t co = 0; co < param.out_channels; co++) {
        float acc = biases[co];
        for (uint32_t ci = 0; ci < param.in_channels; ci++) {
          for (uint32_t ky = 0; ky < param.kernel_y; ky++) {
            for (uint32_t kx = 0; kx < param.kernel_x; kx++) {
              uint32_t inp_addr =
                  ci * img_size + (y + ky) * param.image_x + (x + kx);
              uint32_t w_addr = co * kern_size * param.in_channels +
                                ci * kern_size + ky * param.kernel_x + kx;
              acc += in[inp_addr] * weights[w_addr];
            }
          }
        }
        uint32_t out_addr = co * img_size + y * param.image_x + x;
        out[out_addr] = acc;
      }
    }
  }
}

void conv2d::forward(float *in, float *out) { convolve(in, out); }

void conv2d::init_parameters(float *weights, uint32_t w_size, float *biases,
                             uint32_t b_size) {
  uint32_t expected_weight_size =
      param.in_channels * param.out_channels * param.kernel_x * param.kernel_y;
  if (w_size != expected_weight_size) {
    std::cerr << "Unable to load weight parameters\n";
    exit(1);
  }

  if (b_size != param.out_channels) {
    std::cerr << "Unable to load bias parameters\n";
    exit(1);
  }

  this->weights = weights;
  this->biases = biases;
}