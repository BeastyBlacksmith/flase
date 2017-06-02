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

#ifndef _MEASURE_H
#define _MEASURE_H

#include <string>
#include <iostream>
#include <fstream>

#include "common.h"
#include "World.h"
#include "VoidMeasure.h"

class DoMeasure : public Measure
{
public:
    
    DoMeasure( size_t skip, std::string filename );
    
    ~DoMeasure();
    
    void measure( const World& world, const real time );
    
    void operator()( const World& world, const real time ) { return measure( world, time ); }
    
    void init();
    
    real getMQD() { return mqdValue; }
    
    real getMSD() { return msdValue; }
    
    std::string getFile() { return file; }
    
};

#endif // _MEASURE_H
