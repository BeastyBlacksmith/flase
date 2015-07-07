
#ifndef _MEASURE_H
#define _MEASURE_H

#include <string>
#include <iostream>
#include <fstream>

#include "common.h"
#include "World.h"
#include "VoidMeasure.h"

class Measure : public VoidMeasure
{
public:
    
    Measure( size_t skip, std::string filename );
    ~Measure();

    void measure( const World& world, const real time );
    void operator()( const World& world, const real time ) { return measure( world, time ); }

    const std::string file;

private:
    real mqdNorm = 1.;
    real msdNorm = 1.;
    real mqdValue = 0.;
    real msdValue = 0.;

    size_t skip;
    size_t skipcounter;
    std::ofstream out;
};

#endif // _MEASURE_H
