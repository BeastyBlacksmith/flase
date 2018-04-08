//
// Created by christ on 08.04.18.
//

#ifndef SHEEPNDOGS_FLASEAPP_H
#define SHEEPNDOGS_FLASEAPP_H

#include <Wt/WContainerWidget.h>

class FlaseApp : public Wt::WPaintedWidget
{
public:
    FlaseApp( const size_t size );

protected:
    void paintEvent( Wt::WPaintDevice* paintDevice );

private:
    std::size_t size;
};


#endif //SHEEPNDOGS_FLASEAPP_H
