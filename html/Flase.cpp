//
// Created by christ on 08.04.18.
//

#include <Motion/BrownianMotion.h>
#include "Flase.h"

using namespace std;
using namespace Wt;

Flase::Flase( Dogs &dogs, const size_t size ) :
        WPaintedWidget(),
        size( size ),
        dogs( dogs )
{
    resize( size, size );
    
}

Flase::~Flase()
{
}

void Flase::paintEvent( Wt::WPaintDevice* paintDevice )
{
    WPainter painter( paintDevice );
    painter.setBrush( WBrush( WColor( StandardColor::DarkBlue ) ) );
    painter.drawRect( 0, 0, size, size );
}

void Flase::nextFrame( double dt )
{

}

