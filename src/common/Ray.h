
#ifndef _RAY_H
#define _RAY_H

#include "RVec.h"

class Ray {
public:
    RVec pos;
    RVec dir;

    Ray ()
    {
    }

    Ray( const RVec& p, const RVec& d ) :
        pos( p ),
        dir( d )
    {
    }

    Ray( const Ray& r )
    {
        pos = r.pos;
        dir = r.dir;
    }

    void normalize( )
    {
        dir.normalize();
    }
};

#endif // _RAY_H
