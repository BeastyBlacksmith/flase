

#include "common.h"
#include "ClusterTimeSimulation.h"

using namespace std;

ClusterTimeSimulation::ClusterTimeSimulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng, Measure& measure, real dt, real msdThreshold, real mqdThreshold, int condition ) :
    Simulation( plotter, meanSheepDiffusionTime, rng, measure ),
    measure( measure ),
    dt( dt ),
    msdThreshold( msdThreshold ),
    mqdThreshold( mqdThreshold ),
    condition( condition)
{
}

real ClusterTimeSimulation::run( )
{
    World& world = World::instance();
    
    switch( condition )
    {
    case 0:
    {
        while( measure.getMSD() < msdThreshold ) {
            iterate( dt );


            measure( world, time );
            plotter.plot( world, time );
            time += dt;
        }
        break;
    }
    case 1:
    {
        while( measure.getMQD() > mqdThreshold ) {
            iterate( dt );


            measure( world, time );
            plotter.plot( world, time );
            time += dt;
        }
        break;
    }
    case 2:
    {
        while( measure.getMSD() < msdThreshold && measure.getMQD() > mqdThreshold ) {
            iterate( dt );


            measure( world, time );
            plotter.plot( world, time );
            time += dt;
        }
        break;
    }
    default:
        std::cerr<< " Check breaking condition !! It is " << condition <<" right now." <<endl;
        break;
    }
    
    return time;
}

