#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <cfloat>
#include "SoftwareRender/math/Matrix.h"
#include "SoftwareRender/math/Vector.h"
#include "SoftwareRender/SoftwareRender.h"
#include "SoftwareRender/Geometry/Cube.h"
using namespace std;


int main()
{
	freopen("C:\\Users\\12111\\Desktop\\VSC\\2.txt","r",stdin);
	SoftwareRender software_render;
	Cube cube;
	for(int i=0;i<8;i++)
	{
		float x,y,z;
		cin>>x>>y>>z;
		cube.vertex0[i]=Vector3(x,y,z);
	}
	software_render.DrawCube(cube);
	software_render.PPM();
	return 0;
}

/*
-1 1 1
-1 1 -1
-1 -1 1

-1 -1 -1
-1 1 -1
-1 -1 1

*/
