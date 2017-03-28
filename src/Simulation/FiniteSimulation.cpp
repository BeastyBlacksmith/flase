
#include "common.h"
#include "FiniteSimulation.h"

using namespace std;

FiniteSimulation::FiniteSimulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng, VoidMeasure& measure, real dt, real judgementtime ) :
    Simulation( plotter, meanSheepDiffusionTime, rng, measure ),
    dt( dt ),
    judgementtime( judgementtime  )
{
}

real FiniteSimulation::run( )
{
    World& world = World::instance();

    while( time <= judgementtime ) {
        iterate( dt );

        time += dt;

        measure( world, time );
        plotter.plot( world, time );
    }
    
    return time;
}

