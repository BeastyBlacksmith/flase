
#include <math.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "common.h"
#include "ConstVelocity.h"

void ConstVelocity::step( real& x, real& y, real& vx, real& vy, real dt ) const
{
		//Heun
                real vabs, phi, heun1;
		vabs = sqrt( vx*vx+vy*vy );
		phi = atan2( vy, vx );
		heun1 = phi;

		phi += sqrt( 2.*noise*dt ) * gsl_ran_gaussian( rng, 1. )/vabs;
		vx = vabs * cos(phi);
		vy = vabs * sin(phi);

		x += 0.5 * (vabs*cos(heun1)+vx) * dt;
		y += 0.5 * (vabs*sin(heun1)+vy) * dt;

}

