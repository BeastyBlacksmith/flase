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

#ifndef SHEEPNDOGS_MEASURE_H
#define SHEEPNDOGS_MEASURE_H

#include <fstream>
#include "World.h"

class Measure
{
public:

    Measure(size_t skip, std::string filename);
    virtual ~Measure() {}
    virtual void measure( const World& world, const real time) = 0;
    void operator()( const World& world, const real time ) { return measure( world, time ); }

    virtual void init() = 0;
    virtual real getMQD() = 0;
    virtual real getMSD() = 0;

    virtual std::string getFile() = 0;

protected:

    static real meanQuadraticDistance( const Sheep& sheep );
    static real meanSquareDisplacement( const Sheep& sheep );

    const std::string file;

    real mqdNorm = 1.;
    real msdNorm = 1.;
    real mqdValue = 0.;
    real msdValue = 0.;

    size_t skip;
    size_t skipcounter;
    std::ofstream out;
};
#endif //SHEEPNDOGS_MEASURE_H
