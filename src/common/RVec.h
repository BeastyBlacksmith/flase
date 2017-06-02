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

#ifndef _RVEC_H
#define _RVEC_H

#include "Vec.h"

class RVec : public Vec< real >
{
public:
	RVec( ) : Vec< real >() {}
	
	RVec( const real x, const real y, const real z ) : Vec< real >( x, y, z ) {}
	
	RVec( const real _v ) : Vec< real >( _v ) {}
	
	RVec( const Vec< real >& r ) : Vec< real >( r ) {}
	
	RVec( const RVec& r ) : Vec< real >( r ) {}
	
	template< typename S >
	RVec( const Vec< S >& r ) : Vec< real >( r[0], r[1], r[2] ) {}
	
	RVec operator*( const real c ) const
	{
		return RVec( static_cast< const Vec< real >& >( *this ) * c );
	}
	
	RVec operator/( const real c ) const
	{
		return RVec( static_cast< const Vec< real >& >( *this ) / c );
	}
	
	RVec& operator*=( const real c )
	{
		static_cast< Vec< real >& >( *this ) *= c;
		return *this;
	}
	
	RVec& operator+=( const RVec& r )
	{
		static_cast< Vec< real >& >( *this ) += r;
		return *this;
	}
	
	RVec& operator-=( const RVec& r )
	{
		static_cast< Vec< real >& >( *this ) -= r;
		return *this;
	}
	
	// bool operator==( const RVec& r )
	// {
	// 	return this->v[0] == r.v[0] && this->v[1] == r.v[1] && this->v[2] == r.v[2];
	// }
	
	// bool operator!=( const RVec& r )
	// {
	// 	return this->v[0] != r.v[0] || this->v[1] != r.v[1] || this->v[2] != r.v[2];
	// }
	
	real operator*( const RVec& r ) const
	{
		return static_cast< const Vec< real >& >( *this ) * r;
	}
	
	RVec scale( const RVec& r ) const
	{
		return RVec( Vec< real >::scale( r ) );
	}
	
	RVec operator+( const RVec& r ) const
	{
		return RVec( static_cast< const Vec< real >& >( *this ) + r );
	}
	
	RVec operator+( const real r ) const
	{
		return RVec( static_cast< const Vec< real >& >( *this ) + r );
	}
	
	RVec operator-( const RVec& r ) const
	{
		return RVec( static_cast< const Vec< real >& >( *this ) - r );
	}
	
	RVec operator-( const real r ) const
	{
		return RVec( static_cast< const Vec< real >& >( *this ) -r );
	}
	
	RVec cross( const RVec& r ) const
	{
		return RVec( Vec< real >::cross( r ) );
	}
	
};

inline RVec operator*( const real l, const RVec& r ) { return r*l; }

#endif // _RVEC_H
