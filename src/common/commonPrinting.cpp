
#include "commonPrinting.h"

std::ostream& operator<<( std::ostream& out, const RVec& vec )
{
        return out << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";
}

std::ostream& operator<<( std::ostream& out, const Matrix& m )
{
        out << "(";
        for( unsigned int i = 0; i < 4; ++i )
        {
                out << "(";
                out << m[4*i];
                for( unsigned int j = 1; j < 4; ++j )
                {
                        out << "," << m[4*i+j];
                }
                if( 3 == i )
                        out << ")";
                else
                        out << "),";
        }

        return out << ")";
}

std::ostream& operator<<( std::ostream& out, const Camera& cam )
{
        return out << "(" << cam.getX() << ", " << cam.getY() << ", " << cam.getZ() << ", " << cam.pos << ")";
}

