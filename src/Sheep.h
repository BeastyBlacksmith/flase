
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

    virtual void init( size_t totalSheep );
    virtual size_t getNSheep( size_t i, size_t j ) const = 0;
    void setNSheep( size_t i, size_t j, size_t nSheep );
    virtual void getRandomSheep( size_t& i, size_t& j ) const = 0;

    real sqrDistance( size_t i1, size_t j1, size_t i2, size_t j2 ) const;
    real realSpaceSqrdistance( size_t i1, size_t j1, real x, real y ) const;

    virtual bool first( size_t& i, size_t& j, size_t& n ) const = 0;
    virtual bool next( size_t& i, size_t& j, size_t& n ) const = 0;

    size_t getCapacity() const { return capacity; }
    size_t getCurrentSheep() const { return currentSheep; }

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
