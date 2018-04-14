
/*
Copyright (C) 2017  Simon Christ <c.O_o.l@web.de>, Jörg Bachmann <explicit@explicits.de>

This program is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _WORLD_H
#define _WORLD_H

#include <vector>

#include "common.h"

#include "Sheep/Sheep.h"
#include "Dogs/Dogs.h"

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
