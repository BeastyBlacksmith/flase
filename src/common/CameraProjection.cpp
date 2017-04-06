
#include <GL/glew.h>

#include <math.h>

#include "CameraProjection.h"

void CameraProjection::set_projection( ) const
{
    glMatrixMode( GL_PROJECTION );
    glLoadMatrixd( projection.v );
    glMatrixMode( GL_MODELVIEW );
}

// TODO: same as perspective mode in class Matrix?!
void CameraProjection::perspective( real angle_fov, real ratio, real znear, real zfar )
{
        const real xymax = znear * tan( angle_fov * ( M_PI / 360.0 ) );
        const real ymin = -xymax;
        const real xmin = -xymax;

        const real width = xymax - xmin;
        const real height = xymax - ymin;

        const real depth = zfar - znear;
        const real q = -(zfar + znear) / depth;
        const real qn = -2 * (zfar * znear) / depth;

        const real w = 2 * znear / ( width * ratio );
        const real h = 2 * znear / height;

        projection[0]  = w;
        projection[1]  = 0;
        projection[2]  = 0;
        projection[3]  = 0;

        projection[4]  = 0;
        projection[5]  = h;
        projection[6]  = 0;
        projection[7]  = 0;

        projection[8]  = 0;
        projection[9]  = 0;
        projection[10] = q;
        projection[11] = -1;

        projection[12] = 0;
        projection[13] = 0;
        projection[14] = qn;
        projection[15] = 0;
}

void CameraProjection::orthographic( real width, real height, real znear, real zfar ) {
        projection[0]  = 2 / width;
        projection[1]  = 0;
        projection[2]  = 0;
        projection[3]  = 0;

        projection[4]  = 0;
        projection[5]  = 2 / height;
        projection[6]  = 0;
        projection[7]  = 0;

        projection[8]  = 0;
        projection[9]  = 0;
        projection[10] = -2/( zfar-znear );
        projection[11] = 0;

        projection[12] = 0;
        projection[13] = 0;
        projection[14] = 0;
        projection[15] = 1;
}

