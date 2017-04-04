

#ifndef _CLUSTERTIMESIMULATION_H
#define _CLUSTERTIMESIMULATION_H

#include "common.h"

#include "Simulation.h"
#include "Measure.h"

class ClusterTimeSimulation : public Simulation
{
public:

    ClusterTimeSimulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng, Measure& measure, real dt, const real msdThreshold = 0.7, const real mqdThreshold = 0.1, const int condition = 0 );

    real run( );

protected:

    Measure& measure;
    const real dt;
    const real msdThreshold;
    const real mqdThreshold;
    const int condition;
};


#endif // _CLUSTERTIMESIMULATION_H
