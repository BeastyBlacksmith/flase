

#ifndef _VOIDMEASURE_H
#define _VOIDMEASURE_H

#include <string>

#include "common.h"
#include "World.h"
#include "Sheep.h"

class VoidMeasure
{
public:
    
    VoidMeasure( size_t skip );
    virtual ~VoidMeasure();

    virtual void measure( const World& world, const real time );
    virtual void operator()( const World& world, const real time ) { return measure( world, time ); }

    virtual void init();
    virtual real getMQD() { return mqdValue; }
    virtual real getMSD() { return msdValue; }

    virtual std::string getFile() { return file; }
protected:

    static real meanQuadraticDistance( const Sheep& sheep );
    static real meanSquareDisplacement( const Sheep& sheep );

private:
    const std::string file;
    real mqdNorm = 1.;
    real msdNorm = 1.;
    real mqdValue = 0.;
    real msdValue = 0.;

    size_t skip;
    size_t skipcounter;
};

#endif // _VOIDMEASURE_H
