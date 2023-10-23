#pragma once
#include "Vector.h"

class Matrix
{
public:
    float Mt[4][4];
    Matrix();
    void Standardize();
    Vector4 operator*(const Vector4 &rhs) const;
    Matrix operator*(const Matrix &rhs) const;
};