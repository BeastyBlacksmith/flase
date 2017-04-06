
#include <assert.h>
#include <math.h>
#include <cstddef>
#include "World.h"

World* World::singleton( NULL );

void World::createInstance( real boxsize, gsl_rng* const rng, real meanSleepyness, real businessRate, real freedomRate, Sheep& sheep, Dogs& dogs )
{
    if( singleton == NULL )
        singleton = new World( boxsize, rng, meanSleepyness, businessRate, freedomRate, sheep, dogs );
}

World& World::instance()
{
    return *singleton;
}

World::World( real boxsize, gsl_rng* const rng, real meanSleepyness, real businessRate, real freedomRate, Sheep& sheep, Dogs& dogs ) :
    rng( rng ),
    boxsize( boxsize ),
    meanSleepyness( meanSleepyness ),
    businessRate( businessRate ),
    freedomRate( freedomRate ),
    sheep( sheep ),
    dogs( dogs )
{
}

void World::moveDogs( real dt )
{
    for( size_t i = 0; i < dogs.size(); ++i ) {
        Doggy& dog = dogs[i];

        dog.move( dt, dogs.motion );
        pbc( dog.x, dog.y );
    }
}

void World::pbc( real& x, real& y ) const
{
    double tx= fmod( x, boxsize );
    double ty= fmod( y, boxsize );
    
    while (tx < 0.0f) 
        tx += boxsize;
    while (ty < 0.0f) 
        ty += boxsize;

    x=tx;
    y=ty;
    
    assert(y >= 0);
    assert(x >= 0);
}

void World::getSheepCoords( real x, real y, size_t& i, size_t& j ) const
{
     // TODO does this fit? ....
    i = x / boxsize * sheep.size();
    j = y / boxsize * sheep.size();
}

