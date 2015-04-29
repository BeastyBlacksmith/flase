
#include <math.h>

#include "Sheep.h"
#include "World.h"

using namespace std;

real Sheep::sqrdistance( size_t i1, size_t j1, size_t i2, size_t j2 ) const
{
    const double d1 = min( abs( (int)i1 - (int)i2 ), (int)size() - abs( (int)i1 - (int)i2 ) );
    const double d2 = min( abs( (int)i2 - (int)i2 ), (int)size() - abs( (int)i2 - (int)i2 ) );

    return d1*d1 + d2*d2;
}

void Sheep::init( size_t totalSheep )
{
    for( size_t k = 0; k < totalSheep; ++k )
    {
        const size_t i = gridsize * gsl_rng_uniform( rng );
        const size_t j = gridsize * gsl_rng_uniform( rng );
        const size_t nsheep = getNSheep( i, j );
        setNSheep( i, j, nsheep+1 );
    }
    currentSheep = totalSheep;
    kickSheep();
}

void Sheep::setNSheep( size_t i, size_t j, size_t nSheep )
{
    const size_t oldNSheep = _setNSheep( i, j, nSheep );

    currentSheep += (int)nSheep - (int)oldNSheep;
}

void Sheep::kickSheep()
{
    while( !diffusionCandidates.empty() )
    {
        pair< size_t, size_t > coords = diffusionCandidates.front();
        diffusionCandidates.pop();

        const size_t nSheep = getNSheep( coords.first, coords.second );

        if( nSheep <= capacity )
            continue;

        diffuseSheep( coords.first, coords.second );
    }
}

void Sheep::diffuseSheep( size_t i, size_t j )
{
    // sheep is running away...
    // TODO speedup this part..
    const size_t nSheep = getNSheep( i, j );

    if( nSheep == 0 )
        return;

    setNSheep( i, j, nSheep-1 );

    // do a random walk with pbc
    int r;
    r = 4 * gsl_rng_uniform( rng );
    switch(r)
    {
    case 0:
        ++i;
        if( i >= gridsize )
            i = 0;
        break;
    case 1: 
        if( i == 0 ) {
            i = gridsize-1;
            break;
        }
        --i;
        break;
    case 2: 
        ++j;
        if( j >= gridsize )
            j = 0;
        break;
    case 3: 
        if( j == 0 ) {
            j = gridsize-1;
            break;
        }
        --j;
        break;
    }

    // and settle down
    const size_t newNSheep = getNSheep( i, j );
    setNSheep( i, j, newNSheep+1 );
}

void Sheep::getCenterOfMass( real& x, real& y ) const
{
    size_t i;
    size_t j;
    size_t n;

    double xt1 = 0;
    double yt1 = 0;
    double xt2 = 0;
    double yt2 = 0;
    double pi = 4 * atan(1);
    double r = size()/2./pi;
    double phi1, phi2;

    World& world = World::instance();

    if( first( i, j, n ) ) {
        xt1 += n * cos( i/r );
        yt1 += n * sin( i/r ); 
        xt2 += n * cos( j/r );
        yt2 += n * sin( j/r ); 

        while( next( i, j, n ) ) {
            xt1 += n * cos( i/r );
            yt1 += n * sin( i/r ); 
            xt2 += n * cos( j/r );
            yt2 += n * sin( j/r ); 
        }
    }
    if( xt1 == 0 && yt1 == 0 ) phi1 = 2*pi* (double) rand()/RAND_MAX;
    else phi1 = atan2( yt1,xt1 );
    if( phi1 < 0. ) phi1 += 2*pi;
    if( xt2 == 0 && yt2 == 0 ) phi2 = 2*pi* (double) rand()/RAND_MAX;
    else phi2 = atan2( yt2,xt2 );
    if( phi2 < 0. ) phi2 += 2*pi;

    x = phi1*world.boxsize/2./pi;
    y = phi2*world.boxsize/2./pi;
}

