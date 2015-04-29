
#ifndef _DOGGY_H
#define _DOGGY_H

#include "common.h"

#include "Motion.h"

typedef enum {
    ACTIVE = 1,
    OCCUPIED,
    SLEEPY
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
