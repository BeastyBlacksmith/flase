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

#include <math.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "common.h"
#include "ConstVelocity.h"

ConstVelocity::ConstVelocity() :
        Motion( 0, nullptr )
{
    persistenceTime = 0;
    persistenceLength = 0;
    effectiveDiffusion = 0;
}

ConstVelocity::ConstVelocity( real noise, gsl_rng* const rng, real velocity ) :
		Motion( noise, rng )
{
	persistenceTime = velocity * velocity / noise;
	persistenceLength = persistenceTime * velocity;
	effectiveDiffusion = persistenceLength * velocity / 2.;
}

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

