#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Motion/BrownianMotion.h>
#include "FlaseContainer.h"

class FlaseApp : public Wt::WApplication
{
public:
    FlaseApp( const Wt::WEnvironment &env ) :
            WApplication( env )
    {
        setTitle( "flase: diffusive item-collector simulation" );
    
        root()->addWidget( std::make_unique<FlaseContainer>( *this ) );
        
    }
};


int main( int argc, char** argv )
{
    
    return Wt::WRun( argc, argv, []( const Wt::WEnvironment &env ) { return std::make_unique<FlaseApp>( env ); } );
}