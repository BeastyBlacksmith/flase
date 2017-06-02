
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
#ifndef _SHEEPFIELD_H
#define _SHEEPFIELD_H

#include <vector>

#include "Sheep.h"

class SheepField : public Sheep {

public:

    SheepField( const size_t gridsize, const size_t capacity, gsl_rng* const rng );

    size_t getNSheep( size_t i, size_t j ) const;
    void getRandomSheep( size_t& i, size_t& j ) const;

    bool first( size_t& i, size_t& j, size_t& n ) const;
    bool next( size_t& i, size_t& j, size_t& n ) const;

protected:
    size_t _setNSheep( size_t i, size_t j, size_t nSheep );

private:

    size_t getIndex( size_t i, size_t j ) const;
    void getCoords( size_t k, size_t& i, size_t& j ) const;

    std::vector< size_t > field;

};

#endif // _SHEEPFIELD_H
