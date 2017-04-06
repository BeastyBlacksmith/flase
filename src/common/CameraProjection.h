
#ifndef _CAMERAPROJECTION_H
#define _CAMERAPROJECTION_H

#include "Matrix.h"

class CameraProjection
{
public:
        void set_projection( ) const;
        const Matrix& get_projection_matrix( ) const { return projection; }

        void perspective( real angle_fov, real ratio, real znear, real zfar );
        void orthographic( real width, real height, real znear, real zfar );

        Matrix projection;
};

#endif // _CAMERAPROJECTION_H
