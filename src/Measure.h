
#ifndef _MEASURE_H
#define _MEASURE_H

#include <string>
#include <iostream>
#include <fstream>

#include "common.h"
#include "Sheep.h"

class Measure {
public:
    
    //TODO: complete this and crack!
    Measure( size_t skip, std::string filename );
    ~Measure();

    void measure( const Sheep& sheep );
    void operator()( const Sheep& sheep ) { return measure( sheep ); }

    const std::string file;

protected:

    static real meanQuadraticDistance( const Sheep& sheep );
    static real meanSquareDisplacement( const Sheep& sheep );

private:

    size_t skip;
    size_t skipcounter;
    std::ofstream out;
};

#endif // _MEASURE_H
