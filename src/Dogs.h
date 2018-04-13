
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
#ifndef _DOGS_H
#define _DOGS_H

#include <vector>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "common.h"

#include "Motion.h"
#include "Sheep.h"

#include "Dogs/Doggy.h"

class Dogs
{
public:

    Dogs( Motion& motion );
    
    Dogs( const Dogs &that );
    
    Dogs &operator=( const Dogs &that );
    ~Dogs();
    virtual void init( size_t nDogs, real v0 );
    
    void init( size_t nDogs, real v0, double boxsize, gsl_rng* const rng );

    Doggy& operator[]( size_t i ) const { return *dogs[i]; }
    size_t size() const { return dogs.size(); }

    void work( real dt );
    
    double getV0() const { return v0; }
    
    Motion* motion;

    const std::vector< Doggy* >& getDogs() const { return dogs; }

protected:
    
    void copyDogs( std::vector<Doggy*> those );
    std::vector< Doggy* > dogs;

private:
    
    real v0{ 0 };
};

#endif // _DOGS_H
