
#include <math.h>

#include "gl_includes.h"
#include "Vec.h"
#include "Camera.h"

Camera::Camera( )
{
	pos[0] = pos[1] = pos[2] = 0;
	rotation.identity();
}

Matrix Camera::get_modelview_matrix( ) const
{
        Matrix m = rotation;

        const RVec v = pos * rotation;

        m[12] = -v[0];
        m[13] = -v[1];
        m[14] = -v[2];

        return m;
}

void Camera::reset_bounds()
{
        const Matrix m = get_modelview_matrix() * projection;

        n_left = RVec(
                        m.v[3] + m.v[0],
                        m.v[7] + m.v[4],
                        m.v[11] + m.v[8]);

        n_right = RVec(
                        m.v[3] - m.v[0],
                        m.v[7] - m.v[4],
                        m.v[11] - m.v[8]);
        
        n_bottom = RVec(
                        m.v[3] + m.v[1],
                        m.v[7] + m.v[5],
                        m.v[11] + m.v[9]);
        
        n_top = RVec(
                        m.v[3] - m.v[1],
                        m.v[7] - m.v[5],
                        m.v[11] - m.v[9]);
        
        n_near = RVec(
                        m.v[3] + m.v[2],
                        m.v[7] + m.v[6],
                        m.v[11] + m.v[10]);

        n_far = RVec(
                        m.v[3] - m.v[2],
                        m.v[7] - m.v[6],
                        m.v[11] - m.v[10]);

        const real d_near = m.v[15] + m.v[14];
        const real d_far = m.v[15] - m.v[14];

        const RVec d_bl = n_bottom.cross( n_left );
        const RVec d_br = n_bottom.cross( n_right );
        const RVec d_tl = n_top.cross( n_left );
        const RVec d_tr = n_top.cross( n_right );

        nbl = plane_line_intersection( pos, d_bl, n_near, d_near );
        nbr = plane_line_intersection( pos, d_br, n_near, d_near );
        ntl = plane_line_intersection( pos, d_tl, n_near, d_near );
        ntr = plane_line_intersection( pos, d_tr, n_near, d_near );
        fbl = plane_line_intersection( pos, d_bl, n_far, d_far );
        fbr = plane_line_intersection( pos, d_br, n_far, d_far );
        ftl = plane_line_intersection( pos, d_tl, n_far, d_far );
        ftr = plane_line_intersection( pos, d_tr, n_far, d_far );
}

RVec Camera::getX( ) const
{
	return RVec( rotation.v[0], rotation.v[4], rotation.v[8] );
}

RVec Camera::getY( ) const
{
	return RVec( rotation.v[1], rotation.v[5], rotation.v[9] );
}

RVec Camera::getZ( ) const
{
	return RVec( rotation.v[2], rotation.v[6], rotation.v[10] );
}

void Camera::moveTo( real x, real y, real z )
{
	pos[ 0 ] = x;
	pos[ 1 ] = y;
	pos[ 2 ] = z;
}

void Camera::moveTo( const RVec& p )
{
	pos = p;
}

void Camera::move( real dx, real dy, real dz )
{
	pos[ 0 ] += dx;
	pos[ 1 ] += dy;
	pos[ 2 ] += dz;
}

void Camera::move( const RVec& d )
{
	pos += d;
}

//         |  CE      -CF      -D   0 |
//    M  = | -BDE+AF   BDF+AE  -BC  0 |
//         |  ADE+BF  -ADF+BE   AC  0 |
//         |  0        0        0   1 |

void Camera::rotate( real dRX, real dRY, real dRZ )
{
	Matrix m;

	m.rotation( dRX, dRY, dRZ );

	rotation *= m;
}

void Camera::rotate( real angle, real nx, real ny, real nz )
{
	Matrix m;

	m.rotation( angle, nx, ny, nz );

	rotation *= m;
}

void Camera::rotate( real angle, const RVec& axis )
{
	Matrix m;

	m.rotation( angle, axis );

	rotation *= m;
}

void Camera::lookdir( const RVec& look, const RVec& up )
{
	lookdir( look[0], look[1], look[2], up[0], up[1], up[2] );
}

void Camera::lookdir( real dx, real dy, real dz, real ux, real uy, real uz )
{
	real nd = 1 / sqrt (dx*dx + dy*dy + dz*dy);
	real nu = 1 / sqrt (ux*ux + uy*uy + uz*uy);

	dx *= nd;
	dy *= nd;
	dz *= nd;

	ux *= nu;
	uy *= nu;
	uz *= nu;

	rotation.v[ 0 ] = dx;
	rotation.v[ 4 ] = dy;
	rotation.v[ 8 ] = dz;

	rotation.v[ 1 ] = ux;
	rotation.v[ 5 ] = uy;
	rotation.v[ 9 ] = uz;

	rotation.v[ 2 ] = dy*uz - dz*uy;
	rotation.v[ 6 ] = dz*ux - dx*uz;
	rotation.v[ 10 ]= dx*uy - dy*ux;
}

void Camera::viewFrom( ) const
{
        glMatrixMode( GL_MODELVIEW );
        const Matrix m = get_modelview_matrix();
        glLoadMatrixd( m.v );
}
