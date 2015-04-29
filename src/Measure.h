
#ifndef _MEASURE_H
#define _MEASURE_H

#include "common.h"

class Measure {
public:
    
    //TODO: complete this and check!
    Measure( ) :
    {
    }

    real distancePbc2D( real x1, real y1, real x2, real y2, real xboundary, real yboundary );
    real centerOfMassPbc1D( Sheep sheep, real boundary );

protected:
    
    real meanSquareDisplacement;
    real meanQuadraticDistance;
    real centerOfMassX;
    real centerOfMassY;
    real clusterRadius;

};

#endif // _MEASURE_H
