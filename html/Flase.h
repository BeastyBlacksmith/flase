//
// Created by christ on 08.04.18.
//

#ifndef SHEEPNDOGS_FLASEAPP_H
#define SHEEPNDOGS_FLASEAPP_H

#include <Wt/WPaintedWidget.h>
#include <Wt/WPaintDevice.h>
#include <Wt/Wpainter.h>
#include <Dogs.h>

class Flase : public Wt::WPaintedWidget
{
public:
    Flase( gsl_rng* const rng, const size_t size = 500 );
    
    ~Flase();

protected:
    void paintEvent( Wt::WPaintDevice* paintDevice ) override;

private:
    std::size_t size;
    double meanSheepDiffusionTime{ 1000 };
    double tsheepboredom;
    double time{ 0 };
    double dt{ 0.1 };
    
    void nextFrame( double dt );
};


#endif //SHEEPNDOGS_FLASEAPP_H
