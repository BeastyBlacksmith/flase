
#ifndef _GNUPLOTTER_H
#define _GNUPLOTTER_H

#include <string>
#include <iostream>
#include <fstream>

#include "common.h"
#include "HarryPlotter.h"

class GNUPlotter : public HarryPlotter
{
public:

    GNUPlotter(
            size_t skip = 1,
            real vecsize = 1.,
            std::string sheepdat = "sheeppl.dat",
            std::string oscillator = "oscillator.dat",
            std::string gnuplotscript = "havefun.gp" );

    virtual void plot( World& world, real time );

protected:

    size_t skip;
    size_t counter;
    real vecsize;
    std::string sheepdat;
    std::string oscillator; 

    std::ofstream outMaeh;
    std::ofstream outWuff;
    std::ofstream outGnuPlot;
};

#endif // _GNUPLOTTER_H
