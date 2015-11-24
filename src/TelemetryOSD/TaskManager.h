#pragma once
#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "PeriodicTask.h"
#include "TelemetryRequestFncs.h"

#define N_MAX_TASKS	10

class TaskManager
{
public:
	TaskManager();
	~TaskManager();

	void runTasks();
private:
	PeriodicTask **tasks_;
	uint8_t nTasks_;

	void addTask(PeriodicTask *task);
};



#endif
