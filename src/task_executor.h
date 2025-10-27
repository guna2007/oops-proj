#ifndef TASK_EXECUTOR_H
#define TASK_EXECUTOR_H

#include <vector>
#include <ostream>
#include <iostream>
#include "task.h"

using namespace std;

// OOP Concept: Composition - TaskExecutor uses Task objects to perform operations
// OOP Concept: Abstraction - Execution details hidden from caller

class TaskExecutor
{
private:
    ostream &output; // OOP Concept: Composition - Contains reference to output stream
    int total_execution_time;

    // Helper methods
    void executeTaskWithSubtasks(Task *task, int indent = 0);
    void printTaskExecution(Task *task, int indent, const string &action);
    void showProgressAnimation(Task *task, int indent);

public:
    // Constructor takes output stream (default is cout)
    explicit TaskExecutor(ostream &out = cout);

    // OOP Concept: Abstraction - High-level execution interface
    void runTasks(const vector<Task *> &ordered_tasks, const string &scheduler_name = "");

    // Get total simulated execution time
    int getTotalExecutionTime() const;

    // Reset execution time counter
    void resetExecutionTime();
};

#endif // TASK_EXECUTOR_H
