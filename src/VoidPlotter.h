
#ifndef _VOIDPLOTTER_H
#define _VOIDPLOTTER_H

#include "HarryPlotter.h"

class VoidPlotter : public HarryPlotter
{
public:

    void plot( World& world, real time );
};

#endif // _VOIDPLOTTER_H
