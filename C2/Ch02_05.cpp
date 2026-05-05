#include "Ch02_05.h"
#include <iostream>

static void ShiftU16(void);

int main() {
  ShiftU16();
  return 0;
}

static void ShiftU16(void) {
  XmmVal a, c;
  const int count_l = 8;
  const int count_r = 4;
  const char endl = '\n';

  a.m_U16[0] = 0x1234;
  a.m_U16[1] = 0xFFB0;
  a.m_U16[2] = 0x00CC;
  a.m_U16[3] = 0x8080;
  a.m_U16[4] = 0x00FF;
  a.m_U16[5] = 0xAAAA;
  a.m_U16[6] = 0x0F0F;
  a.m_U16[7] = 0x0101;

  SllU16_Iavx(&c, &a, count_l);
  cout << "\nResultados para SllU16_Aavx - count = " << count_l << endl;
  cout << "a: " << a.ToStringX16() << endl;
  cout << "c: " << c.ToStringX16() << endl;

  SrlU16_Iavx(&c, &a, count_r);
  cout << "\nResultados para SrlU16_Aavx - count = " << count_r << endl;
  cout << "a: " << a.ToStringX16() << endl;
  cout << "c: " << c.ToStringX16() << endl;

  SraU16_Iavx(&c, &a, count_r);
  cout << "\nResultados para SraU16_Aavx - count = " << count_r << endl;
  cout << "a: " << a.ToStringX16() << endl;
  cout << "c: " << c.ToStringX16() << endl;
}
