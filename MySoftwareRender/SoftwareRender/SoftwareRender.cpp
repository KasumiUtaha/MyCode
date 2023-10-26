#include "SoftwareRender.h"
#include <iostream>
#include <cmath>
using std::cout;
using std::max;
using std::min;

SoftwareRender::SoftwareRender()
{
    SSAAFactor = 4;
    length = 50;
    for (int i = 0; i < 3200; i++)
    {
        for (int j = 0; j < 2400; j++)
        {
            depth_buffer[i][j] = 1e9;
            frame_buffer[i][j] = Color(255, 255, 255);
        }
    }
    for (int i = 0; i < 800; i++)
    {
        for (int j = 0; j < 600; j++)
        {
            pixel[i][j] = Color(255, 255, 255);
        }
    }
    Width = 800;
    Height = 600;
    Camera = Vector3(-4, 5, 8);
    // 8,5,-4
    CameraPoint = Vector3(0, 0, 0);
    UP = Vector3(0, 1, 0);
    fov = acos(-1.0) / 3;
    aspect = 4.0 / 3.0;
    near = 0.1;
    far = 100;
    GetMatrix();
}

Color SoftwareRender::Render(int x, int y)
{
}

float SoftwareRender::DepthTest(Vector2 point, Triangle triangle)
{
    float a = (-(point.x - triangle.P[1].x) * (triangle.P[2].y - triangle.P[1].y) + (point.y - triangle.P[1].y) * (triangle.P[2].x - triangle.P[1].x)) / (-(triangle.P[0].x - triangle.P[1].x) * (triangle.P[2].y - triangle.P[1].y) + (triangle.P[0].y - triangle.P[1].y) * (triangle.P[2].x - triangle.P[1].x));
    float b = ((point.y - triangle.P[2].y) * (triangle.P[0].x - triangle.P[2].x) - (point.x - triangle.P[2].x) * (triangle.P[0].y - triangle.P[2].y)) / ((triangle.P[1].y - triangle.P[2].y) * (triangle.P[0].x - triangle.P[2].x) - (triangle.P[1].x - triangle.P[2].x) * (triangle.P[0].y - triangle.P[2].y));
    float c = 1 - a - b;
    float Ans = a * (1.0 / dep[0]) + b * (1.0 / dep[1]) + c * (1.0 / dep[2]);
    return 1.0 / Ans;
}

Color SoftwareRender::ColorTest(Vector2 point, Triangle triangle)
{
    float b = ((point.y - triangle.P[2].y) * (triangle.P[0].x - triangle.P[2].x) - (point.x - triangle.P[2].x) * (triangle.P[0].y - triangle.P[2].y)) / ((triangle.P[1].y - triangle.P[2].y) * (triangle.P[0].x - triangle.P[2].x) - (triangle.P[1].x - triangle.P[2].x) * (triangle.P[0].y - triangle.P[2].y));
    float a = (-(point.x - triangle.P[1].x) * (triangle.P[2].y - triangle.P[1].y) + (point.y - triangle.P[1].y) * (triangle.P[2].x - triangle.P[1].x)) / (-(triangle.P[0].x - triangle.P[1].x) * (triangle.P[2].y - triangle.P[1].y) + (triangle.P[0].y - triangle.P[1].y) * (triangle.P[2].x - triangle.P[1].x));
    float c = 1 - a - b;
    Color ans = color_base[0] * a + color_base[1] * b + color_base[2] * c;
    return ans;
}

