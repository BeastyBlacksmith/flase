
#ifndef _FINITESIMULATION_H
#define _FINITESIMULATION_H

#include "common.h"

#include "Simulation.h"

class FiniteSimulation : public Simulation
{
public:

    FiniteSimulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng, Measure& measure, real dt, real judgementtime );

    void run( );

protected:

    const real dt;
    const real judgementtime;
};


#endif // _FINITESIMULATION_H
