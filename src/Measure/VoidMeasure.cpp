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

