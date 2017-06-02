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

#ifndef _MATRIX_H
#define _MATRIX_H

#include <math.h>

#include "common.h"

#include "commonmath.h"

#include "RVec.h"

class Matrix
{
public:
	real		v[16];
	
	Matrix ();
	
	void identity ();
	
	void rotation ( real dRX, real dRY, real dRZ);
	
	void rotation ( real angle, real nx, real ny, real nz);
	
	void rotation ( real angle, const RVec& axis);
	
	void perspective ( real fovy, real aspect, real zNear, real zFar);
	
	Matrix operator* ( const Matrix& m) const;
	
	Matrix& operator*= ( const Matrix& m);
	
	Matrix transposed( ) const;
	
	real& operator[]( const unsigned int i ) { return v[i]; }
	
	real operator[]( const unsigned int i ) const { return v[i]; }
	
	RVec operator* (const RVec& r) const
	{
		const real w = 1 / v[15];
		return RVec (
				w *( r[0]*v[0] + r[1]*v[1] + r[2]*v[2] + v[3] ),
				w *( r[0]*v[4] + r[1]*v[5] + r[2]*v[6] + v[7] ),
				w *( r[0]*v[8] + r[1]*v[9] + r[2]*v[10] + v[11] )
		);
	}
	
	RVec rotate( const RVec& r ) const
	{
		return RVec (
				r[0] *v[0] + r[1]*v[1] + r[2]*v[2],
				r[0] *v[4] + r[1]*v[5] + r[2]*v[6],
				r[0] *v[8] + r[1]*v[9] + r[2]*v[10]
		);
	}
};

inline RVec operator*( const RVec& v, const Matrix& m )
{
	const real w = 1 / m.v[15];
	return RVec(
			w *( v[0]*m.v[0] + v[1]*m.v[4] + v[2]*m.v[8] + m.v[12] ),
			w *( v[0]*m.v[1] + v[1]*m.v[5] + v[2]*m.v[9] + m.v[13] ),
			w *( v[0]*m.v[2] + v[1]*m.v[6] + v[2]*m.v[10] + m.v[14] )
	);
}

// intersection of line p+t*d with plane n*x+d=0
RVec plane_line_intersection( const RVec& l_p, const RVec& l_d, const RVec& p_n, const real p_d );
bool plane_ray_intersection( const RVec& l_p, const RVec& l_d, const RVec& p_n, const real p_d, RVec& result );

inline real rad2deg( const real rad )
{
	return rad*( 180 / M_PI );
}

inline real deg2rad( const real deg )
{
	return deg*( M_PI / 180 );
}

#endif // _MATRIX_H
