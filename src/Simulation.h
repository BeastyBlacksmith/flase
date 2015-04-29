
#ifndef _SIMULATION_H
#define _SIMULATION_H

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "HarryPlotter.h"

class Simulation
{
public:

    Simulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng );

    virtual void run( ) = 0;

protected:

    void iterate( real dt );

    HarryPlotter& plotter;

    gsl_rng* const rng;

    real time;
    real tsheepboredom;
    real meanSheepDiffusionTime;
};

#endif // _SIMULATION_H