Color SoftwareRender::SSAA(int x, int y, bool type)
{
    if (!type)
    {
        Color ans;
        ans.R = ans.G = ans.B = 0;
        for (int i = 0; i < SSAAFactor; i++)
            for (int j = 0; j < SSAAFactor; j++)
            {
                int sx = x * SSAAFactor + i;
                int sy = y * SSAAFactor + j;
                if (!Tmp.InTriangle(Vector2(sx, sy)))
                {
                    ans = ans + frame_buffer[sx][sy];
                    continue;
                }
                if (DepthTest(Vector2(sx, sy), Tmp) >= depth_buffer[sx][sy])
                {
                    ans = ans + frame_buffer[sx][sy];
                }
                else
                {
                    depth_buffer[sx][sy] = DepthTest(Vector2(sx, sy), Tmp);

                    Color rend = ColorTest(Vector2(sx, sy), Tmp);
                    ans = ans + rend;
                    frame_buffer[sx][sy] = rend;
                }
            }
        ans /= (SSAAFactor * SSAAFactor);
        return ans;
    }
    else
    {
        Color ans;
        ans.R=ans.G=ans.B=0;
        Vector2 edge1 = Tmp.P[2] - Tmp.P[1];
        Vector2 edge2 = Tmp.P[0] - Tmp.P[1];
        float det=edge1.x*edge2.y-edge1.y*edge2.x;
        for (int i = 0; i < SSAAFactor; i++)
        {
            for (int j = 0; j < SSAAFactor; j++)
            {
                int sx = x * SSAAFactor + i;
                int sy = y * SSAAFactor + j;
                if (!Tmp.InTriangle(Vector2(sx, sy)))
                {
                    ans = ans + frame_buffer[sx][sy];
                    continue;
                }
                if (DepthTest(Vector2(sx, sy), Tmp) >= depth_buffer[sx][sy])
                {
                    ans = ans + frame_buffer[sx][sy];
                }
                else
                {
                    float ratex=fabs((Vector2(sx,sy)-Tmp.P[1])*Vector2(edge2.y,-edge2.x)/det);
                    float ratey=fabs((Vector2(sx,sy)-Tmp.P[1])*Vector2(-edge1.y,edge1.x)/det);
                    if(ratex>2) cout<<"Wrong",exit(0);
                    bool flag = 0;
                    depth_buffer[sx][sy] = DepthTest(Vector2(sx, sy), Tmp);
                    if (ratex <= 0.1 || (ratex >= 0.2 && ratex <= 0.3) || (ratex >= 0.4 && ratex <= 0.5) || (ratex >= 0.6 && ratex <= 0.7) || (ratex >= 0.8 && ratex <= 0.9))
                        flag = 1;
                    if (flag)
                    {
                        
                        if (ratey <= 0.1 || (ratey >= 0.2 && ratey <= 0.3) || (ratey >= 0.4 && ratey <= 0.5) || (ratey >= 0.6 && ratey <= 0.7) || (ratey >= 0.8 && ratey <= 0.9))
                        {
                            ans += color_base[0];
                            frame_buffer[sx][sy] = color_base[0];
                        }
                        else
                        {
                            
                            ans += Color(251,238,226);
                            frame_buffer[sx][sy] = Color(251,238,226);
                        }
                    }
                    else
                    {
                        if (ratey <= 0.1 || (ratey >= 0.2 && ratey <= 0.3) || (ratey >= 0.4 && ratey <= 0.5) || (ratey >= 0.6 && ratey <= 0.7) || (ratey >= 0.8 && ratey <= 0.9))
                        {
                            ans += Color(251,238,226);
                            frame_buffer[sx][sy] = Color(251,238,226);
                        }
                        else
                        {
                            ans += color_base[0];
                            frame_buffer[sx][sy] = color_base[0];
                        }
                    }
                }
            }
        }
        ans/=(SSAAFactor*SSAAFactor);
        return ans;
    }
}

void SoftwareRender::DrawTriangle(Triangle Tri)
{
    Tmp = Tri * SSAAFactor;
    int l, r, t, b;
    l = min(int(Tri.P[0].x), min(int(Tri.P[1].x), int(Tri.P[2].x)));
    r = max(int(Tri.P[0].x), max(int(Tri.P[1].x), int(Tri.P[2].x)));
    t = max(int(Tri.P[0].y), max(int(Tri.P[1].y), int(Tri.P[2].y)));
    b = min(int(Tri.P[0].y), min(int(Tri.P[1].y), int(Tri.P[2].y)));
    for (int j = b; j <= t; j++)
    {
        for (int i = l; i <= r; i++)
        {
            pixel[i][j] = SSAA(i, j, 0);
        }
    }
}

