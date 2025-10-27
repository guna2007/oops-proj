#include "task_executor.h"
#include <iostream>
#include <iomanip>

using namespace std;

// OOP Concept: Composition - TaskExecutor coordinates execution of Task objects

TaskExecutor::TaskExecutor(ostream &out)
    : output(out), total_execution_time(0)
{
}

// OOP Concept: Abstraction - Complex execution logic abstracted into single method
void TaskExecutor::runTasks(const vector<Task *> &ordered_tasks, const string &scheduler_name)
{
    output << "========================================" << endl;
    output << "STARTING TASK EXECUTION" << endl;
    output << "========================================" << endl;
    if (!scheduler_name.empty())
    {
        output << "[Scheduler Used: " << scheduler_name << "]" << endl;
        output << "----------------------------------------" << endl;
    }

    int executed_count = 0;
    int not_ready_count = 0;
    const int MAX_PASSES = 10; // Prevent infinite loops

    // Create a working list of tasks to execute
    vector<Task *> remaining_tasks = ordered_tasks;

    for (int pass = 0; pass < MAX_PASSES && !remaining_tasks.empty(); ++pass)
    {
        vector<Task *> deferred_tasks;
        bool progress_made = false;

        for (Task *task : remaining_tasks)
        {
            // Skip already completed tasks
            if (task->getStatus() == COMPLETED)
            {
                continue;
            }

            // Check if task is ready (all dependencies completed)
            if (!task->isReady())
            {
                deferred_tasks.push_back(task);
                continue;
            }

            // Execute the task
            executeTaskWithSubtasks(task, 0);
            executed_count++;
            progress_made = true;
        }

        // Update remaining tasks
        remaining_tasks = deferred_tasks;

        // If no progress was made, we're stuck
        if (!progress_made && !remaining_tasks.empty())
        {
            output << "----------------------------------------" << endl;
            output << "WARNING: Cannot make further progress!" << endl;
            output << "The following tasks are NOT READY:" << endl;
            for (Task *task : remaining_tasks)
            {
                output << "  Task " << task->getId() << ": " << task->getName()
                       << " (waiting on dependencies)" << endl;
                not_ready_count++;
            }
            break;
        }
    }

    output << "========================================" << endl;
    if (not_ready_count == 0)
    {
        output << "ALL TASKS COMPLETED SUCCESSFULLY" << endl;
    }
    else
    {
        output << "EXECUTION COMPLETED WITH " << not_ready_count << " TASK(S) NOT READY" << endl;
    }
    output << "========================================" << endl;
}

// OOP Concept: Recursion - Executes task and all its subtasks recursively
void TaskExecutor::executeTaskWithSubtasks(Task *task, int indent)
{
    if (task == nullptr || task->getStatus() == COMPLETED)
    {
        return;
    }

    // Print RUNNING status
    printTaskExecution(task, indent, "RUNNING");

    // Execute subtasks first (depth-first execution)
    for (Task *subtask : task->getSubtasks())
    {
        if (subtask->getStatus() != COMPLETED && subtask->isReady())
        {
            executeTaskWithSubtasks(subtask, indent + 1);
        }
    }

    // Execute the task itself
    task->execute();
    total_execution_time += task->getEstimatedTime();

    // Print COMPLETED status
    printTaskExecution(task, indent, "COMPLETED");
}

void TaskExecutor::printTaskExecution(Task *task, int indent, const string &action)
{
    string indentation(indent * 2, ' ');
    output << indentation << action << ": Task " << task->getId()
           << " : " << task->getName()
           << " (priority=" << task->getPriority()
           << ", deadline=" << task->getDeadline() << ")" << endl;
    output.flush(); // Force output immediately
}

int TaskExecutor::getTotalExecutionTime() const
{
    return total_execution_time;
}

void TaskExecutor::resetExecutionTime()
{
    total_execution_time = 0;
}
