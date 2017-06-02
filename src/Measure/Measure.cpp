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
//
// Created by loki on 04.04.17.
//

#include "Measure.h"

Measure::Measure( size_t skip, std::string filename) :
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
