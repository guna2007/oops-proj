#include "task.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

// Constructor - Initialize task with given parameters
Task::Task(int id, const string &name, int priority, int deadline, int time)
    : id(id), name(name), priority(priority), deadline(deadline),
      status(PENDING), estimated_time(time)
{
}

// Destructor
Task::~Task()
{
}

// Getters for task properties
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

// Add a subtask to this task
void Task::addSubtask(Task *t)
{
    if (t != nullptr)
        subtasks.push_back(t);
}

// Add a dependency that must complete before this task
void Task::addDependency(Task *t)
{
    if (t != nullptr)
        dependencies.push_back(t);
}

// Check if all dependencies are completed
bool Task::isReady() const
{
    for (const Task *dep : dependencies)
    {
        if (dep->getStatus() != COMPLETED)
            return false;
    }
    return true;
}

// Execute the task (simulated with sleep)
void Task::execute()
{
    status = RUNNING;
    Sleep(estimated_time * 1000); // Sleep for estimated time
    status = COMPLETED;
}

// Mark task as complete
void Task::markComplete()
{
    status = COMPLETED;
}

// Display task info with proper indentation
void Task::displayInfo(int indent) const
{
    string indentation(indent * 3, ' ');
    string statusStr, statusColor, prefix;

    // Set status string and color
    switch (status)
    {
    case PENDING:
        statusStr = "PENDING ";
        statusColor = "\033[1;33m";
        break;
    case RUNNING:
        statusStr = "RUNNING ";
        statusColor = "\033[1;34m";
        break;
    case COMPLETED:
        statusStr = "COMPLETE";
        statusColor = "\033[1;32m";
        break;
    }

    // Set tree prefix based on indent level
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

// Display task hierarchy recursively
void Task::displayHierarchy(int indent) const
{
    displayInfo(indent);
    for (const Task *subtask : subtasks)
        subtask->displayHierarchy(indent + 1);
}

// Count total subtasks recursively
int Task::getTotalSubtasks() const
{
    int count = subtasks.size();
    for (const Task *subtask : subtasks)
        count += subtask->getTotalSubtasks();
    return count;
}

// ========== OPERATOR OVERLOADING ==========

// Comparison operators - Compare by priority
bool Task::operator<(const Task &other) const
{
    return this->priority < other.priority;
}

bool Task::operator>(const Task &other) const
{
    return this->priority > other.priority;
}

bool Task::operator<=(const Task &other) const
{
    return this->priority <= other.priority;
}

bool Task::operator>=(const Task &other) const
{
    return this->priority >= other.priority;
}

bool Task::operator==(const Task &other) const
{
    return this->id == other.id;
}

bool Task::operator!=(const Task &other) const
{
    return this->id != other.id;
}

// Arithmetic operators - Create new task with modified priority
Task Task::operator+(int value) const
{
    Task result = *this;
    result.priority = min(10, max(1, this->priority + value)); // Clamp to 1-10
    return result;
}

Task Task::operator-(int value) const
{
    Task result = *this;
    result.priority = min(10, max(1, this->priority - value)); // Clamp to 1-10
    return result;
}

// Compound assignment - Modify priority in place
Task &Task::operator+=(int value)
{
    this->priority = min(10, max(1, this->priority + value));
    return *this;
}

Task &Task::operator-=(int value)
{
    this->priority = min(10, max(1, this->priority - value));
    return *this;
}

// Increment operators
Task &Task::operator++() // Pre-increment
{
    if (this->priority < 10)
        this->priority++;
    return *this;
}

Task Task::operator++(int) // Post-increment
{
    Task temp = *this;
    if (this->priority < 10)
        this->priority++;
    return temp;
}

// Decrement operators
Task &Task::operator--() // Pre-decrement
{
    if (this->priority > 1)
        this->priority--;
    return *this;
}

Task Task::operator--(int) // Post-decrement
{
    Task temp = *this;
    if (this->priority > 1)
        this->priority--;
    return temp;
}

// Stream insertion operator
ostream &operator<<(ostream &os, const Task &task)
{
    string statusStr;
    switch (task.status)
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

    os << "Task[ID=" << task.id << ", Name=\"" << task.name
       << "\", Priority=" << task.priority
       << ", Deadline=" << task.deadline << "d"
       << ", Status=" << statusStr
       << ", Time=" << task.estimated_time << "u]";
    return os;
}

// Assignment operator
Task &Task::operator=(const Task &other)
{
    if (this != &other)
    {
        this->id = other.id;
        this->name = other.name;
        this->priority = other.priority;
        this->deadline = other.deadline;
        this->status = other.status;
        this->estimated_time = other.estimated_time;
    }
    return *this;
}
