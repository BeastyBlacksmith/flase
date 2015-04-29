
#ifndef _SHEEPTREE_H
#define _SHEEPTREE_H

#include <vector>

#include "Sheep.h"
#include "kdtree.hpp"

class SheepTree : public Sheep {

public:

    SheepTree( const size_t gridsize, const size_t capacity, gsl_rng* const rng );

    size_t getNSheep( size_t i, size_t j ) const;
    void setNSheep( size_t i, size_t j, size_t nSheep );
    void getRandomSheep( size_t& i, size_t& j ) const;

    bool first( size_t& i, size_t& j, size_t& n ) const;
    bool next( size_t& i, size_t& j, size_t& n ) const;

    class Point
    {
    public:
        typedef size_t value_type;

        Point( size_t i, size_t j, size_t n = 1 )
        {
            d[0] = i;
            d[1] = j;

            counter = new size_t;
            *counter = n;
        }

        Point( const Point& r )
        {
            d[0] = r.d[0];
            d[1] = r.d[1];

            counter = new size_t;
            *counter = *r.counter;
        }

        ~Point()
        {
            delete counter;
        }

        Point& operator=( const Point& r )
        {
            d[0] = r.d[0];
            d[1] = r.d[1];

            *counter = *r.counter;

            return *this;
        }

        bool operator==( const Point& r ) const
        {
            return d[0] == r.d[0] && d[1] == r.d[1];
        }

        size_t operator[]( size_t const N ) const
        {
            return d[N];
        }

        size_t d[2];

        size_t* counter;
    };

private:

    size_t getIndex( size_t i, size_t j ) const;

    typedef KDTree::KDTree< 2, SheepTree::Point > Tree;
    Tree tree;

};

#endif // _SHEEPTREE_H
