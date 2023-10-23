#include <cmath>
#include "Triangle.h"

Triangle::Triangle(Vector3 a,Vector3 b,Vector3 c)
{
    P[0]=Vector2(a);
    P[1]=Vector2(b);
    P[2]=Vector2(c);
    Get_Edge();
}

Triangle Triangle::operator*(const int &Fac) const
{
    Triangle Ans;
    for (int i = 0; i < 3; i++)
        Ans.P[i] = P[i] * Fac;
    Ans.Get_Edge();
    return Ans;
}

void Triangle::Get_Edge()
{
    Edge[0] = P[1] - P[0];
    Edge[1] = P[2] - P[1];
    Edge[2] = P[0] - P[2];
}

bool Triangle::InTriangle(const Vector2 &Point)
{
    float f1 = (Point - P[0]) ^ Edge[0];
    float f2 = (Point - P[1]) ^ Edge[1];
    float f3 = (Point - P[2]) ^ Edge[2];
    if ((f1 > 0 && f2 > 0 && f3 >= 0) || (f1 < 0 && f2 < 0 && f3 < 0))
    {
        return true;
    }
    return false;
}
