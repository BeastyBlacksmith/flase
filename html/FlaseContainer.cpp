//
// Created by christ on 08.04.18.
//

#include "FlaseContainer.h"
#include <chrono>
#include <thread>

using namespace Wt;
using namespace std;

FlaseContainer::FlaseContainer( WApplication &app ) :
        app( app )
{
    setContentAlignment( AlignmentFlag::Center );
    
    // init random number generator
    const gsl_rng_type* T;
    gsl_rng* rng;
    long int seed;
    
    gsl_rng_env_setup();
    T = gsl_rng_default;
    rng = gsl_rng_alloc( T );
    time_t t1;
    time( &t1 );
    seed = t1;
//    seed = 1523557004;
    gsl_rng_set( rng, seed );
    
    { // Text
        header = this->addWidget( make_unique<WText>( "<h1>Flase: Diffusive collector-item simulation</h1>" ) );
    }
    { // Simulation frame
        frame = addWidget( make_unique<Flase>( rng ) );
    }
    { // Buttons
        start = this->addWidget( make_unique<WPushButton>( "Start" ) );
        stop = this->addWidget( make_unique<WPushButton>( "Stop!" ) );
        stop->clicked().connect( start, &WPushButton::enable );
        stop->clicked().connect( stop, [this] { isRunning = false; } );
        start->clicked().connect( start, &WPushButton::disable );
        start->clicked().connect( start, [this, &app] {
            isRunning = true;
            while( isRunning )
            {
                for( int i = 0; i < 100; ++i )
                {
                    frame->startSimulation( 0.1 );
                    
                }
                app.processEvents();
            }
        } );
    }
}