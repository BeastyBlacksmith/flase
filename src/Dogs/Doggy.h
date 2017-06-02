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

#ifndef _DOGGY_H
#define _DOGGY_H

#include "common.h"

#include "Motion.h"

typedef enum {
    ACTIVE = 1, OCCUPIED, SLEEPY
} DoggyState;

class Doggy
{
public:
    
    Doggy() :
            state( ACTIVE ),
            sleepyness( 0 )
    {
    }
    
    void move( real dt, Motion& motion );
    
    void work( real dt );
    
    DoggyState getState() const { return state; }
    
    real x;
    real y;
    real vx;
    real vy;

private:
    
    DoggyState state;
    size_t sleepyness;
};

#endif // _DOGGY_H
