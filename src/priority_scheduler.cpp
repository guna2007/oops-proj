#include "priority_scheduler.h"
#include <algorithm>

using namespace std;

// OOP Concept: Polymorphism - Concrete implementation of abstract interface

vector<Task *> PriorityScheduler::schedule(const vector<Task *> &tasks)
{
    // Create a copy of the task list to sort
    vector<Task *> scheduled = tasks;

    // Sort by priority in descending order (higher priority first)
    // OOP Concept: Encapsulation - Uses Task's public getPriority() method
    sort(scheduled.begin(), scheduled.end(),
         [](const Task *a, const Task *b)
         {
             return a->getPriority() > b->getPriority();
         });

    return scheduled;
}

string PriorityScheduler::getName() const
{
    return "PriorityScheduler";
}
