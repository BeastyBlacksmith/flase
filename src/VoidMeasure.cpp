#include <math.h>

#include "World.h"
#include "Sheep.h"

#include "VoidMeasure.h"

VoidMeasure::VoidMeasure( size_t skip ) : 
    file( "noFile" ),
    mqdValue( 1 ),
    msdValue( 0 ),
    skip( skip ),
    skipcounter( 0 )
{
}

VoidMeasure::~VoidMeasure()
{
}


void VoidMeasure::init( )
{
    World& world = World::instance();

    mqdNorm = meanQuadraticDistance( world.sheep );
}

void VoidMeasure::measure( const World& world, real time )
{
    if( skipcounter % skip == 0 )
    {
        // center of mass
            real x;
            real y;

            world.sheep.getCenterOfMass( x, y );
        
        real dl = world.boxsize / world.sheep.size();
        real rcl = world.sheep.getClusterRadius() ;

        msdNorm =  rcl * rcl /  2 + rcl * dl / 2;
        msdValue = ( msdNorm / meanSquareDisplacement( world.sheep ) ); 
        mqdValue = ( meanQuadraticDistance( world.sheep ) / mqdNorm );

    }

    ++skipcounter;
}

real VoidMeasure::meanQuadraticDistance( const Sheep& sheep )
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

real VoidMeasure::meanSquareDisplacement( const Sheep& sheep )
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
