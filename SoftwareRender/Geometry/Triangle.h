#pragma once
#include "../math/Vector.h"

class Triangle
{
public:
    Vector2 P[3], Edge[3];
    Triangle()=default;
    Triangle(Vector3 a,Vector3 b,Vector3 c);

    Triangle operator*(const int &Fac) const;

    inline void Get_Edge();

    bool InTriangle(const Vector2 &Point);
};