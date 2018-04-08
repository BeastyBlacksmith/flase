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

#include <iostream>
#include <math.h>

#include "common.h"
#include "OpenMP.h"
#include "Dogs.h"
#include "World.h"

Dogs::Dogs( Motion& motion ) :
        motion( motion )
{
}

Dogs::~Dogs()
{
    for( size_t i = 0; i < dogs.size(); ++i ) {
        delete dogs[i];
    }
}

void Dogs::init( size_t nDogs, real v0 )
{
    dogs.resize( nDogs );
    
    World& world = World::instance();
    real vabs = v0;
    real phi = 0;
    
    
    for( size_t i = 0; i < nDogs; ++i ) {
        phi = 2 * Constants::pi * gsl_rng_uniform( world.rng );
        
        dogs[i] = new Doggy;
        dogs[i]->x = world.boxsize * gsl_rng_uniform( world.rng );
        dogs[i]->y = world.boxsize * gsl_rng_uniform( world.rng );
        dogs[i]->vx = vabs * cos( phi );
        dogs[i]->vy = vabs * sin( phi );
        
    }
}

void Dogs::init( size_t nDogs, real v0, double boxsize, gsl_rng* const rng )
{
    dogs.resize( nDogs );
    
    real vabs = v0;
    real phi = 0;
    
    for( size_t i = 0; i < nDogs; ++i )
    {
        phi = 2 * Constants::pi * gsl_rng_uniform( rng );
        
        dogs[i] = new Doggy;
        dogs[i]->x = boxsize * gsl_rng_uniform( rng );
        dogs[i]->y = boxsize * gsl_rng_uniform( rng );
        dogs[i]->vx = vabs * cos( phi );
        dogs[i]->vy = vabs * sin( phi );
        
    }
}

void Dogs::work( real dt )
{
//#   pragma omp parallel for
    for( size_t i = 0; i < dogs.size(); ++i ) {
        dogs[i]->work( dt );
    }
}

