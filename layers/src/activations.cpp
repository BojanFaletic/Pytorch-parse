#include "activations.hpp"
#include <algorithm>

void ReLU(matrix3 const &in, matrix3 &out) {
  uint32_t idx = 0;
  std::for_each(in.mat, in.mat + in.size(),
                [&](float &f) { out.mat[idx++] = std::max(0.F, f); });
}

void max_pool2d(matrix3 const &in, matrix3 &out, uint32_t stride) {
  for (uint32_t z = 0; z < in.z; z++) {
    for (uint32_t n = 0; n < in.n-stride; n += stride) {
      for (uint32_t m = 0; m < in.m-stride; m += stride) {
        // search in stride
        float max = in(z, n, m);
        for (uint32_t sy = 0; sy < stride; sy++) {
          for (uint32_t sx = 0; sx < stride; sx++) {
            max = std::max(max, in(z, n+sy, m+sx));
          }
        }
        out(z, n, m) = max;
      }
    }
  }
}