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
  CalcZ_Cpp(z.data(), x.data(), y.data(), n);
  auto end = chrono::high_resolution_clock::now();
  auto duration_cpp = chrono::duration_cast<chrono::microseconds>(end - start);

  cout << z[0] << ", " << z[n - 1] << endl;
  cout << "CalcZ_Cpp  : " << duration_cpp.count() << " microsegundos" << endl;

  return 0;
}
