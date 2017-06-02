
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
#include "SheepTree.h"

using namespace std;

SheepTree::SheepTree( const size_t gridsize, const size_t capacity, gsl_rng* const rng ) :
    Sheep( gridsize, capacity, rng )
{
}

size_t SheepTree::getNSheep( size_t i, size_t j ) const
{
    Tree::const_iterator it = tree.find_exact( Point( i, j ) );

    if( it != tree.end() )
        return *it->counter;
    else
        return 0;
}

size_t SheepTree::_setNSheep( size_t i, size_t j, size_t nSheep )
{
    size_t old = 0;

    if( nSheep > 0 )
    {
        Tree::const_iterator it = tree.find_exact( Point( i, j ) );

        if( it != tree.end() ) {
            old = *it->counter;
            *it->counter = nSheep;
        }
        else
            tree.insert( Point( i, j, nSheep ) );
    }
    else {
        Tree::const_iterator it = tree.find_exact( Point( i, j ) );

        if( it != tree.end() ) {
            old = *it->counter;
            tree.erase( it );
        }
    }

    if( nSheep > capacity )
        diffusionCandidates.emplace( i, j );

    //tree.optimise();

    return old;
}

void SheepTree::getRandomSheep( size_t& i, size_t& j ) const
{
    size_t index = floorl( tree.size() * gsl_rng_uniform( rng ) );

    Tree::const_iterator it = tree.begin();
    for( size_t i = 0; i < index; ++i )
        ++it;

    i = it->d[0];
    j = it->d[1];
}

bool SheepTree::first( size_t& i, size_t& j, size_t& n ) const
{
    Tree::const_iterator it = tree.begin();
    if( it == tree.end() )
        return false;

    i = it->d[0];
    j = it->d[1];
    n = *it->counter;

    return true;
}

bool SheepTree::next( size_t& i, size_t& j, size_t& n ) const
{
    Tree::const_iterator it = tree.find_exact( Point( i, j ) );

    if( it == tree.end() )
        return false;
    ++it;
    if( it == tree.end() )
        return false;

    i = it->d[0];
    j = it->d[1];
    n = *it->counter;

    return true;
}

