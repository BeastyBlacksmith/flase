
#ifndef _WORLD_H
#define _WORLD_H

#include <vector>

#include "common.h"

#include "Sheep.h"
#include "Dogs.h"

class World
{
public:

    static void createInstance( real boxsize, gsl_rng* const rng, real meanSleepyness, real businessRate, real freedomRate, Sheep& sheep, Dogs& dogs );
    static World& instance();

    void moveDogs( real dt );

    void getSheepCoords( real x, real y, size_t& i, size_t& j ) const;

    gsl_rng* const rng;
    const real boxsize;
    const real meanSleepyness;
    const real businessRate;
    const real freedomRate;

    Sheep& sheep;
    Dogs& dogs;

private:

    World( real boxsize, gsl_rng* const rng, real meanSleepyness, real businessRate, real freedomRate, Sheep& sheep, Dogs& dogs );

    // periodic boundary condition 
    void pbc( real& x, real& y ) const;

    static World* singleton;
};

#endif // _WORLD_H
