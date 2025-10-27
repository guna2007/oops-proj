#include "deadline_scheduler.h"
#include <algorithm>

using namespace std;

// OOP Concept: Polymorphism - Concrete implementation of abstract interface

vector<Task *> DeadlineScheduler::schedule(const vector<Task *> &tasks)
{
    // Create a copy of the task list to sort
    vector<Task *> scheduled = tasks;

    // Sort by deadline in ascending order (earliest deadline first)
    // OOP Concept: Encapsulation - Uses Task's public getDeadline() method
    sort(scheduled.begin(), scheduled.end(),
         [](const Task *a, const Task *b)
         {
             return a->getDeadline() < b->getDeadline();
         });

    return scheduled;
}

string DeadlineScheduler::getName() const
{
    return "DeadlineScheduler";
}
