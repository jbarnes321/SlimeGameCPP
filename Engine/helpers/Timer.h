#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <memory>

namespace sf
{
	class Clock;
}

typedef std::shared_ptr<sf::Clock> ClockPtr;


class Timer
{
    public:
        Timer();
        ~Timer() {};
        void start();
        void reset();
        void pause();
        void resume();
        void stop();
        bool isStarted();
        bool isPaused();
        unsigned int getTicks();

    private:
        ClockPtr m_clock;
        unsigned int m_startTicks;
        unsigned int m_pausedTicks;
        bool m_paused;
        bool m_started;
};

#endif // TIMER_H_INCLUDED
