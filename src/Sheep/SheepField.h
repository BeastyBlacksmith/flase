
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
