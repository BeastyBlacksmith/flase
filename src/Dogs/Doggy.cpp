
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
