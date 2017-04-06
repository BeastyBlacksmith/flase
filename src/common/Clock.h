
#ifndef _CLOCK_H
#define _CLOCK_H

class Clock
{
public:
    Clock();

    double precision;

    double last_time;
    double act_time;

    double getTime();
    double getFrameTime() const { return act_time - last_time; }
    double tick();
};

#endif // _CLOCK_H

