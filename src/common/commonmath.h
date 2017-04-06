
#ifndef _COMMONMATH_H
#define _COMMONMATH_H

#include "common.h"

inline real minf( const real a, const real b )
{
	return a < b ? a : b;
}

inline real maxf( const real a, const real b )
{
	return a > b ? a : b;
}

inline int min( const int a, const int b )
{
	return a < b ? a : b;
}

inline int max( const int a, const int b )
{
	return a > b ? a : b;
}


inline int sgn( const int i )
{
        if( i >= 0 )
                return 1;
        else
                return -1;
}

#endif // _COMMONMATH_H
