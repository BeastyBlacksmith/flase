
#ifndef _MOTION_H
#define _MOTION_H

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "common.h"

class Motion {
public:

    Motion( real noise, gsl_rng* const rng ) :
        noise( noise ),
        rng( rng ),
        persistenceLength( -1 ),
        persistenceTime( -1 ),
        effectiveDiffusion( -1 )
    {
    }

    virtual ~Motion() {}

    virtual void step( real& x, real& y, real& vx, real& vy, real dt ) const = 0;

    real getPersistenceLength() const { return persistenceLength; }
    real getPersistenceTime() const { return persistenceTime; }
    real getEffectiveDiffusion() const { return effectiveDiffusion; }

protected:

    real noise;
    gsl_rng* const rng;
    real persistenceLength;
    real persistenceTime;
    real effectiveDiffusion;

};

#endif // _MOTION_H
