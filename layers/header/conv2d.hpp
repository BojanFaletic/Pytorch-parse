#pragma once

#include "matrix1.hpp"
#include "matrix3.hpp"
#include "matrix4.hpp"
#include <stdint.h>

class Conv2d {
  const char *name;

  matrix4 weights;
  matrix1 biases;

public:
  // normal with all options
  Conv2d();
  Conv2d(const char *name, uint32_t in_channels, uint32_t out_channels,
         uint32_t kernel);

  Conv2d(const char *name, matrix4 const &weights, matrix1 const &biases);
  ~Conv2d();

  matrix3 operator()(matrix3 const &in);
};