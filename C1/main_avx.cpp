#include "funciones.h"
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  const size_t n = 100000000;
  vector<float> x(n, 1.5f);
  vector<float> y(n, 2.3f);
  vector<float> z(n);

  auto start = chrono::high_resolution_clock::now();
  CalcZ_Iavx(z.data(), x.data(), y.data(), n);
  CalcZ_Cpp(z.data(), x.data(), y.data(), n);
  auto end = chrono::high_resolution_clock::now();
  auto duration_avx = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "CalcZ_Iavx : " << duration_avx.count() << " microsegundos\n";

  cout << z[0] << ", " << z[n - 1] << endl;
  return 0;
}
