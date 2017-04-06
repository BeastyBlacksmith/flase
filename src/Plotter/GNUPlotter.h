
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
            Measure& measure,
            size_t skip = 1,
            real vecsize = 1.,
            std::string sheepdat = "temp/sheepPosition.dat",
            std::string dogsdat = "temp/dogsPosition.dat",
            std::string gnuplotscript = "havefun.gp" );
    ~GNUPlotter();

    virtual void plot( World& world, real time );

protected:

    Measure& measure;
    size_t skip;
    size_t counter;
    real vecsize;
    std::string sheepdat;
    std::string dogsdat;

    std::ofstream outMaeh;
    std::ofstream outWuff;
    std::ofstream outGnuPlot;
};

#endif // _GNUPLOTTER_H
