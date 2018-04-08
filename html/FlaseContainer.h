//
// Created by christ on 08.04.18.
//

#ifndef SHEEPNDOGS_FLASECONTAINER_H
#define SHEEPNDOGS_FLASECONTAINER_H

#include <Wt/WContainerWidget>
#include <Wt/WPaintedWidget>
#include <Motion/BrownianMotion.h>
#include "Flase.h"

class FlaseContainer : public Wt::WContainerWidget
{
public:
    FlaseContainer();

private:
    Wt::WPaintedWidget* frame;
    
};


#endif //SHEEPNDOGS_FLASECONTAINER_H
