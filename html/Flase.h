//
// Created by christ on 08.04.18.
//

#ifndef SHEEPNDOGS_FLASEAPP_H
#define SHEEPNDOGS_FLASEAPP_H

#include <Wt/WPaintedWidget.h>
#include <Wt/WPaintDevice.h>
#include <Wt/Wpainter.h>
#include <Dogs.h>
#include <Motion/ConstVelocity.h>

class Flase : public Wt::WPaintedWidget
{
public:
    Flase( gsl_rng* const rng, const size_t size = 500 );
    
    ~Flase();
    
    void startSimulation( double dt );
    
    void changeMovement( int id );

protected:
    void paintEvent( Wt::WPaintDevice* paintDevice ) override;

private:
    std::size_t size;
    Motion* motion;
    gsl_rng* const rng;
    BrownianMotion* bm;
    ConstVelocity* cv;
    double meanSheepDiffusionTime{ 1000 };
    double tsheepboredom;
    double time{ 0 };
    double noise{ 4.0 };
    double friction{ 1.0 };
    double velocity{ 5.0 };
    
};


#endif //SHEEPNDOGS_FLASEAPP_H
