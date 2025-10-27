#ifndef TASK_EXECUTOR_H
#define TASK_EXECUTOR_H

#include <vector>
#include <ostream>
#include <iostream>
#include "task.h"

// OOP Concept: Composition - TaskExecutor uses Task objects to perform operations
// OOP Concept: Abstraction - Execution details hidden from caller

class TaskExecutor
{
private:
    std::ostream &output; // OOP Concept: Composition - Contains reference to output stream
    int total_execution_time;

    // Helper methods
    void executeTaskWithSubtasks(Task *task, int indent = 0);
    void printTaskExecution(Task *task, int indent, const std::string &action);

public:
    // Constructor takes output stream (default is std::cout)
    explicit TaskExecutor(std::ostream &out = std::cout);

    // OOP Concept: Abstraction - High-level execution interface
    void runTasks(const std::vector<Task *> &ordered_tasks);

    // Get total simulated execution time
    int getTotalExecutionTime() const;

    // Reset execution time counter
    void resetExecutionTime();
};

#endif // TASK_EXECUTOR_H
