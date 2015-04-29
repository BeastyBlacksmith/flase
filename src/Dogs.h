
#ifndef _DOGS_H
#define _DOGS_H

#include <vector>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "common.h"

#include "Motion.h"
#include "Sheep.h"

#include "Doggy.h"

class Dogs
{
public:

    Dogs( Motion& motion );
    ~Dogs();
    virtual void init( size_t nDogs, real v0 );

    Doggy& operator[]( size_t i ) const { return *dogs[i]; }
    size_t size() const { return dogs.size(); }

    void work( real dt );

    Motion& motion;

    const std::vector< Doggy* >& getDogs() const { return dogs; }

protected:

    std::vector< Doggy* > dogs;
};

#endif // _DOGS_H
