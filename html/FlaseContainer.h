//
// Created by christ on 08.04.18.
//

#ifndef SHEEPNDOGS_FLASECONTAINER_H
#define SHEEPNDOGS_FLASECONTAINER_H

#include <Wt/WApplication.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPaintedWidget.h>
#include <Motion/BrownianMotion.h>
#include "Flase.h"

class FlaseContainer : public Wt::WContainerWidget
{
public:
    FlaseContainer( Wt::WApplication &app );

private:
    Wt::WText* header;
    Wt::WApplication &app;
    Flase* frame;
    Wt::WPushButton* start;
    Wt::WPushButton* stop;
    bool isRunning{ true };
};


#endif //SHEEPNDOGS_FLASECONTAINER_H
