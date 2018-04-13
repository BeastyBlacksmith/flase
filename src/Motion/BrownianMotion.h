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

#ifndef _BROWNIANMOTION_H
#define _BROWNIANMOTION_H

#include "Motion.h"

class BrownianMotion : public Motion
{
public:
    
    BrownianMotion();
    BrownianMotion( real noise, gsl_rng* const rng, real friction ) ;
    
    void step( real& x, real& y, real& vx, real& vy, real dt ) const;

protected:
    
    real friction;
};

#endif // _BROWNIANMOTION_H
