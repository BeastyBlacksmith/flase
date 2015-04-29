
#ifndef _CONSTVELOCITY_H
#define _CONSTVELOCITY_H

#include "Motion.h"

class ConstVelocity : public Motion
{
public:

    ConstVelocity( real noise, gsl_rng* const rng ) :
        Motion( noise, rng )
    {
    }

    void step( real& x, real& y, real& vx, real& vy, real dt ) const;

protected:
    //TODO: an v0 kommen! 
    real persistenceLength;

};

#endif // _CONSTVELOCITY_H