void SoftwareRender::PPM()
{
    cout << 'k';
    freopen("Test.ppm", "w", stdout);
    cout << "P3\n"
         << Width << ' ' << Height << "\n255\n";
    for (int j = 0; j < Height; j++)
    {
        for (int i = 0; i < Width; i++)
        {
            cout << int(pixel[i][j].R) << ' ' << int(pixel[i][j].G) << ' ' << int(pixel[i][j].B) << '\n';
        }
    }
}

void SoftwareRender::GetMatrix()
{
    Vector3 Z = CameraPoint - Camera;
    Z.Standardize();
    Vector3 X = UP ^ Z;
    X.Standardize();
    Vector3 Y = Z ^ X;
    Y.Standardize();
    WTI.Mt[0][0] = X.x;
    WTI.Mt[0][1] = X.y;
    WTI.Mt[0][2] = X.z;
    WTI.Mt[0][3] = -X * Camera;
    WTI.Mt[1][0] = Y.x;
    WTI.Mt[1][1] = Y.y;
    WTI.Mt[1][2] = Y.z;
    WTI.Mt[1][3] = -Y * Camera;
    WTI.Mt[2][0] = Z.x;
    WTI.Mt[2][1] = Z.y;
    WTI.Mt[2][2] = Z.z;
    WTI.Mt[2][3] = -Z * Camera;
    WTI.Mt[3][0] = 0;
    WTI.Mt[3][1] = 0;
    WTI.Mt[3][2] = 0;
    WTI.Mt[3][3] = 1;

    ITP.Standardize();
    ITP.Mt[0][0] = 1.0 / (aspect * tan(fov));
    ITP.Mt[1][1] = 1 / tan(fov);
    ITP.Mt[2][2] = -(far + near) / (far - near);
    ITP.Mt[2][3] = -1;
    ITP.Mt[3][3] = 0;
    ITP.Mt[3][2] = 2 * near * far / (far - near);

    PTS.Standardize();
    PTS.Mt[0][0] = PTS.Mt[0][3] = Width / 2;
    PTS.Mt[1][1] = -Height / 2;
    PTS.Mt[1][3] = Height / 2;
    PTS.Mt[2][2] = 1000;

    MVP = PTS * ITP * WTI;
}

Vector3 SoftwareRender::MVPTransformation(Vector3 vec)
{
    Vector4 tmp;
    tmp.x = vec.x;
    tmp.y = vec.y;
    tmp.z = vec.z;
    tmp.w = 1;
    tmp = MVP * tmp;
    vec.x = tmp.x / tmp.w;
    vec.y = tmp.y / tmp.w;
    vec.z = tmp.z / tmp.w;
    return vec;
}

void SoftwareRender::DrawCube(Cube cube)
{
    for (int i = 0; i < 8; i++)
    {
        cube.vertex1[i] = MVPTransformation(cube.vertex0[i]);
    }
    for (int i = 0; i < 12; i++)
    {
        Vector3 a = cube.vertex1[cube.triangle[i][0]];
        Vector3 b = cube.vertex1[cube.triangle[i][1]];
        Vector3 c = cube.vertex1[cube.triangle[i][2]];
        color_base[0] = cube.vertex_color[cube.triangle[i][0]];
        color_base[1] = cube.vertex_color[cube.triangle[i][1]];
        color_base[2] = cube.vertex_color[cube.triangle[i][2]];
        dep[0] = far * near / (far - a.z * (far - near));
        dep[1] = far * near / (far - b.z * (far - near));
        dep[2] = far * near / (far - c.z * (far - near));
        DrawTriangle(Triangle(a, b, c));
    }
}
