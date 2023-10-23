#include "Color.h"
#include <cmath>

Color::Color(float _R = 0, float _G = 0, float _B = 0) : R(_R), G(_G), B(_B){};

Color Color::operator+(const Color &rhs) const
{
    return Color(R + rhs.R, G + rhs.G, B + rhs.B);
}

Color Color::operator-(const Color &rhs) const
{
    return Color(R - rhs.R, G - rhs.G, B - rhs.B);
}

Color Color::operator/(const float &fac) const
{
    return Color(R/fac,G/fac,B/fac);
}

void Color::operator /=(const float &fac)
{
   R/=fac;
   G/=fac;
   B/=fac;
}

Color Color::operator*(float fac) const
{
    return Color(R * fac, G * fac, B * fac);
}

void Color::operator+=(const Color& rhs)
{
    R+=rhs.R;
    G+=rhs.G;
    B+=rhs.B;
}