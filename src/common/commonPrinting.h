
#ifndef _COMMON_PRINTING_H
#define _COMMON_PRINTING_H

#include <iostream>

#include "Camera.h"

std::ostream& operator<<( std::ostream& out, const RVec& vec );

template< typename T >
std::ostream& operator<<( std::ostream& out, const Vec< T >& vec )
{
        return out << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";
}

std::ostream& operator<<( std::ostream& out, const Camera& cam );

std::ostream& operator<<( std::ostream& out, const Matrix& m );

#endif // _COMMON_PRINTING
