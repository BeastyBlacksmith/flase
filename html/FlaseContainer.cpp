//
// Created by christ on 08.04.18.
//

#include "FlaseContainer.h"
#include <chrono>
#include <thread>
#include <World.h>

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
        controls = controlBox->addWidget( make_unique<WGroupBox>( "Controls" ) );
        setDt = controls->addWidget( make_unique<WLineEdit>() );
        setDt->setInline( false );
        setDt->setWidth( WLength( 10, LengthUnit::FontEm ) );
        setDt->setPlaceholderText( "Timestep: " + to_string( dt ) );
        setDt->enterPressed().connect( [this] { dt = stod( setDt->text() ); } );
        setDt->enterPressed().connect( [this] {
                                           setDt->setText( "" );
                                           setDt->setPlaceholderText( "Timestep: " + to_string( dt ) );
                                       }
        );
    }
    { // Buttons
        { // Motion Buttons
            motionButtons = make_shared<WButtonGroup>();
            motionButton = controls->addWidget( make_unique<WRadioButton>( "Brownian motion" ) );
            motionButtons->addButton( motionButton );
            motionButton = controls->addWidget( make_unique<WRadioButton>( "Random motion with constant velocity" ) );
            motionButtons->addButton( motionButton );
            motionButtons->setSelectedButtonIndex( 0 );
        
            auto rawMotionButtons = motionButtons.get();
            motionButtons->checkedChanged().connect( [this, rawMotionButtons, &app]( WRadioButton* selection ) {
                                                         isRunning = false;
                                                         frame->changeMovement( rawMotionButtons->id( selection ) );
                                                         app.log( "test" ) << "Address: " <<
                                                                           World::instance().dogs.motion;
                                                         app.log( "test" ) << "Eff. Diffusion: " <<
                                                                           World::instance().dogs.motion
                                                                                   ->getEffectiveDiffusion();
                                                         app.log( "test" ) << "Persistence length: " <<
                                                                           World::instance().dogs.motion
                                                                                   ->getPersistenceLength();
                                                         app.log( "test" ) << "Persistence length: " <<
                                                                           World::instance().dogs.motion
                                                                                   ->getPersistenceTime();
                                                     }
            );
        }
        { // Start / Stop
            southContainer = vbox->addWidget( make_unique<WContainerWidget>() );
            southBox = southContainer->setLayout( make_unique<WHBoxLayout>() );
            start = southBox->addWidget( make_unique<WPushButton>( "Start" ) );
            stop = southBox->addWidget( make_unique<WPushButton>( "Stop!" ) );
            stop->clicked().connect( start, &WPushButton::enable );
            motionButtons->checkedChanged().connect( start, &WPushButton::enable );
            stop->clicked().connect( stop, [this] { isRunning = false; } );
            start->clicked().connect( start, &WPushButton::disable );
            start->clicked().connect( start, [&] {
                isRunning = true;
                while( isRunning )
                {
                    for( int i = 0; i < 100; ++i )
                    {
                        frame->startSimulation( dt );
                    
                    }
                    app.processEvents();
                }
            } );
        }
    }
}