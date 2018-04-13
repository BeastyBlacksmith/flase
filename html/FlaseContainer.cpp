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
    
    { // Set boxes box
        vbox = this->setLayout( make_unique<WVBoxLayout>() );
    }
    { // Header Text
        header = make_unique<WText>( "<h1>Flase: Diffusive collector-item simulation</h1>" );
        header->setTextAlignment( AlignmentFlag::Center );
        vbox->addWidget( move( header ) );
    }
    { // Simulation frame
        controlBox = vbox->addLayout( make_unique<WHBoxLayout>() );
        frame = controlBox->addWidget( make_unique<Flase>( rng ) );
    }
    { // Controls
        controls = make_unique<WGroupBox>( "Controls" );
        controlBox->addWidget( move( controls ) );
    }
    { // Buttons
        southContainer = vbox->addWidget( make_unique<WContainerWidget>() );
        southBox = southContainer->setLayout( make_unique<WHBoxLayout>() );
        start = southBox->addWidget( make_unique<WPushButton>( "Start" ) );
        stop = southBox->addWidget( make_unique<WPushButton>( "Stop!" ) );
        stop->clicked().connect( start, &WPushButton::enable );
        stop->clicked().connect( stop, [this] { isRunning = false; } );
        start->clicked().connect( start, &WPushButton::disable );
        start->clicked().connect( start, [&] {
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