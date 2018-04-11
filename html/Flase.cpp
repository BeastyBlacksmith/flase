//
// Created by christ on 08.04.18.
//

#include <Motion/BrownianMotion.h>
#include <World.h>
#include <Sheep/SheepField.h>
#include "Flase.h"

using namespace std;
using namespace Wt;

Flase::Flase( gsl_rng* const rng, const size_t size ) :
        WPaintedWidget(),
        size( size )
{
    resize( size, size );
    
    BrownianMotion motion( 4.0, rng, 1.0 );
    Dogs* dogs = new Dogs( motion );
    Sheep* sheep = new SheepField( size / 2.5, 1, rng );
    
    dogs->init( 50, 1., size, rng );
    sheep->init( 20 );
    World::createInstance( size, rng, 10, 20, 20, *sheep, *dogs );
    tsheepboredom = gsl_ran_exponential( rng, meanSheepDiffusionTime / World::instance().sheep.getCurrentSheep() );
}

Flase::~Flase()
{
}

void Flase::paintEvent( Wt::WPaintDevice* paintDevice )
{
    WPainter painter( paintDevice );
    { // draw simulation area
        painter.setBrush( WBrush( WColor( StandardColor::LightGray ) ) );
        painter.drawRect( 0, 0, size, size );
    }
    { // draw dogs
        auto dogs = World::instance().dogs;
        painter.setBrush( WBrush( WColor( StandardColor::DarkMagenta ) ) );
        for( int i = 0; i < dogs.size(); ++i )
        {
            painter.drawRect( dogs[i].x, dogs[i].y, 5, 5 );
        }
    }
    { // draw sheep
        double scale = World::instance().boxsize / World::instance().sheep.size();
        painter.setBrush( WBrush( WColor( StandardColor::Black ) ) );
        size_t i, j, n;
        
        if( World::instance().sheep.first( i, j, n ) )
        {
            painter.drawRect( i * scale, j * scale, 2.5, 2.5 );
            
            while( World::instance().sheep.next( i, j, n ) )
            {
                painter.drawRect( i * scale, j * scale, 2.5, 2.5 );
            }
        }
    }
//   TODO: how to iterate? nextFrame( dt );
}

void Flase::nextFrame( double dt )
{
    World &world = World::instance();
    
    // move dogs
    {
        world.moveDogs( dt );
    }
    
    // move sheep
    {
        // move random sheep
        if( time >= tsheepboredom )
        {
            size_t i = 0;
            size_t j = 0;
            world.sheep.getRandomSheep( i, j );
            world.sheep.diffuseSheep( i, j );
            
            tsheepboredom = time + gsl_ran_exponential( world.rng, meanSheepDiffusionTime / world.sheep
                    .getCurrentSheep() );
        }
        
        // get into a consistent state, i.e. fight!
        // nicht draengeln!
        world.sheep.kickSheep();
    }
    
    // doggy, wakeup!
    {
        world.dogs.work( dt );
    }
    time += dt;
}

