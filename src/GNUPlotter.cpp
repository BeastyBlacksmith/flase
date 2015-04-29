
#include "common.h"
#include "World.h"

#include "GNUPlotter.h"

using namespace std;

GNUPlotter::GNUPlotter(
            size_t skip,
            real vecsize,
            string sheepdat,
            string oscillator,
            string gnuplotscript ) :
    skip( skip ),
    counter( 0 ),
    vecsize( vecsize ),
    outMaeh( sheepdat ),
    outWuff( oscillator ),
    outGnuPlot( gnuplotscript )
{
}

std::ostream& operator<<( std::ostream &out, const Sheep& sheep )
{
    size_t i, j, n;

    if( sheep.first( i, j, n ) )
    {
        out << i << "\t" << j << "\t" << n << "\n";

        while( sheep.next( i, j, n ) )
        {
            out << i << "\t" << j << "\t" << n << "\n";
        }
    }

    return out;
}

std::ostream& operator<<( std::ostream &out, const Dogs& dogs )
{
    const std::vector< Doggy* >& v = dogs.getDogs();

    for( auto i = v.begin(); i != v.end(); ++i ) {
        const Doggy& dog = **i;

        out << dog.x << "\t" << dog.y << "\t" << dog.vx << "\t" << dog.vy << "\t" << dog.getState() << "\n";
    }

    return out;
}

void GNUPlotter::plot( World& world, real time )
{
    //TODO flush at end of simulation.
    if( counter % skip == 0 ) {
        outMaeh << world.sheep << "\n" << "\n";
        outWuff << world.dogs << "\n" << "\n";

        outGnuPlot << "set size square" << "\n";
        outGnuPlot << "unset key" << "\n";
        outGnuPlot << "set cbrange [1:3]" << "\n";
        outGnuPlot << "set xrange[0:" << world.sheep.size() << "];set yrange[0:" << world.sheep.size() << "];" << "\n";
        outGnuPlot << "set title \" time=" << time << " \" " << "\n";
        outGnuPlot << "set palette model RGB defined (1 \"red\", 2 \"black\", 3 \"green\")" << "\n";
        outGnuPlot << "pl \"" << oscillator << "\" i " << ( counter/skip ) << " u 1:2:($3*" << vecsize << "):($4*" << vecsize << "):5 w vectors palette, \"" << sheepdat << "\" i " <<  ( counter/skip ) << " u 1:2 lt 3" << "\n";
        outGnuPlot << "pause 0.1" << "\n" << "\n";
    }

    ++counter;
}
