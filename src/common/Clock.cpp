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
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "Clock.h"

Clock::Clock()
{
#ifdef _POSIX_TIMERS

# ifdef CLOCK_REALTIME
	
	timespec ts;
	
	if ( 0 != clock_getres ( CLOCK_REALTIME, &ts))
	{
		std::cerr << "Could not initialize realtime clock!" << std::endl;
		exit ( -1);
	}
	
	precision = (double)ts.tv_sec + 0.000000001 * (double)ts.tv_nsec;

# else // CLOCK_REALTIME
	
	precision = 1 / (double)CLOCKS_PER_SEC;

# endif // CLOCK_REALTIME
#else
	std::cout << "WARNING: no POSIX TIMER found" << std::endl;
#endif // _POSIX_TIMERS
	
	
	getTime ();
	last_time = act_time;
}

double Clock::getTime()
{
#ifdef _POSIX_TIMERS
# ifdef CLOCK_REALTIME
	
	timespec ts;
	clock_gettime (CLOCK_REALTIME, &ts);
	act_time = (double)ts.tv_sec + 0.000000001 * (double)ts.tv_nsec;

# else // CLOCK_REALTIME
	
	act_time = (double)clock () * precision;

# endif // CLOCK_REALTIME
#endif // _POSIX_TIMERS
	
	return act_time;
}

double Clock::tick()
{
	last_time = act_time;
	return getTime () - last_time;
}

