#ifndef TASKINTERFACE_H_INCLUDED
#define TASKINTERFACE_H_INCLUDED

class ITask
{
	public:
		ITask(unsigned int priority = 10000) : m_isFinished(false), m_priority(priority) {};
		~ITask() {};

		virtual bool start() = 0;
		virtual void update() = 0;
		virtual void stop() = 0;
		virtual void onSuspend() {};
		virtual void onResume() {};

		bool m_isFinished;
		unsigned int m_priority;
};

#endif // TASKINTERFACE_H_INCLUDED
