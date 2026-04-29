#include "Ch02_02.h"
#include "XmmVal.h"
#include <iostream>

using namespace std;

static void SubI32(void);
static void SubI64(void);

int main() {
  SubI32();
  SubI64();
  return 0;
}

static void SubI32() {

  XmmVal a, b, c;
  a.m_I32[0] = 1000000;
  b.m_I32[0] = 100;
  a.m_I32[1] = -30;
  b.m_I32[1] = 30000;
  a.m_I32[2] = 200;
  b.m_I32[2] = -200;
  a.m_I32[3] = 40000000;
  b.m_I32[3] = 5000;

  SubI32_Iavx(&c, &a, &b);

  cout << "\nResultados SubI32_Iavx" << endl;
  cout << "a: " << a.ToStringI32() << endl;
  cout << "b: " << b.ToStringI32() << endl;
  cout << "c: " << c.ToStringI32() << endl;
}

static void SubI64() {
  XmmVal a, b, c;
  a.m_I64[0] = 100000000000;
  b.m_I64[0] = 99;
  a.m_I64[1] = 200;
  b.m_I64[1] = 300000000000;

  SubI64_Iavx(&c, &a, &b);

  cout << "\nResultados SubI64_Iavx" << endl;
  cout << "a: " << a.ToStringI64() << endl;
  cout << "b: " << b.ToStringI64() << endl;
  cout << "c: " << c.ToStringI64() << endl;
}
