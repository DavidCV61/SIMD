#include "Ch02_03.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

static void MulI16(void);
static void MulI32a(void);
static void MulI32b(void);

int main() {
  string sep(75, '-');

  MulI16();
  cout << "\n" << sep << endl;
  MulI32a();
  cout << "\n" << sep << endl;
  MulI32b();
  return 0;
}

static void MulI16(void) {
  XmmVal a, b, c[2];

  a.m_I16[0] = 10;
  b.m_I16[0] = -5;
  a.m_I16[1] = 3000;
  b.m_I16[1] = 100;
  a.m_I16[2] = -2000;
  b.m_I16[2] = -9000;
  a.m_I16[3] = 42;
  b.m_I16[3] = 1000;
  a.m_I16[4] = -5000;
  b.m_I16[4] = 25000;
  a.m_I16[5] = 8;
  b.m_I16[5] = 16384;
  a.m_I16[6] = 10000;
  b.m_I16[6] = 3500;
  a.m_I16[7] = -60;
  b.m_I16[7] = 6000;

  MulI16_Iavx(c, &a, &b);

  cout << "\nResultados para  MulI16_Iavx" << endl;
  for (size_t i = 0; i < 8; i++) {
    cout << "a[" << i << "]: " << setw(8) << a.m_I16[i] << "  ";
    cout << "b[" << i << "]: " << setw(8) << b.m_I16[i] << "  ";

    if (i < 4) {
      cout << "c[0][" << i << "]: ";
      cout << setw(12) << c[0].m_I32[i] << endl;
    } else {
      cout << "c[1][" << i - 4 << "]: ";
      cout << setw(12) << c[1].m_I32[i - 4] << endl;
    }
  }
}

static void MulI32a(void) {
  XmmVal a, b, c;

  a.m_I32[0] = 10;
  b.m_I32[0] = -500;
  a.m_I32[1] = 3000;
  b.m_I32[1] = 100;
  a.m_I32[2] = -2000;
  b.m_I32[2] = -12000;
  a.m_I32[3] = 4200;
  b.m_I32[3] = 1000;

  MulI32a_Iavx(&c, &a, &b);

  cout << "\nResultados para MulI32a_Iavx" << endl;
  for (size_t i = 0; i < 4; i++) {
    cout << "a[" << i << "]: " << setw(10) << a.m_I32[i] << "  ";
    cout << "b[" << i << "]: " << setw(10) << b.m_I32[i] << "  ";
    cout << "c[" << i << "]: " << setw(10) << c.m_I32[i] << endl;
  }
}

static void MulI32b(void) {
  XmmVal a, b, c[2];

  a.m_I32[0] = 10;
  b.m_I32[0] = -500;
  a.m_I32[1] = 3000;
  b.m_I32[1] = 100;
  a.m_I32[2] = -40000;
  b.m_I32[2] = -120000;
  a.m_I32[3] = 4200;
  b.m_I32[3] = 1000;

  MulI32b_Iavx(c, &a, &b);

  cout << "\nResultados para MulI32b_Iavx" << endl;
  for (size_t i = 0; i < 4; i++) {
    cout << "a[" << i << "]: " << setw(10) << a.m_I32[i] << "  ";
    cout << "b[" << i << "]: " << setw(10) << b.m_I32[i] << "  ";

    if (i < 2) {
      cout << "c[0][" << i << "]: ";
      cout << setw(14) << c[0].m_I64[i] << endl;

    } else {
      cout << "c[1][" << i - 2 << "]: ";
      cout << setw(14) << c[1].m_I64[i - 2] << endl;
    }
  }
}
