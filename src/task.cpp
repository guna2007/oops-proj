#include "task.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

// OOP Concept: Encapsulation - Implementation details hidden from users

Task::Task(int id, const string &name, int priority, int deadline, int time)
    : id(id), name(name), priority(priority), deadline(deadline),
      status(PENDING), estimated_time(time)
{
}

Task::~Task()
{
    // Note: Task does not own subtasks or dependencies, so no deletion here
    // TaskManager will handle cleanup
}

// Getters - OOP Concept: Encapsulation (controlled read access)
int Task::getId() const
{
    return id;
}

string Task::getName() const
{
    return name;
}

int Task::getPriority() const
{
    return priority;
}

int Task::getDeadline() const
{
    return deadline;
}

TaskStatus Task::getStatus() const
{
    return status;
}

int Task::getEstimatedTime() const
{
    return estimated_time;
}

const vector<Task *> &Task::getSubtasks() const
{
    return subtasks;
}

const vector<Task *> &Task::getDependencies() const
{
    return dependencies;
}

// OOP Concept: Composition - Managing child tasks
void Task::addSubtask(Task *t)
{
    if (t != nullptr)
    {
        subtasks.push_back(t);
    }
}

// OOP Concept: Aggregation - Maintaining references to dependency tasks
void Task::addDependency(Task *t)
{
    if (t != nullptr)
    {
        dependencies.push_back(t);
    }
}

// OOP Concept: Encapsulation - Business logic encapsulated in method
bool Task::isReady() const
{
    // Check if all dependencies are completed
    for (const Task *dep : dependencies)
    {
        if (dep->getStatus() != COMPLETED)
        {
            return false;
        }
    }
    return true;
}

// OOP Concept: Abstraction - Simulates execution without exposing details
void Task::execute()
{
    status = RUNNING;
    // Simulate realistic work with 500ms delay
    Sleep(5000); // Windows API sleep function (milliseconds)
    status = COMPLETED;
}

void Task::markComplete()
{
    status = COMPLETED;
}

// OOP Concept: Abstraction - Display logic abstracted into method
void Task::displayInfo(int indent) const
{
    string indentation(indent * 3, ' ');
    string statusStr;
    string statusColor;

    switch (status)
    {
    case PENDING:
        statusStr = "PENDING ";
        statusColor = "\033[1;33m"; // Yellow
        break;
    case RUNNING:
        statusStr = "RUNNING ";
        statusColor = "\033[1;34m"; // Blue
        break;
    case COMPLETED:
        statusStr = "COMPLETE";
        statusColor = "\033[1;32m"; // Green
        break;
    }

    // Tree structure symbols
    string prefix = "";
    if (indent == 0)
        prefix = "[*] ";
    else if (indent == 1)
        prefix = " |-- ";
    else
        prefix = " |   +-- ";

    cout << indentation << prefix << "Task " << id << ": " << name
         << " [P=" << priority << ", D=" << deadline << "d, "
         << statusColor << statusStr << "\033[0m" << "]" << endl;
}

// OOP Concept: Recursion - Displaying hierarchical structure recursively
void Task::displayHierarchy(int indent) const
{
    displayInfo(indent);

    // Recursively display all subtasks
    for (const Task *subtask : subtasks)
    {
        subtask->displayHierarchy(indent + 1);
    }
}

// OOP Concept: Recursion - Counting subtasks recursively
int Task::getTotalSubtasks() const
{
    int count = subtasks.size();
    for (const Task *subtask : subtasks)
    {
        count += subtask->getTotalSubtasks();
    }
    return count;
}
