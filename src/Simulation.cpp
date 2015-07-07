
#include "common.h"
#include "World.h"

#include "Simulation.h"

Simulation::Simulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng, VoidMeasure& measure ) :
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

