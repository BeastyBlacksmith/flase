
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

void SheepTree::setNSheep( size_t i, size_t j, size_t nSheep )
{
    if( nSheep > 0 )
    {
        Tree::const_iterator it = tree.find_exact( Point( i, j ) );

        if( it != tree.end() ) {
            *it->counter = nSheep;
        }
        else
            tree.insert( Point( i, j, nSheep ) );
    }
    else {
        tree.erase_exact( Point( i, j ) );
    }

    if( nSheep > capacity )
        diffusionCandidates.emplace( i, j );

    //tree.optimise();
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

