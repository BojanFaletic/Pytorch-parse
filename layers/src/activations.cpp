#include "activations.hpp"
#include <algorithm>

matrix3 ReLU(matrix3 const &in) {
  matrix3 out = in;
  uint32_t idx = 0;
  std::for_each(out.mat, out.mat + out.size(),
                [&](float &f) { out.mat[idx++] = std::max(0.F, f); });
  return out;
}

matrix3 max_pool2d(matrix3 const &in, uint32_t stride) {
  if (stride == 0) {
    stride = 1;
  }
  matrix3 out = matrix3::zeros(in.z, in.n / stride, in.m / stride);

  for (uint32_t z = 0; z < in.z; z++) {
    for (uint32_t n = 0; n < in.n - stride; n += stride) {
      for (uint32_t m = 0; m < in.m - stride; m += stride) {
        // search in stride
        float max = in(z, n, m);
        for (uint32_t sy = 0; sy < stride; sy++) {
          for (uint32_t sx = 0; sx < stride; sx++) {
            max = std::max(max, in(z, n + sy, m + sx));
          }
        }
        out(z, n / stride, m / stride) = max;
      }
    }
  }
  return out;
}