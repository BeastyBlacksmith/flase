
#ifndef _GLPLOTTER_H
#define _GLPLOTTER_H

#include <string>
#include <iostream>
#include <fstream>

#include <pthread.h>

#include "HarryPlotter.h"

class GLPlotter : public HarryPlotter
{
public:

    GLPlotter();
    ~GLPlotter();

    virtual void plot( World& world, real time );

protected:

    pthread_t thread;
};

#endif // _GLPLOTTER_H
