#include <cmath>
#include "Vector.h"

Vector2::Vector2(float _x = 0, float _y = 0) : x(_x), y(_y)
{
}

Vector2::Vector2(const Vector3 &rhs)
{
    x=rhs.x;
    y=rhs.y;
}

Vector2 Vector2::operator+(const Vector2 &rhs) const
{
    return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2 &rhs) const
{
    return Vector2(x - rhs.x, y - rhs.y);
}

float Vector2::operator*(const Vector2 &rhs) const
{
    return x * rhs.x + y * rhs.y;
}

Vector2 Vector2::operator*(const int &Fac) const
{
    return Vector2(x * Fac, y * Fac);
}

float Vector2::operator^(const Vector2 &rhs) const
{
    return x * rhs.y - y * rhs.x;
}

void Vector2::Standardize()
{
    float Sca = sqrt(x * x + y * y);
    x /= Sca;
    y /= Sca;
}

Vector3::Vector3(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z){};


Vector3 Vector3::operator+(const Vector3 &rhs) const
{
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3 Vector3::operator-(const Vector3 &rhs) const
{
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

float Vector3::operator*(const Vector3 &rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3 Vector3::operator*(const int &Fac) const
{
    return Vector3(x * Fac, y * Fac, z * Fac);
}

Vector3 Vector3::operator^(const Vector3 &rhs) const
{
    return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

void Vector3::Standardize()
{
    float Sca = sqrt(x * x + y * y + z * z);
    x /= Sca;
    y /= Sca;
    z /= Sca;
}

Vector4::Vector4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) : x(_x), y(_y), z(_z), w(_w){};
Vector4::Vector4(const Vector3 &rhs) { x = rhs.x, y = rhs.y, z = rhs.z, w = 1.0; }
