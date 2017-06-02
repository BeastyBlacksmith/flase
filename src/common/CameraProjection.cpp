/*
Copyright (C) 2017  Simon Christ <c.O_o.l@web.de>, Jörg Bachmann <explicit@explicits.de>

This program is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

