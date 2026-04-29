#include "Ch02_01.h"
#include "XmmVal.h"
#include <iostream>

using namespace std;

static void AddI16(void);
static void AddU16(void);

int main() {

  AddI16();
  AddU16();
  return 0;
}

static void AddI16(void) {
  XmmVal a, b, c1, c2;

  a.m_I16[0] = 10;
  b.m_I16[0] = 100;
  a.m_I16[1] = 200;
  b.m_I16[1] = -200;
  a.m_I16[2] = 30;
  b.m_I16[2] = 32760;
  a.m_I16[3] = -32766;
  b.m_I16[3] = -400;
  a.m_I16[4] = 50;
  b.m_I16[4] = 500;
  a.m_I16[5] = 60;
  b.m_I16[5] = -600;
  a.m_I16[6] = 32000;
  b.m_I16[6] = 1200;
  a.m_I16[7] = -3200;
  b.m_I16[7] = -950;

  AddI16_Iavx(&c1, &c2, &a, &b);

  cout << "\n Resultados para AddI16_Iavx - Wraparound" << endl;
  cout << "a: " << a.ToStringI16() << endl;
  cout << "b: " << b.ToStringI16() << endl;
  cout << "c1: " << c1.ToStringI16() << endl;

  cout << "\n Resultados para AddI16_Iavx - Saturado" << endl;
  cout << "a: " << a.ToStringI16() << endl;
  cout << "b: " << b.ToStringI16() << endl;
  cout << "c2: " << c2.ToStringI16() << endl;
}

static void AddU16() {

  XmmVal a, b, c1, c2;

  a.m_U16[0] = 10;
  b.m_U16[0] = 100;
  a.m_U16[1] = 200;
  b.m_U16[1] = 200;
  a.m_U16[2] = 300;
  b.m_U16[2] = 65530;
  a.m_U16[3] = 32766;
  b.m_U16[3] = 40000;
  a.m_U16[4] = 50;
  b.m_U16[4] = 500;
  a.m_U16[5] = 20000;
  b.m_U16[5] = 25000;
  a.m_U16[6] = 32000;
  b.m_U16[6] = 1200;
  a.m_U16[7] = 32000;
  b.m_U16[7] = 50000;

  AddI16_Uavx(&c1, &c2, &a, &b);

  cout << "\n Resultados para AddU16_Uavx - Wraparound" << endl;
  cout << "a: " << a.ToStringU16() << endl;
  cout << "b: " << b.ToStringU16() << endl;
  cout << "c1: " << c1.ToStringU16() << endl;

  cout << "\n Resultados para AddU16_Uavx - Saturado" << endl;
  cout << "a: " << a.ToStringU16() << endl;
  cout << "b: " << b.ToStringU16() << endl;
  cout << "c2: " << c2.ToStringU16() << endl;
}
