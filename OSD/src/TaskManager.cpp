#include "TaskManager.h"


TaskManager::TaskManager()
	: nTasks_(0)
{
	// Allocate memory for tasks
	this->tasks_ = (PeriodicTask **)malloc(N_MAX_TASKS * sizeof(PeriodicTask*));

	// Add tasks
	this->addTask(new PeriodicTask(TASK_PERIOD_STATUS, &TelemetryRequestFncs::requestStatus));
	this->addTask(new PeriodicTask(TASK_PERIOD_POSE,   &TelemetryRequestFncs::requestPose));
	this->addTask(new PeriodicTask(TASK_PERIOD_GPS,	   &TelemetryRequestFncs::requestGPS));
}


TaskManager::~TaskManager()
{
	// Remove tasks
	for (uint8_t i = 0; i < N_MAX_TASKS; ++i)
	{
		free(this->tasks_[i]);
	}

	// Remove vector
	free(this->tasks_);
}

void TaskManager::runTasks()
{
	for (uint8_t i = 0; i < this->nTasks_; ++i)
	{
		this->tasks_[i]->run();
	}
}

void TaskManager::addTask(PeriodicTask *task)
{
	if (this->nTasks_ < N_MAX_TASKS - 1)
	{
		this->tasks_[this->nTasks_++] = task;
	}
}