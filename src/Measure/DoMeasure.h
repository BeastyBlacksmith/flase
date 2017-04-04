
#ifndef _MEASURE_H
#define _MEASURE_H

#include <string>
#include <iostream>
#include <fstream>

#include "common.h"
#include "World.h"
#include "VoidMeasure.h"

class DoMeasure : public Measure
{
public:
    
    DoMeasure( size_t skip, std::string filename );
    ~DoMeasure();

    void measure( const World& world, const real time );
    void operator()( const World& world, const real time ) { return measure( world, time ); }

    void init();
    real getMQD() { return mqdValue; }
    real getMSD() { return msdValue; }

    std::string getFile() { return file; }

};

#endif // _MEASURE_H
