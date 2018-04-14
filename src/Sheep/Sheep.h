
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
#ifndef _SHEEP_H
#define _SHEEP_H

#include <queue>
#include <utility>
#include <iostream>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "common.h"

class Sheep {

public:

    Sheep( const size_t gridsize, const size_t capacity, gsl_rng* const rng ) :
        rng( rng ),
        gridsize( gridsize ),
        capacity( capacity ),
        currentSheep( 0 )
    {
    }
    virtual ~Sheep() {}

    virtual void init( size_t totalSheep );
    virtual size_t getNSheep( size_t i, size_t j ) const = 0;
    void setNSheep( size_t i, size_t j, size_t nSheep );
    virtual void getRandomSheep( size_t& i, size_t& j ) const = 0;

    real sqrDistance( size_t i1, size_t j1, size_t i2, size_t j2 ) const;
    real realSpaceSqrDistance( size_t i1, size_t j1, real x, real y ) const;

    virtual bool first( size_t& i, size_t& j, size_t& n ) const = 0;
    virtual bool next( size_t& i, size_t& j, size_t& n ) const = 0;

    size_t getCapacity() const { return capacity; }
    size_t getCurrentSheep() const { return currentSheep; }
    real getClusterRadius() const;

    void kickSheep();
    void diffuseSheep( size_t i, size_t j );

    size_t size() const { return gridsize; }

    void getCenterOfMass( real& x, real& y ) const;

protected:
    
    gsl_rng* const rng;
    const size_t gridsize;
    const size_t capacity;
    size_t currentSheep;

    std::queue< std::pair< size_t, size_t > > diffusionCandidates;

    virtual size_t _setNSheep( size_t i, size_t j, size_t nSheep ) = 0;
};

#endif // _SHEEP_H
