#ifndef GameClock_h
#define GameClock_h

#include "includes/sdl.hpp"

class GameClock {
public:
    GameClock();

    void tick();
    void resetAverage();

    float getCurrentTime();
    float getDeltaTime();
    float getAverageDeltaTime();


private:

    float current_time;
    float last_time;
    float delta_time;

    int tick_count;
    float average_delta_time;

};

#endif
