#include "Ch02_04.h"
#include <iostream>

using namespace std;

static void BitwiseLogical(void);

int main() {
  BitwiseLogical();
  return 0;
}

static void BitwiseLogical(void) {
  XmmVal a, b, c;

  a.m_U16[0] = 0x1234;
  b.m_U16[0] = 0xFF00;
  a.m_U16[1] = 0xABDC;
  b.m_U16[1] = 0x00FF;
  a.m_U16[2] = 0xAA55;
  b.m_U16[2] = 0xAAAA;
  a.m_U16[3] = 0x1111;
  b.m_U16[3] = 0x5555;
  a.m_U16[4] = 0xFFFF;
  b.m_U16[4] = 0x8000;
  a.m_U16[5] = 0x7F7F;
  b.m_U16[5] = 0x7FFF;
  a.m_U16[6] = 0x9876;
  b.m_U16[6] = 0xF0F0;
  a.m_U16[7] = 0x7F00;
  b.m_U16[7] = 0x0880;

  AndU16_Iavx(&c, &a, &b);
  cout << "\nResultados para AndU16_Iavx\n";
  cout << "a: " << a.ToStringX16() << endl;
  cout << "b: " << b.ToStringX16() << endl;
  cout << "c: " << c.ToStringX16() << endl;

  OrU16_Iavx(&c, &a, &b);
  cout << "\nResultados para OrU16_Iavx\n";
  cout << "a: " << a.ToStringX16() << endl;
  cout << "b: " << b.ToStringX16() << endl;
  cout << "c: " << c.ToStringX16() << endl;

  XorU16_Iavx(&c, &a, &b);
  cout << "\nResultados para XorU16_Iavx\n";
  cout << "a: " << a.ToStringX16() << endl;
  cout << "b: " << b.ToStringX16() << endl;
  cout << "c: " << c.ToStringX16() << endl;
}
