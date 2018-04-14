//
// Created by christ on 08.04.18.
//

#ifndef SHEEPNDOGS_FLASECONTAINER_H
#define SHEEPNDOGS_FLASECONTAINER_H

#include <Wt/WApplication.h>
#include <Wt/WGroupBox.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPaintedWidget.h>
#include <Motion/BrownianMotion.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTemplate.h>
#include "Flase.h"
#include "util/ParameterField.h"

class FlaseContainer : public Wt::WContainerWidget
{
public:
    FlaseContainer( Wt::WApplication &app );

private:
    Wt::WVBoxLayout* vbox;
    Wt::WContainerWidget* southContainer;
    Wt::WHBoxLayout* controlBox;
    Wt::WHBoxLayout* southBox;
    std::unique_ptr<Wt::WText> header;
    Wt::WApplication &app;
    Flase* frame;
    Wt::WPushButton* start;
    Wt::WPushButton* stop;
    Wt::WGroupBox* controls;
    
    Wt::WRadioButton* motionButton;
    std::shared_ptr<Wt::WButtonGroup> motionButtons;
    
    bool isRunning{ true };
    double dt{ 0.002 };
    double steps{ 100 };
};


#endif //SHEEPNDOGS_FLASECONTAINER_H
