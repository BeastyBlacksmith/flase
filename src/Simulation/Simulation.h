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
#ifndef _SIMULATION_H
#define _SIMULATION_H

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "common.h"
#include "Plotter/HarryPlotter.h"
#include "Measure/Measure.h"

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
