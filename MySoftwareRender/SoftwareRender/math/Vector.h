#pragma once

class Vector3
{
public:
    float x, y, z;
    Vector3() = default;
    Vector3(float _x, float _y, float _z);
    Vector3 operator+(const Vector3 &rhs) const;
    Vector3 operator-(const Vector3 &rhs) const;
    Vector3 operator-() const;
    float operator*(const Vector3 &rhs) const;
    Vector3 operator*(const int &Fac) const;
    Vector3 operator^(const Vector3 &rhs) const;
    void Standardize();
};

class Vector2
{
public:
    float x, y;
    Vector2() = default;
    Vector2(float _x, float _y);
    Vector2(const Vector3 &rhs);
    Vector2 operator+(const Vector2 &rhs) const;
    Vector2 operator-(const Vector2 &rhs) const;
    float operator*(const Vector2 &rhs) const;
    Vector2 operator*(const int &Fac) const;
    float operator^(const Vector2 &rhs) const;
    void Standardize();
};

class Vector4
{
public:
    float x, y, z, w;
    Vector4() = default;
    Vector4(float _x, float _y, float _z, float _w);
    Vector4(const Vector3 &rhs);
};
