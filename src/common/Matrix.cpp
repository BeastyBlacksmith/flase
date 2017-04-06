
#include <math.h>
#include <string.h>

#include "common.h"
#include "Matrix.h"


Matrix::Matrix ()
{
}

void Matrix::rotation (real angle, const RVec& axis)
{
    rotation (angle, axis[0], axis[1], axis[2]);
}

void Matrix::rotation (real angle, real nx, real ny, real nz)
{
    const real c = cos(angle);
    const real mc = 1 - c;
    const real s = sin(angle);
    const real nx2 = nx*nx;
    const real ny2 = ny*ny;
    const real nz2 = nz*nz;
    const real nxny = nx*ny * mc;
    const real nxnz = nx*nz * mc;
    const real nynz = ny*nz * mc;

    v[0] = nx2 + (1 - nx2) * c;
    v[1] = nxny - nz * s;
    v[2] = nxnz + ny * s;
    v[3] = 0;
    v[4] = nxny + nz * s;
    v[5] = ny2 + (1 - ny2) * c;
    v[6] = nynz - nx * s;
    v[7] = 0;
    v[8] = nxnz - ny * s;
    v[9] = nynz + nx * s;
    v[10]= nz2 + (1 - nz2) * c;
    v[11]= 0;
    v[12]= 0;
    v[13]= 0;
    v[14]= 0;
    v[15]= 1;
}

//         |  CE      -CF      -D   0 |
//    M  = | -BDE+AF   BDF+AE  -BC  0 |
//         |  ADE+BF  -ADF+BE   AC  0 |
//         |  0        0        0   1 |
void Matrix::rotation (real dRX, real dRY, real dRZ)
{
    const real A = cos(dRX);
    const real B = sin(dRX);
    const real C = cos(dRY);
    const real D = sin(dRY);
    const real E = cos(dRZ);
    const real F = sin(dRZ);

    const real AD = A * D;
    const real BD = B * D;

    v[0] =  C   *   E;
    v[1] =  -C  *   F;
    v[2] =  -D;
    v[3] =  0;
    v[4] =  -BD *   E   +   A   *   F;
    v[5] =  BD  *   F   +   A   *   E;
    v[6] =  -B  *   C;
    v[7] =  0;
    v[8] =  AD  *   E   +   B   *   F;
    v[9] =  -AD *   F   +   B   *   E;
    v[10]=  A   *   C;
    v[11]=  0;
    v[12]=  0;
    v[13]=  0;
    v[14]=  0;
    v[15]=  1;
}

void Matrix::perspective (real fovy, real aspect, real zNear, real zFar)
{
    const float pi = 3.14159265358979323846;
    const real f = 1 / tan (fovy * (90 / pi));

    v[0] = f / aspect;
    v[1] = v[2] = v[3] = 0;

    v[4] = 0;
    v[5] = f;
    v[6] = v[7] = 0;

    v[8] = v[9] = 0;
    v[10] = (zNear + zFar) / (zNear - zFar);
    v[11] = 2*zNear*zFar / (zNear - zFar);

    v[12] = 0;
    v[13] = 0;
    v[14] = -1;
    v[15] = 0;
}

void Matrix::identity ()
{
    memset (v, 0, 16*sizeof (real));

    v[0] = v[5] = v[10] = v[15] = 1;
}

Matrix Matrix::transposed( ) const
{
    Matrix tmp;

    tmp.v[0] = v[0];
    tmp.v[1] = v[4];
    tmp.v[2] = v[8];
    tmp.v[3] = v[12];

    tmp.v[4] = v[1];
    tmp.v[5] = v[5];
    tmp.v[6] = v[9];
    tmp.v[7] = v[13];

    tmp.v[8] = v[2];
    tmp.v[9] = v[6];
    tmp.v[10] = v[10];
    tmp.v[11] = v[14];

    tmp.v[12] = v[3];
    tmp.v[13] = v[7];
    tmp.v[14] = v[11];
    tmp.v[15] = v[15];

    return tmp;
}

Matrix Matrix::operator* (const Matrix& m) const
{
    Matrix          tmp;
    real* const     dNew = tmp.v;
    const real* const   src = m.v;
    const real* const   dest = v;

    dNew[0] = dest[0] * src[0] + dest[1] * src[4] + dest[2] * src[8] + dest[3] * src[12];
    dNew[1] = dest[0] * src[1] + dest[1] * src[5] + dest[2] * src[9] + dest[3] * src[13];
    dNew[2] = dest[0] * src[2] + dest[1] * src[6] + dest[2] * src[10] + dest[3] * src[14];
    dNew[3] = dest[0] * src[3] + dest[1] * src[7] + dest[2] * src[11] + dest[3] * src[15];

    dNew[4] = dest[4] * src[0] + dest[5] * src[4] + dest[6] * src[8] + dest[7] * src[12];
    dNew[5] = dest[4] * src[1] + dest[5] * src[5] + dest[6] * src[9] + dest[7] * src[13];
    dNew[6] = dest[4] * src[2] + dest[5] * src[6] + dest[6] * src[10] + dest[7] * src[14];
    dNew[7] = dest[4] * src[3] + dest[5] * src[7] + dest[6] * src[11] + dest[7] * src[15];

    dNew[8] = dest[8] * src[0] + dest[9] * src[4] + dest[10] * src[8] + dest[11] * src[12];
    dNew[9] = dest[8] * src[1] + dest[9] * src[5] + dest[10] * src[9] + dest[11] * src[13];
    dNew[10] = dest[8] * src[2] + dest[9] * src[6] + dest[10] * src[10] + dest[11] * src[14];
    dNew[11] = dest[8] * src[3] + dest[9] * src[7] + dest[10] * src[11] + dest[11] * src[15];

    dNew[12] = dest[12] * src[0] + dest[13] * src[4] + dest[14] * src[8] + dest[15] * src[12];
    dNew[13] = dest[12] * src[1] + dest[13] * src[5] + dest[14] * src[9] + dest[15] * src[13];
    dNew[14] = dest[12] * src[2] + dest[13] * src[6] + dest[14] * src[10] + dest[15] * src[14];
    dNew[15] = dest[12] * src[3] + dest[13] * src[7] + dest[14] * src[11] + dest[15] * src[15];

    return tmp;
}

Matrix& Matrix::operator*= (const Matrix& m)
{
    *this = *this * m;
    return *this;
}


////////////////////////////////////////////////////////////////////////////////


RVec plane_line_intersection( const RVec& l_p, const RVec& l_d, const RVec& p_n, const real p_d )
{
    const real t = ( -p_d - l_p*p_n ) / ( l_d*p_n );

    return l_p + t*l_d;
}

bool plane_ray_intersection( const RVec& l_p, const RVec& l_d, const RVec& p_n, const real p_d, RVec& result )
{
    const real t = ( -p_d - l_p*p_n ) / ( l_d*p_n );
    if (t < 0) {
        return false;
    } else {
        result = l_p + t*l_d;
        return true;
    }
}
