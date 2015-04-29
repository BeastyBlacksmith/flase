
#include "FiniteSimulation.h"

using namespace std;

FiniteSimulation::FiniteSimulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng, Measure& measure, real dt, real judgementtime ) :
    Simulation( plotter, meanSheepDiffusionTime, rng, measure ),
    dt( dt ),
    judgementtime( judgementtime  )
{
}

void FiniteSimulation::run( )
{
    World& world = World::instance();

    size_t i = 0;
    while( time < judgementtime ) {
        iterate( dt );

        time += dt;
        ++i;

        plotter.plot( world, time );
    }
    plotter.plot( world, time );

}

