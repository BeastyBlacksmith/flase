
#ifndef _HARRYPLOTTER_H
#define _HARRYPLOTTER_H

#include "common.h"
#include "World.h"

class HarryPlotter
{
public:

    virtual void plot( World& world, real time ) = 0;

};

#endif // _HARRYPLOTTER_H
