
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

#ifndef _CLUSTERTIMESIMULATION_H
#define _CLUSTERTIMESIMULATION_H

#include "common.h"

#include "Simulation.h"
#include "Measure/Measure.h"

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
