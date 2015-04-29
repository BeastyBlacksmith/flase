
#ifndef _SHEEP_H
#define _SHEEP_H

#include <queue>
#include <utility>
#include <iostream>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

class Sheep {

public:

    Sheep( const size_t gridsize, const size_t capacity, gsl_rng* const rng ) :
        rng( rng ),
        gridsize( gridsize ),
        capacity( capacity )
    {
    }

    virtual void init( size_t totalSheep );
    virtual size_t getNSheep( size_t i, size_t j ) const = 0;
    virtual void setNSheep( size_t i, size_t j, size_t nSheep ) = 0;
    virtual void getRandomSheep( size_t& i, size_t& j ) const = 0;

    virtual bool first( size_t& i, size_t& j, size_t& n ) const = 0;
    virtual bool next( size_t& i, size_t& j, size_t& n ) const = 0;

    size_t getCapacity() const { return capacity; }
    size_t getCurrentSheep() const { return currentSheep; }

    void setCurrentSheep(size_t newCurrentSheep) { currentSheep = newCurrentSheep; }
    void kickSheep();
    void diffuseSheep( size_t i, size_t j );

    size_t size() const { return gridsize; }

protected:
    
    gsl_rng* const rng;
    const size_t gridsize;
    const size_t capacity;
    size_t currentSheep;

    std::queue< std::pair< size_t, size_t > > diffusionCandidates;
};

#endif // _SHEEP_H
