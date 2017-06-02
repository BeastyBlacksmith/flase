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

#ifndef _GNUPLOTTER_H
#define _GNUPLOTTER_H

#include <string>
#include <iostream>
#include <fstream>

#include "common.h"
#include "HarryPlotter.h"

class GNUPlotter : public HarryPlotter
{
public:
    
    GNUPlotter(
            Measure& measure,
            size_t skip = 1,
            real vecsize = 1.,
            std::string sheepdat = "temp/sheepPosition.dat",
            std::string dogsdat = "temp/dogsPosition.dat",
            std::string gnuplotscript = "havefun.gp" );
    
    ~GNUPlotter();
    
    virtual void plot( World& world, real time );

protected:
    
    Measure& measure;
    size_t skip;
    size_t counter;
    real vecsize;
    std::string sheepdat;
    std::string dogsdat;
    
    std::ofstream outMaeh;
    std::ofstream outWuff;
    std::ofstream outGnuPlot;
};

#endif // _GNUPLOTTER_H
