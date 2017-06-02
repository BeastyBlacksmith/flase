
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
#include <math.h>

#include "SheepField.h"

SheepField::SheepField( const size_t gridsize, const size_t capacity, gsl_rng* const rng ) :
    Sheep( gridsize, capacity, rng )
{
    // initialize a quadratic field
    field.resize( gridsize*gridsize );
}

size_t SheepField::getNSheep( size_t i, size_t j ) const
{
    return field[ getIndex( i, j ) ];
}

size_t SheepField::_setNSheep( size_t i, size_t j, size_t nSheep )
{
    const size_t index = getIndex( i, j );
    const size_t old = field[ index ];
    field[ index ] = nSheep;

    if( nSheep > capacity )
        diffusionCandidates.emplace( i, j );

    return old;
}

void SheepField::getRandomSheep( size_t& i, size_t& j ) const
{
    size_t index = floorl( field.size() * gsl_rng_uniform( rng ) );

    for( ; index < field.size() && field[index] == 0; ++index );
    if( index == field.size() )
        for( index = 0; index < field.size() && field[index] == 0; ++index );

    i = index % gridsize;
    j = index / gridsize;
}

size_t SheepField::getIndex( size_t i, size_t j ) const
{
    return i + gridsize*j;
}

void SheepField::getCoords( size_t k, size_t& i, size_t& j ) const
{
    i= k % gridsize;
    j = k / gridsize;
}

bool SheepField::first( size_t& i, size_t& j, size_t& n ) const
{
    for(size_t k=0; k<field.size(); k++)
    {
        if( field[k] > 0 )
        {
            getCoords( k, i, j );
            n = getNSheep( i, j );
            return true;
        }
    }
    return false;
}

bool SheepField::next( size_t& i, size_t& j, size_t& n ) const
{
    size_t k = getIndex(i,j)+1;
    for(; k<field.size(); k++)
    {
        if( field[k] > 0 )
        {
            getCoords( k, i, j );
            n=getNSheep( i, j );
            return true;
        }

    }
    return false;
}
