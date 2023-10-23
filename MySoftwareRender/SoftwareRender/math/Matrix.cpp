#include "Matrix.h"
#include <cstring>

Matrix::Matrix()
{
    memset(Mt,0,16*sizeof(float));
}

Vector4 Matrix::operator *(const Vector4& rhs) const
{
    Vector4 Ans;
    Ans.x=Ans.y=Ans.z=Ans.w=0;
    Ans.x=rhs.x*Mt[0][0]+rhs.y*Mt[0][1]+rhs.z*Mt[0][2]+rhs.w*Mt[0][3];
    Ans.y=rhs.x*Mt[1][0]+rhs.y*Mt[1][1]+rhs.z*Mt[1][2]+rhs.w*Mt[1][3];
    Ans.z=rhs.x*Mt[2][0]+rhs.y*Mt[2][1]+rhs.z*Mt[2][2]+rhs.w*Mt[2][3];
    Ans.w=rhs.x*Mt[3][0]+rhs.y*Mt[3][1]+rhs.z*Mt[3][2]+rhs.w*Mt[3][3];
    return Ans;
}

void Matrix::Standardize()
{
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) Mt[i][j]=0;
    Mt[0][0]=Mt[1][1]=Mt[2][2]=Mt[3][3]=1;
}

Matrix Matrix::operator * (const Matrix& rhs) const
{
    Matrix Ans;
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) Ans.Mt[i][j]=0;
    for(int k=0;k<4;k++)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            Ans.Mt[i][j]+=Mt[i][k]*rhs.Mt[k][j];
        }
    }
    return Ans;
}