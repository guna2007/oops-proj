#include "deadline_scheduler.h"
#include <algorithm>

// OOP Concept: Polymorphism - Concrete implementation of abstract interface

std::vector<Task *> DeadlineScheduler::schedule(const std::vector<Task *> &tasks)
{
    // Create a copy of the task list to sort
    std::vector<Task *> scheduled = tasks;

    // Sort by deadline in ascending order (earliest deadline first)
    // OOP Concept: Encapsulation - Uses Task's public getDeadline() method
    std::sort(scheduled.begin(), scheduled.end(),
              [](const Task *a, const Task *b)
              {
                  return a->getDeadline() < b->getDeadline();
              });

    return scheduled;
}

std::string DeadlineScheduler::getName() const
{
    return "DeadlineScheduler";
}
