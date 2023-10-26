#pragma once
#include "Color.h"
#include "math/Matrix.h"
#include "Geometry/Triangle.h"
#include "Geometry/Cube.h"

class SoftwareRender
{
public:
    float fov, aspect, near, far;
    Matrix WTI, ITP, PTS, MVP;
    Vector3 Camera, CameraPoint, UP;
    int SSAAFactor;
    int Width, Height;
    int length;
    Triangle Tmp;
    Color frame_buffer[3200][2400];
    Color pixel[800][600];
    float depth_buffer[3200][2400];
    float dep[3];
    SoftwareRender();
    Color color_base[3];
    Color Render(int x, int y);
    float DepthTest(Vector2 point, Triangle transformed);
    Color ColorTest(Vector2 point, Triangle transformed);
    Color SSAA(int x, int y,bool type);
    void DrawTriangle(Triangle Tri);
    void PPM();
    void GetMatrix();
    Vector3 MVPTransformation(Vector3 vec);
    void DrawCube(Cube cube);
};
