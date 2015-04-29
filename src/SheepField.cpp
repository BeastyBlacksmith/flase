
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

void SheepField::setNSheep( size_t i, size_t j, size_t nSheep )
{
    field[ getIndex( i, j ) ] = nSheep;

    if( nSheep > capacity )
        diffusionCandidates.emplace( i, j );
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
