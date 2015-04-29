
#include <math.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "BrownianMotion.h"

void BrownianMotion::step( real& x, real& y, real& vx, real& vy, real dt ) const
{
    vx -= friction*vx*dt - sqrt( 2*noise*friction*dt )*gsl_ran_gaussian( rng, 1. );
    vy -= friction*vy*dt - sqrt( 2*noise*friction*dt )*gsl_ran_gaussian( rng, 1. );

    x += vx*dt;
    y += vy*dt;
}
