#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "FlaseApp.h"


int main( int argc, char** argv )
{
    
    return Wt::WRun( argc, argv, []( const Wt::WEnvironment &env ) { return std::make_unique<FlaseApp>( env ); } );
}