#ifndef TASKMANAGER_H_INCLUDED
#define TASKMANAGER_H_INCLUDED

#include <memory>
#include <list>
#include "TaskInterface.h"

typedef std::shared_ptr<ITask> taskPtr;


class ITaskManager : public ITask
{
	public:
		ITaskManager(unsigned int priority = 10000) : ITask(priority) {};
		~ITaskManager() {};

		bool addTask(taskPtr& task);
		void updateTaskList();
		void suspendTask(taskPtr& task);
		void resumeTask(taskPtr& task);
		void removeTask(taskPtr& task);
		void killAllTasks();

	protected:
		std::list<taskPtr> m_taskList;
		std::list<taskPtr> m_pausedTaskList;
};

#endif // TASKMANAGER_H_INCLUDED
