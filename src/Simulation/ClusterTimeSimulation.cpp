
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

#include "common.h"
#include "ClusterTimeSimulation.h"

using namespace std;

ClusterTimeSimulation::ClusterTimeSimulation( HarryPlotter& plotter, real meanSheepDiffusionTime, gsl_rng* const rng, Measure& measure, real dt, real msdThreshold, real mqdThreshold, int condition ) :
    Simulation( plotter, meanSheepDiffusionTime, rng, measure ),
    measure( measure ),
    dt( dt ),
    msdThreshold( msdThreshold ),
    mqdThreshold( mqdThreshold ),
    condition( condition)
{
}

real ClusterTimeSimulation::run( )
{
    World& world = World::instance();
    
    switch( condition )
    {
    case 0:
    {
        while( measure.getMSD() < msdThreshold ) {
            iterate( dt );


            measure( world, time );
            plotter.plot( world, time );
            time += dt;
        }
        break;
    }
    case 1:
    {
        while( measure.getMQD() > mqdThreshold ) {
            iterate( dt );


            measure( world, time );
            plotter.plot( world, time );
            time += dt;
        }
        break;
    }
    case 2:
    {
        while( measure.getMSD() < msdThreshold && measure.getMQD() > mqdThreshold ) {
            iterate( dt );


            measure( world, time );
            plotter.plot( world, time );
            time += dt;
        }
        break;
    }
    default:
        std::cerr<< " Check breaking condition !! It is " << condition <<" right now." <<endl;
        break;
    }
    
    return time;
}

