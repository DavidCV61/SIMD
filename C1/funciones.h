#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <cstddef>

void CalcZ_Cpp(float *z, const float *x, const float *y, std::size_t n);
void CalcZ_Iavx(float *z, const float *x, const float *y, std::size_t n);

#endif
