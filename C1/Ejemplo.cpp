#include <chrono>
#include <immintrin.h>
#include <iostream>
#include <vector>

using namespace std;

void CalcZ_Cpp(float *z, const float *x, const float *y, size_t n) {
  for (size_t i = 0; i < n; ++i)
    z[i] = x[i] + y[i];
}

void CalcZ_Iavx(float *z, const float *x, const float *y, size_t n) {
  size_t i = 0;
  const size_t num_simd_elements = 8;

  for (; n - i >= num_simd_elements; i += num_simd_elements) {
    __m256 x_vals = _mm256_loadu_ps(&x[i]);
    __m256 y_vals = _mm256_loadu_ps(&y[i]);
    __m256 z_vals = _mm256_add_ps(x_vals, y_vals);
    _mm256_storeu_ps(&z[i], z_vals);
  }

  for (; i < n; ++i)
    z[i] = x[i] + y[i];
}

int main() {
  const size_t n = 100000000;
  vector<float> x(n, 1.5f);
  vector<float> y(n, 2.3f);
  vector<float> z1(n), z2(n);

  auto start = chrono::high_resolution_clock::now();
  CalcZ_Cpp(z1.data(), x.data(), y.data(), n);
  auto end = chrono::high_resolution_clock::now();
  auto duration_cpp = chrono::duration_cast<chrono::microseconds>(end - start);

  start = chrono::high_resolution_clock::now();
  CalcZ_Iavx(z2.data(), x.data(), y.data(), n);
  end = chrono::high_resolution_clock::now();
  auto duration_avx = chrono::duration_cast<chrono::microseconds>(end - start);

  cout << "CalcZ_Cpp: " << z1[n - 1] << " | " << "CalcZ_Iavx: " << z2[n - 2]
       << endl;
  cout << "Tamaño de los arreglos: " << n << "\n";
  cout << "CalcZ_Cpp  : " << duration_cpp.count() << " microsegundos\n";
  cout << "CalcZ_Iavx : " << duration_avx.count() << " microsegundos\n";

  return 0;
}
