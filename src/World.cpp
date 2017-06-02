
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

