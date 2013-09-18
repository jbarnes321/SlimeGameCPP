#ifndef GAMEBASE_H_INCLUDED
#define GAMEBASE_H_INCLUDED

#include "helpers/Event.h"
#include "helpers/Timer.h"
#include "input/Input.h"
#include "video/Video.h"
#include "debug/DebugLog.h"


class GameBase
{
	public:
		GameBase();
		~GameBase() {};
		void start();
		void stop();
		unsigned int getTimeRunning();
		unsigned int getFps();

	protected:
		InputPtr m_input;
		VideoPtr m_video;
		DebugPtr m_debug;

	private:
		void delayMs(const unsigned int delayMs);
		void loop();
		void systemInit();
		void systemEnd();
		virtual void init() {};
		virtual void onTick() = 0;
		virtual void onRender() = 0;
		virtual void onEvent(const int eventType, const int param1, const int param2) = 0;
		virtual void end() {};

		EventListener3<GameBase, void, int, int, int> m_eventListener;
		bool m_run;
		unsigned int m_fpsCounter;
		unsigned int m_msFrameDuration;
		Timer m_fpsTimer;
		Timer m_updateTimer;
		Timer m_runningTimer;
		unsigned int m_fps;
};


#endif // GAMEBASE_H_INCLUDED
