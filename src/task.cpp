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
    string indentation(indent * 2, ' ');
    string statusStr;

    switch (status)
    {
    case PENDING:
        statusStr = "PENDING";
        break;
    case RUNNING:
        statusStr = "RUNNING";
        break;
    case COMPLETED:
        statusStr = "COMPLETED";
        break;
    }

    cout << indentation << "Task " << id << ": " << name
         << " (priority=" << priority
         << ", deadline=" << deadline
         << ", status=" << statusStr
         << ", time=" << estimated_time << ")" << endl;
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
