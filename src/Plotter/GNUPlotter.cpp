/*
Copyright (C) 2017  Simon Christ <c.O_o.l@web.de>, Jörg Bachmann <explicit@explicits.de>

This program is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <math.h>

#include "common.h"
#include "World.h"
#include "Measure/VoidMeasure.h"

#include "GNUPlotter.h"

using namespace std;

GNUPlotter::GNUPlotter(
        Measure& measure,
        size_t skip,
        real vecsize,
        string sheepdat,
        string dogsdat,
        string gnuplotscript ) :
        measure( measure ),
        skip( skip ),
        counter( 0 ),
        vecsize( vecsize ),
        sheepdat( sheepdat ),
        dogsdat( dogsdat ),
        outMaeh( sheepdat ),
        outWuff( dogsdat ),
        outGnuPlot( gnuplotscript )
{
}

GNUPlotter::~GNUPlotter()
{
    outMaeh.flush();
    outWuff.flush();
    
    outGnuPlot << "pause -1" <<"\n";
    outGnuPlot.flush();
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
    if( counter % skip == 0 ) {
        real scale = world.boxsize / world.sheep.size();
        
        outMaeh << world.sheep << "\n" << "\n";
        outWuff << world.dogs << "\n" << "\n";
        
        outGnuPlot << "set size square" << "\n";
        outGnuPlot << "set terminal wxt size 750,750" << "\n";
        outGnuPlot << "unset key" << "\n";
        outGnuPlot << "set cbrange [1:3]" << "\n";
        outGnuPlot << "set cbtics 1,1,3" << "\n";
        outGnuPlot << "set xrange[0:" << world.boxsize << "];set yrange[0:" << world.boxsize << "];" << "\n";
        outGnuPlot << "set title \" time=" << time << ", Cluster=" << measure.getMSD() <<" / " << measure.getMQD() << "\"\n";
        outGnuPlot << "set palette model RGB defined (1 \"red\", 2 \"black\", 3 \"green\")" << "\n";
        outGnuPlot << "set palette maxcolors 3\n";
        outGnuPlot << "pl \"" << dogsdat << "\" i " << ( counter / skip ) << " u 1:2:($3*" << vecsize << "):($4*"
                << vecsize << "):5 w vectors palette,";
        outGnuPlot << "\"" << sheepdat << "\" i " <<  ( counter/skip ) << " u ($1*" << scale <<"):($2*" << scale  <<"):(" << ( scale/2 ) <<") w circles lc 3, ";
        outGnuPlot << "\"" << measure.getFile() << "\" i " << ( counter/skip ) << " u 1:2:(" << world.sheep.getClusterRadius() <<") with circles lc 4\n";
        outGnuPlot << "pause 0.04" << "\n" << "\n";
    }
    
    ++counter;
}
