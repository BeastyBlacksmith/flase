//
// Created by loki on 04.04.17.
//

#ifndef SHEEPNDOGS_MEASURE_H
#define SHEEPNDOGS_MEASURE_H

#include <fstream>
#include "World.h"

class Measure
{
public:

    Measure(size_t skip, std::string filename);
    virtual ~Measure() {}
    virtual void measure( const World& world, const real time) = 0;
    void operator()( const World& world, const real time ) { return measure( world, time ); }

    virtual void init() = 0;
    virtual real getMQD() = 0;
    virtual real getMSD() = 0;

    virtual std::string getFile() = 0;

protected:

    static real meanQuadraticDistance( const Sheep& sheep );
    static real meanSquareDisplacement( const Sheep& sheep );

    const std::string file;

    real mqdNorm = 1.;
    real msdNorm = 1.;
    real mqdValue = 0.;
    real msdValue = 0.;

    size_t skip;
    size_t skipcounter;
    std::ofstream out;
};
#endif //SHEEPNDOGS_MEASURE_H
