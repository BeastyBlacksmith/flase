//
// Created by christ on 08.04.18.
//

#include <Motion/BrownianMotion.h>
#include "Flase.h"

using namespace std;
using namespace Wt;

Flase::Flase( Dogs* ddogs, gsl_rng* const rng, const size_t size ) :
        WPaintedWidget(),
        size( size ),
        dogs( ddogs )
{
    resize( size, size );
    dogs->init( 50, 1., size, rng );
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
    for( int i = 0; i < dogs->size(); ++i )
    {
        painter.drawRect( dogs[0][i].x, dogs[0][i].y, 5, 5 );
    }
    
}

void Flase::nextFrame( double dt )
{

}

