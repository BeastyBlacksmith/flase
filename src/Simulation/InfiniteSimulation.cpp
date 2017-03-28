
#include "InfiniteSimulation.h"

using namespace std;

InfiniteSimulation::InfiniteSimulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng, VoidMeasure& measure, real dt ) :
    Simulation( plotter, meanSheepDiffusionTime, rng, measure ),
    dt( dt )
{
}

real InfiniteSimulation::run( )
{
    World& world = World::instance();

    size_t i = 0;
    while( true ) {
        iterate( dt );

        time += dt;
        ++i;

        plotter.plot( world, time );
    }
    
    return time;
}

