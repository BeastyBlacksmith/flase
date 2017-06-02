
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
