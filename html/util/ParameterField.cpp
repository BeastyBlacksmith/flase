//
// Created by christ on 14.04.18.
//

#include "ParameterField.h"

using namespace std;
using namespace Wt;

ParameterField::ParameterField( const string &name, double &parameter, WContainerWidget &container, bool isInline ) :
        name( name ),
        parameter( &parameter )
{
    widget = container.addWidget( make_unique<WLineEdit>() );
    widget->setInline( isInline );
    auto pText = name + ": " + to_string( parameter );
    widget->setWidth( WLength( pText.size(), LengthUnit::FontEx ) );
    widget->setPlaceholderText( pText );
}

void ParameterField::connect()
{
    widget->enterPressed().connect( [&] { *parameter = stod( widget->text() ); } );
    widget->enterPressed().connect( [&] {
                                        widget->setText( "" );
                                        widget->setPlaceholderText( name + ": " + to_string( *parameter ) );
                                    }
    );
}
