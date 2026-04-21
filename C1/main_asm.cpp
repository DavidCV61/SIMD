#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

extern "C" void CalcZ_Aavx(float *z, const float *x, const float *y, size_t n);

int main() {
  const size_t n = 100000000;
  vector<float> x(n, 1.5f);
  vector<float> y(n, 2.3f);
  vector<float> z(n);

  auto start = chrono::high_resolution_clock::now();
  CalcZ_Aavx(z.data(), x.data(), y.data(), n);
  auto end = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Resultado: " << z[0] << ", " << z[n - 1] << endl;
  cout << "CalcZ_Aavx : " << duration.count() << " microsegundos" << endl;

  return 0;
}
