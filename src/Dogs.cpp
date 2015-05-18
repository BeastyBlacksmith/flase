
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

void Dogs::work( real dt )
{
//#   pragma omp parallel for
    for( size_t i = 0; i < dogs.size(); ++i ) {
        dogs[i]->work( dt );
    }
}

