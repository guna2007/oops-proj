#include "priority_scheduler.h"
#include <algorithm>

// OOP Concept: Polymorphism - Concrete implementation of abstract interface

std::vector<Task *> PriorityScheduler::schedule(const std::vector<Task *> &tasks)
{
    // Create a copy of the task list to sort
    std::vector<Task *> scheduled = tasks;

    // Sort by priority in descending order (higher priority first)
    // OOP Concept: Encapsulation - Uses Task's public getPriority() method
    std::sort(scheduled.begin(), scheduled.end(),
              [](const Task *a, const Task *b)
              {
                  return a->getPriority() > b->getPriority();
              });

    return scheduled;
}

std::string PriorityScheduler::getName() const
{
    return "PriorityScheduler";
}
