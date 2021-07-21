#pragma once

#include <stdint.h>

typedef struct conv_cfg {
  uint32_t in_channels;
  uint32_t out_channels;
  uint32_t kernel_x;
  uint32_t kernel_y;
  uint32_t image_y;
  uint32_t image_x;
} conv_cfg;

class conv2d {
  const char *name;
  conv_cfg const param;

  float *weights;
  float *biases;

  void convolve(float *in, float *out);

public:
  // normal with all options
  conv2d(const char *name, conv_cfg const param);

  // load parameters from pkl file
  void init_parameters(float *weights, uint32_t w_size, float *biases,
                       uint32_t b_size);

  // use random parameters
  void init_parameters();

  void forward(float *in, float *out);
};