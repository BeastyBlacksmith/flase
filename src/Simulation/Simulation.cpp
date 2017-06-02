
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
#include "common.h"
#include "World.h"

#include "Simulation.h"

Simulation::Simulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng, Measure& measure ) :
    plotter( plotter ),
    rng( rng ),
    time( 0 ),
    meanSheepDiffusionTime( meanSheepDiffusionTime ),
    measure( measure )
{
    World& world = World::instance();

    tsheepboredom = gsl_ran_exponential( rng,  meanSheepDiffusionTime / world.sheep.getCurrentSheep() );
}

void Simulation::iterate( real dt )
{
    World& world = World::instance();

    // move dogs
    {
        world.moveDogs( dt );
    }

    // move sheep
    {
        // TODO: make this individual?
        // move random sheep
        if( time >= tsheepboredom )
        {
            size_t i = 0;
            size_t j = 0;
            world.sheep.getRandomSheep( i, j );
            world.sheep.diffuseSheep( i, j );

            tsheepboredom = time + gsl_ran_exponential( rng, meanSheepDiffusionTime  / world.sheep.getCurrentSheep()  );
        }

        // get into a consistent state, i.e. fight!
        // nicht draengeln!
        world.sheep.kickSheep();
    }

    // doggy, wakeup!
    {
        world.dogs.work( dt );
    }

    // do measurements (moved to FiniteSimulation, since not needed for InfinteSimulation) 
}

