
#ifndef _VEC_H
#define _VEC_H

#include <math.h>

#include "common.h"
#include "commonmath.h"

template< typename T >
class Vec
{
public:
    T   v[3];

    Vec ()
    {
        v[0] = 0, v[1] = 0, v[2] = 0;
    }
    Vec( const T x, const T y, const T z )
    {
        v[0] = x, v[1] = y, v[2] = z;
    }
    Vec( const T _v )
    {
        v[0] = _v;
        v[1] = _v;
        v[2] = _v;
    }
    Vec( const Vec< T >& r )
    {
        v[0] = r.v[0];
        v[1] = r.v[1];
        v[2] = r.v[2];
    }

    void copyto( T* const array ) const
    {
        array[0] = v[0];
        array[1] = v[1];
        array[2] = v[2];
    }

    Vec< T > operator*( const T c ) const
    {
        return Vec< T >( v[0]*c, v[1]*c, v[2]*c );
    }

    Vec< T > operator/( const T c ) const
    {
        return Vec< T >( v[0]/c, v[1]/c, v[2]/c );
    }

    Vec< T > operator%( const T c ) const
    {
        return Vec< T >( v[0]%c, v[1]%c, v[2]%c );
    }

    Vec< T >& operator*=( const T c )
    {
        v[0] *= c;
        v[1] *= c;
        v[2] *= c;
        return *this;
    }

    Vec< T >& operator+=( const Vec< T >& r )
    {
        v[0] += r.v[0];
        v[1] += r.v[1];
        v[2] += r.v[2];
        return *this;
    }

    Vec< T >& operator-=( const Vec< T >& r )
    {
        v[0] -= r.v[0];
        v[1] -= r.v[1];
        v[2] -= r.v[2];
        return *this;
    }

    bool operator==( const Vec< T >& r ) const
    {
        return this->v[0] == r.v[0] && this->v[1] == r.v[1] && this->v[2] == r.v[2];
    }

    bool operator!=( const Vec< T >& r ) const
    {
        return this->v[0] != r.v[0] || this->v[1] != r.v[1] || this->v[2] != r.v[2];
    }

    Vec< T > scale( const Vec< T >& r ) const
    {
        return Vec< T >( v[0]*r[0], v[1]*r[1], v[2]*r[2] );
    }

    Vec< T > operator+( const Vec& r ) const
    {
        return Vec< T >( v[0] + r.v[0], v[1] + r.v[1], v[2] + r.v[2] );
    }

    Vec< T > operator+( const T r ) const
    {
        return Vec< T >( v[0] + r, v[1] + r, v[2] + r );
    }

    Vec< T >operator-( const Vec< T >& r ) const
    {
        return Vec< T >( v[0] - r.v[0], v[1] - r.v[1], v[2] - r.v[2] );
    }

    Vec< T >operator-( const T r ) const
    {
        return Vec< T >( v[0] - r, v[1] - r, v[2] - r );
    }

    T operator*( const Vec< T >& r ) const
    {
        return v[0]*r.v[0] + v[1]*r.v[1] + v[2]*r.v[2];
    }

    T& operator[]( const int i )
    {
        return v[i];
    }

    const T operator[]( const int i ) const
    {
        return v[i];
    }

    bool operator<( const Vec& r ) const
    {
        return v[0] < r.v[0] && v[1] < r.v[1] && v[2] < r.v[1];
    }

    bool operator<=( const Vec& r ) const
    {
        return v[0] <= r.v[0] && v[1] <= r.v[1] && v[2] <= r.v[1];
    }

    bool operator>( const Vec& r ) const
    {
        return v[0] > r.v[0] && v[1] > r.v[1] && v[2] > r.v[1];
    }

    bool operator>=( const Vec& r ) const
    {
        return v[0] >= r.v[0] && v[1] >= r.v[1] && v[2] >= r.v[1];
    }

    T sqnorm( ) const
    {
        return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    }

    T cross_x( const Vec< T >& r ) const
    {
        return v[1]*r.v[2] - v[2]*r.v[1];
    }

    T cross_y( const Vec< T >& r ) const
    {
        return  v[2]*r.v[0]-v[0]*r.v[2];
    }

    T cross_z( const Vec< T >& r ) const
    {
        return v[0]*r.v[1]-v[1]*r.v[0];
    }

    Vec< T > cross( const Vec< T >& r ) const
    {
        return Vec< T >( cross_x( r ), cross_y( r ), cross_z( r ) );
    }

    void normalize( )
    {
        const T sn = sqnorm();
        if( sn > 0.00000001 )
            *this *= 1 / sqrt( sn );
    }

    Vec< T > normalized( ) const
    {
        const T sn = sqnorm();
        if( sn > 0.00000001 )
        {
            const T rsn = 1 / sqrt( sn );
            return Vec< T >( rsn*v[0], rsn*v[1], rsn*v[2] );
        }
        else
            return *this;
    }

    T min( ) const
    {
        if( v[0] < v[1] )
        {
            if( v[0] < v[2] )
                return v[0];
            else
                return v[2];
        }
        else if( v[1] < v[2] )
        {
            return v[1];
        }
        else
            return v[2];
    }

    T max( ) const
    {
        if( v[0] > v[1] )
        {
            if( v[0] > v[2] )
                return v[0];
            else
                return v[2];
        }
        else if( v[1] > v[2] )
        {
            return v[1];
        }
        else
            return v[2];
    }

    void floor( )
    {
        v[0] = ::floor( v[0] );
        v[1] = ::floor( v[1] );
        v[2] = ::floor( v[2] );
    }

    Vec floored( ) const
    {
        return Vec< T >( ::floor( v[0] ), ::floor( v[1] ), ::floor( v[2] ) );
    }

    void ceil( )
    {
        v[0] = ::ceil( v[0] );
        v[1] = ::ceil( v[1] );
        v[2] = ::ceil( v[2] );
    }

    Vec< T > ceiled( )
    {
        return Vec< T >( ::ceil( v[0] ), ::ceil( v[1] ), ::ceil( v[2] ) );
    }
};

template< typename T >
inline Vec< T > operator*( const T l, const Vec< T >& r ) { return r*l; }

template< typename T >
inline Vec< T > min( const Vec< T >& a, const Vec< T >& b )
{
    return Vec< T >(
                    a[0] < b[0] ? a[0] : b[0],
                    a[1] < b[1] ? a[1] : b[1],
                    a[2] < b[2] ? a[2] : b[2]
                    );
}

template< typename T >
inline Vec< T > max( const Vec< T >& a, const Vec< T >& b )
{
    return Vec< T >(
                    a[0] > b[0] ? a[0] : b[0],
                    a[1] > b[1] ? a[1] : b[1],
                    a[2] > b[2] ? a[2] : b[2]
                   );
}

#endif // _VEC_H
