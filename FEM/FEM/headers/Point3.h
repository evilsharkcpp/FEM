#pragma once
#include "FEMSettings.h"


class Point3 {
public:
   cType x, y, z;
   Point3(cType x, cType y, cType z) : x(x), y(y), z(z) {}
   Point3() : Point3(0, 0, 0) {}
   Point3(Point3& p) : x(p.x), y(p.y), z(p.z) {}
   Point3(Point3&& p) noexcept : x(p.x), y(p.y), z(p.z) { p.x = 0; p.y = 0; p.z = 0; }
};