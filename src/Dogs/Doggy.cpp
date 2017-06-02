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

#include <cstddef>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "World.h"
#include "Doggy.h"

void Doggy::move( real dt, Motion& motion )
{
    motion.step( x, y, vx, vy, dt );
}

void Doggy::work( real dt )
{
    World& world = World::instance();
    
    switch( state )
    {
        case ACTIVE:
        {
            size_t i;
            size_t j;
            
            world.getSheepCoords( x, y, i, j );
            const size_t nSheep = world.sheep.getNSheep( i, j );
            
            if( nSheep == 0 )
                break;
            
            if( gsl_rng_uniform( world.rng ) < nSheep * world.businessRate * dt ) {
                // there is a sheep, maehh
                world.sheep.setNSheep( i, j, nSheep-1 );
                
                state = OCCUPIED;
            }
        }
            break;
        
        case OCCUPIED:
        {
            size_t i;
            size_t j;
            
            world.getSheepCoords( x, y, i, j );
            const size_t nSheep = world.sheep.getNSheep( i, j );
            
            if( nSheep == 0 )
                break;
            
            if( gsl_rng_uniform( world.rng ) < nSheep * world.freedomRate * dt ) {
                // there is a sheep, maehh
                world.sheep.setNSheep( i, j, nSheep+1 );
                state = SLEEPY;
                
                // TODO: possibly, this should be exchangeable / overrideable
                sleepyness = gsl_ran_exponential( world.rng, world.meanSleepyness ) / dt;
                //sleepyness is a counter !
            }
        }
            break;
        
        case SLEEPY:
            if( sleepyness == 0 ) {
                state = ACTIVE;
                break;
            }
            
            --sleepyness;
            break;
    }
}
