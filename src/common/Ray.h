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
