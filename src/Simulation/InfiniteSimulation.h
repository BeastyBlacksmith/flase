
#ifndef _INFINITESIMULATION_H
#define _INFINITESIMULATION_H

#include "common.h"

#include "Simulation.h"

class InfiniteSimulation : public Simulation
{
public:

    InfiniteSimulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng, Measure& measure, real dt );

    real run( );

protected:

    const real dt;
};


#endif // _INFINITESIMULATION_H
