#include "task_executor.h"
#include "config.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

// Constructor
TaskExecutor::TaskExecutor(ostream &out)
    : output(out), total_execution_time(0)
{
}

// Main execution method - Run all tasks in order
void TaskExecutor::runTasks(const vector<Task *> &ordered_tasks, const string &scheduler_name)
{
    // Print header
    output << "\n" << COLOR_MAGENTA;
    output << "+============================================+" << endl;
    output << "|        TASK EXECUTION IN PROGRESS         |" << endl;
    output << "+============================================+" << COLOR_RESET << endl;
    
    if (!scheduler_name.empty())
    {
        output << "  Scheduler: " << COLOR_YELLOW << scheduler_name << COLOR_RESET << endl;
        output << "  " << string(44, '-') << endl << endl;
    }

    int executed_count = 0;
    int not_ready_count = 0;
    const int MAX_PASSES = 10;  // Prevent infinite loops
    vector<Task *> remaining_tasks = ordered_tasks;

    // Execute tasks in multiple passes to handle dependencies
    for (int pass = 0; pass < MAX_PASSES && !remaining_tasks.empty(); ++pass)
    {
        vector<Task *> deferred_tasks;
        bool progress_made = false;

        for (Task *task : remaining_tasks)
        {
            // Skip completed tasks
            if (task->getStatus() == COMPLETED)
                continue;

            // Defer tasks with unmet dependencies
            if (!task->isReady())
            {
                deferred_tasks.push_back(task);
                continue;
            }

            // Execute ready task
            executeTaskWithSubtasks(task, 0);
            executed_count++;
            progress_made = true;
        }

        remaining_tasks = deferred_tasks;

        // Check for deadlock (no progress possible)
        if (!progress_made && !remaining_tasks.empty())
        {
            output << "\n  " << string(44, '-') << endl;
            output << "  " << COLOR_RED << "[!] WARNING: Cannot make further progress!" 
                   << COLOR_RESET << endl;
            output << "  The following tasks are NOT READY:" << endl;
            
            for (Task *task : remaining_tasks)
            {
                output << "    - Task " << task->getId() << ": " << task->getName()
                       << " (waiting on dependencies)" << endl;
                not_ready_count++;
            }
            break;
        }
    }

    // Print summary
    output << "\n+============================================+" << endl;
    if (not_ready_count == 0)
        output << "  " << COLOR_GREEN << "[SUCCESS] ALL TASKS COMPLETED!" << COLOR_RESET << endl;
    else
        output << "  " << COLOR_YELLOW << "[WARNING] " << not_ready_count 
               << " TASK(S) NOT READY" << COLOR_RESET << endl;
    output << "+============================================+\n" << endl;
}

// Execute task and all subtasks recursively
void TaskExecutor::executeTaskWithSubtasks(Task *task, int indent)
{
    if (task == nullptr || task->getStatus() == COMPLETED)
        return;

    // Print starting status
    printTaskExecution(task, indent, "RUNNING");

    // Execute subtasks first (depth-first)
    for (Task *subtask : task->getSubtasks())
    {
        if (subtask->getStatus() != COMPLETED && subtask->isReady())
            executeTaskWithSubtasks(subtask, indent + 1);
    }

    // Show progress animation
    showProgressAnimation(task, indent);

    // Mark complete and update time
    task->markComplete();
    total_execution_time += task->getEstimatedTime();

    // Print completion status
    printTaskExecution(task, indent, "COMPLETED");
}

// Display progress bar animation
void TaskExecutor::showProgressAnimation(Task *task, int indent)
{
    string indentation(indent * 2, ' ');
    int estimatedTime = task->getEstimatedTime();

    output << "  " << indentation << COLOR_CYAN << "    Progress: [";
    output.flush();

    int steps = (estimatedTime > 10) ? 10 : estimatedTime;
    int delayPerStep = (estimatedTime * EXEC_DELAY_MS) / steps;

    for (int i = 0; i < steps; i++)
    {
        output << "=";
        output.flush();
        Sleep(delayPerStep);
    }

    output << "] 100%" << COLOR_RESET << endl;
    output.flush();
}

// Print task execution status with formatting
void TaskExecutor::printTaskExecution(Task *task, int indent, const string &action)
{
    string indentation(indent * 2, ' ');
    string actionColor = (action == "RUNNING") ? COLOR_BLUE : COLOR_GREEN;
    string actionSymbol = (action == "RUNNING") ? "[~]" : "[+]";

    output << "  " << indentation << actionColor << actionSymbol << " " 
           << action << COLOR_RESET << ": Task" << task->getId() << " - " 
           << task->getName() << " (P=" << task->getPriority()
           << ", D=" << task->getDeadline() << "d)" << endl;
    output.flush();
}

// Get total execution time
int TaskExecutor::getTotalExecutionTime() const
{
    return total_execution_time;
}

// Reset execution time counter
void TaskExecutor::resetExecutionTime()
{
    total_execution_time = 0;
}
