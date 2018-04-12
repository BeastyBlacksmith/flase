
/*
Copyright (C) 2017  Simon Christ <c.O_o.l@web.de>, Jörg Bachmann <explicit@explicits.de>

This program is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _MOTION_H
#define _MOTION_H

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "common.h"

class Motion {
public:

    Motion( real noise, gsl_rng* const rng ) :
        noise( noise ),
        rng( rng ),
        persistenceLength( -1 ),
        persistenceTime( -1 ),
        effectiveDiffusion( -1 )
    {
    }

    virtual ~Motion() {}

    virtual void step( real& x, real& y, real& vx, real& vy, real dt ) const = 0;

    real getPersistenceLength() const { return persistenceLength; }
    real getPersistenceTime() const { return persistenceTime; }
    real getEffectiveDiffusion() const { return effectiveDiffusion; }

protected:

    real noise;
    gsl_rng* rng;
    real persistenceLength;
    real persistenceTime;
    real effectiveDiffusion;

};

#endif // _MOTION_H
