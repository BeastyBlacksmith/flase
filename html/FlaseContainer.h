//
// Created by christ on 08.04.18.
//

#ifndef SHEEPNDOGS_FLASECONTAINER_H
#define SHEEPNDOGS_FLASECONTAINER_H

#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPaintedWidget.h>
#include <Motion/BrownianMotion.h>
#include "Flase.h"

class FlaseContainer : public Wt::WContainerWidget
{
public:
    FlaseContainer();

private:
    Flase* frame;
    Wt::WPushButton* start;
};


#endif //SHEEPNDOGS_FLASECONTAINER_H
