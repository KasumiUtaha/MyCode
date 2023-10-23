#pragma once

class Color
{
public:
    float R, G, B;
    Color() = default;
    Color(float _R, float _G, float _B);
    Color operator+(const Color &rhs) const;
    Color operator-(const Color &rhs) const;
    Color operator/(const float &fac) const;
    void operator/=(const float &fac);
    Color operator*(float fac) const;
    void operator+=(const Color &rhs);
};