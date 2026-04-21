#include <cstddef>
#include <immintrin.h>

void CalcZ_Cpp(float *z, const float *x, const float *y, std::size_t n) {
  for (std::size_t i = 0; i < n; ++i)
    z[i] = x[i] + y[i];
}

void CalcZ_Iavx(float *z, const float *x, const float *y, std::size_t n) {
  std::size_t i = 0;
  const std::size_t num_simd_elements = 8;

  for (; n - i >= num_simd_elements; i += num_simd_elements) {
    __m256 x_vals = _mm256_loadu_ps(&x[i]);
    __m256 y_vals = _mm256_loadu_ps(&y[i]);
    __m256 z_vals = _mm256_add_ps(x_vals, y_vals);
    _mm256_storeu_ps(&z[i], z_vals);
  }

  for (; i < n; ++i)
    z[i] = x[i] + y[i];
}
