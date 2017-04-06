
#ifndef _SIMULATION_H
#define _SIMULATION_H

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "common.h"
#include "HarryPlotter.h"
#include "Measure.h"

class Simulation
{
public:

    Simulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng, Measure& measure );
    virtual ~Simulation() {}

    virtual real run( ) = 0;

protected:

    void iterate( real dt );

    HarryPlotter& plotter;

    gsl_rng* const rng;

    real time;
    real tsheepboredom;
    real meanSheepDiffusionTime;

    Measure& measure;
};

#endif // _SIMULATION_H
