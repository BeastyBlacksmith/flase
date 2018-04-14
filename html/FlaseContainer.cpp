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
    
    // connect random number generator
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
    World &world = World::instance();
    { // Controls
        controls = controlBox->addWidget( make_unique<WGroupBox>( "Controls" ) );
        auto setDt = new ParameterField( "Timestep", dt, *controls, true );
        setDt->connect();
        auto setSteps = new ParameterField( "Steps per frame", steps, *controls );
        setSteps->connect();
        auto setNDogs = controls->addWidget( make_unique<WLineEdit>() );
        setNDogs->setInline( false );
        setNDogs->setWidth( WLength( dogText().size(), LengthUnit::FontEx ) );
        setNDogs->setPlaceholderText( dogText() );
        // TODO: reinitilization of dogs doesn't work
//        setNDogs->enterPressed().connect( [&] { world.dogs.init( stoi( setNDogs->text() ), world.dogs.getV0() ); app
//                .processEvents(); } );
        setNDogs->enterPressed().connect( [&] {
            setNDogs->setText( "" );
            setNDogs->setPlaceholderText( dogText() );
        } );
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
                    for( int i = 0; i < steps; ++i )
                    {
                        frame->startSimulation( dt );
                    
                    }
                    app.processEvents();
                }
            } );
        }
    }
}