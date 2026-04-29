#pragma once
#include "XmmVal.h"

extern void AddI16_Iavx(XmmVal *c1, XmmVal *c2, const XmmVal *a,
                        const XmmVal *b);
extern void AddI16_Uavx(XmmVal *c1, XmmVal *c2, const XmmVal *a,
                        const XmmVal *b);
