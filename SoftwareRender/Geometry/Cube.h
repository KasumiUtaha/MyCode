#pragma once
#include "../math/Matrix.h"
#include "../Color.h"

class Cube
{
public:
    Vector3 vertex0[8], vertex1[8];
    int triangle[12][3]={{0, 3, 2},{2, 1, 0},{0, 3, 7},
                        {7, 4, 0},{2, 3, 7},{7, 6, 2},
                        {2 , 6, 5},{5,1,2},{1, 5, 4},
                        {4, 0, 1},{6, 7, 4},{4, 5, 6}
                        };
    Color vertex_color[8];

    Cube();

};