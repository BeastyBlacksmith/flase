
#include "common.h"
#include "DoMeasure.h"

using namespace std;

DoMeasure::DoMeasure( size_t skip, string filename ) :
    Measure( ),
    file( filename ),
    mqdValue( 1 ),
    msdValue( 0 ),
    skip( skip ),
    skipcounter( 0 ),
    out( filename )
{
}

DoMeasure::~DoMeasure()
{
    out.flush();
}

void DoMeasure::init( )
{
    World& world = World::instance();

    mqdNorm = meanQuadraticDistance( world.sheep );
}

void DoMeasure::measure( const World& world, real time )
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

        {
            out << x << "\t" << y << "\t";

            out << mqdValue << "\t";
            out << msdValue << "\t";
            out << time;
            out << "\n\n\n";
        }
        
        //output: cmx cmy MQD MSD time (triple newline for gnuplot compability)
    }

    ++skipcounter;
}


