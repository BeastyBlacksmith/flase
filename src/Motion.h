
#ifndef _MOTION_H
#define _MOTION_H

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "common.h"

class Motion {
public:

    Motion( real noise, gsl_rng* const rng ) :
        noise( noise ),
        rng( rng )
    {
    }

    virtual void step( real& x, real& y, real& vx, real& vy, real dt ) const = 0;

protected:

    real noise;
    gsl_rng* const rng;

};

#endif // _MOTION_H
