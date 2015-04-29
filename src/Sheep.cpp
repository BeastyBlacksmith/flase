
#include "Sheep.h"
#include "World.h"

using namespace std;

void Sheep::init( size_t totalSheep )
{
    for( size_t k = 0; k < totalSheep; ++k )
    {
        const size_t i = gridsize * gsl_rng_uniform( rng );
        const size_t j = gridsize * gsl_rng_uniform( rng );
        const size_t nsheep = getNSheep( i, j );
        setNSheep( i, j, nsheep+1 );
    }
    setCurrentSheep( totalSheep );
    kickSheep();
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

