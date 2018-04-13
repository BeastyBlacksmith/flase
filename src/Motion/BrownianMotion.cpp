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
#include <iostream>

#include "BrownianMotion.h"

BrownianMotion::BrownianMotion() :
        Motion( 0, nullptr ),
        friction( 0 )
{
    persistenceLength = 0;
    persistenceTime = 0;
    effectiveDiffusion = 0;
}

BrownianMotion::BrownianMotion( real noise, gsl_rng* const rng, real friction ) :
        Motion( noise, rng ),
        friction( friction )
{
    persistenceLength = sqrt( noise / friction );
    persistenceTime = 1. / friction;
    effectiveDiffusion = noise;
}

void BrownianMotion::step( real& x, real& y, real& vx, real& vy, real dt ) const
{
    vx -= friction * vx * dt - sqrt( 2 * noise * friction *dt ) *gsl_ran_gaussian( rng, 1. );
    vy -= friction*vy*dt - sqrt( 2*noise*friction*dt )*gsl_ran_gaussian( rng, 1. );
    
    x += vx*dt;
    y += vy*dt;
}
