//
// Created by loki on 04.04.17.
//

#include "Measure.h"

Measure::Measure(size_t skip, std::string filename) :
        file( filename ),
        mqdValue( 1 ),
        msdValue( 0 ),
        skip( skip ),
        skipcounter( 0 ),
        out( filename )
{
}

real Measure::meanQuadraticDistance( const Sheep& sheep )
{
    //TODO: real space distance?_?
    size_t i1, j1, n1;
    size_t i2, j2, n2;

    double mean = 0;
    size_t counter = 0;

    if( sheep.first( i1, j1, n1 ) ) {
        i2 = i1;
        j2 = j1;
        n2 = n1;

        while( sheep.next( i2, j2, n2 ) ) {
            mean += n1*n2*sheep.sqrDistance( i1, j1, i2, j2 );
            counter += n1*n2;
        }

        while( sheep.next( i1, j1, n1 ) ) {
            i2 = i1;
            j2 = j1;
            n2 = n1;

            while( sheep.next( i2, j2, n2 ) ) {
                mean += n1*n2*sheep.sqrDistance( i1, j1, i2, j2 );
                counter += n1*n2;
            }
        }
    }

    return mean / counter;
}

real Measure::meanSquareDisplacement( const Sheep& sheep )
{
    size_t i, j, n;
    double cmx, cmy;

    double mean = 0;
    size_t counter = 0;

    sheep.getCenterOfMass( cmx, cmy );

    if( sheep.first( i, j, n ) ) {
        mean += n*sheep.realSpaceSqrDistance( i, j, cmx, cmy );
        counter += n;

        while( sheep.next( i, j, n ) ) {
            mean += n*sheep.realSpaceSqrDistance( i, j, cmx, cmy );
            counter += n;
        }
    }

    return mean / counter;
}
