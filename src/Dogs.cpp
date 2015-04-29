
#include <iostream>

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
    
    for( size_t i = 0; i < nDogs; ++i ) {
        dogs[i] = new Doggy;
        dogs[i]->x = world.boxsize * gsl_rng_uniform( world.rng ); 
        dogs[i]->y = world.boxsize * gsl_rng_uniform( world.rng );
        dogs[i]->vx = 0;
        dogs[i]->vy = v0;
         
    }
}

void Dogs::work( real dt )
{
//#   pragma omp parallel for
    for( size_t i = 0; i < dogs.size(); ++i ) {
        dogs[i]->work( dt );
    }
}

