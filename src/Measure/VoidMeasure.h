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


#ifndef _VOIDMEASURE_H
#define _VOIDMEASURE_H

#include <string>
#include <Measure.h>

#include "common.h"
#include "World.h"
#include "Sheep.h"


class VoidMeasure : public Measure
{
public:
    
    VoidMeasure( size_t skip );
    
    virtual ~VoidMeasure();
    
    virtual void measure( const World& world, const real time ) override;
    
    virtual void init() override;
    
    virtual real getMQD() override { return mqdValue; }
    
    virtual real getMSD() override { return msdValue; }
    
    virtual std::string getFile() override { return file; }
};

#endif // _VOIDMEASURE_H
