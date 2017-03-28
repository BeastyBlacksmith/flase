
#include "common.h"
#include "Measure.h"

using namespace std;

Measure::Measure( size_t skip, string filename ) : 
    VoidMeasure( skip ),
    file( filename ),
    mqdValue( 1 ),
    msdValue( 0 ),
    skip( skip ),
    skipcounter( 0 ),
    out( filename )
{
}

Measure::~Measure()
{
    out.flush();
}

void Measure::init( )
{
    World& world = World::instance();

    mqdNorm = meanQuadraticDistance( world.sheep );
}

void Measure::measure( const World& world, real time )
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


