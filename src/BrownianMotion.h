
#ifndef _BROWNIANMOTION_H
#define _BROWNIANMOTION_H

#include "Motion.h"

class BrownianMotion : public Motion
{
public:

    BrownianMotion( real noise, gsl_rng* const rng, real friction ) ;

    void step( real& x, real& y, real& vx, real& vy, real dt ) const;

protected:

    const real friction;
};

#endif // _BROWNIANMOTION_H
