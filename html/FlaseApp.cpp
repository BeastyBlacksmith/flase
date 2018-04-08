#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Motion/BrownianMotion.h>
#include "Flase.h"

class FlaseApp : public Wt::WApplication
{
public:
    FlaseApp( const Wt::WEnvironment &env ) :
            WApplication( env )
    {
        setTitle( "flase: diffusive item-collector simulation" );
        
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
        gsl_rng_set( rng, seed );
        
        Dogs dogs = Dogs( *( new BrownianMotion( 4.0, rng, 1.0 ) ) );
        
        root()->addWidget( std::make_unique<Flase>( dogs ) );
    }
};


int main( int argc, char** argv )
{
    
    return Wt::WRun( argc, argv, []( const Wt::WEnvironment &env ) { return std::make_unique<FlaseApp>( env ); } );
}