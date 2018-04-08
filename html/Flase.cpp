//
// Created by christ on 08.04.18.
//

#include <Motion/BrownianMotion.h>
#include "Flase.h"

using namespace std;
using namespace Wt;

Flase::Flase( Dogs &dogs, gsl_rng* const rng, const size_t size ) :
        WPaintedWidget(),
        size( size ),
        dogs( dogs )
{
    resize( size, size );
    dogs.init( 2, 1., size, rng );
}

Flase::~Flase()
{
}

void Flase::paintEvent( Wt::WPaintDevice* paintDevice )
{
    WPainter painter( paintDevice );
    painter.setBrush( WBrush( WColor( StandardColor::LightGray ) ) );
    painter.drawRect( 0, 0, size, size );
    painter.setBrush( WBrush( WColor( StandardColor::DarkMagenta ) ) );
    painter.drawRect( 1, 50, 5, 5 );
    painter.drawRect( 50, 1, 5, 5 );
    // TODO: debug the dog painting loop
//    for( int i = 0; i < dogs.size(); ++i )
//    {
//        painter.drawRect( dogs[i].x, dogs[i].y, 5, 5 );
//    }
    
}

void Flase::nextFrame( double dt )
{

}

