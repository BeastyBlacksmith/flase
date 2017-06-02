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
