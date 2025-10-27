#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

#include "scheduler.h"

// OOP Concept: Inheritance - PriorityScheduler inherits from Scheduler
// OOP Concept: Polymorphism - Implements abstract schedule() method

class PriorityScheduler : public Scheduler
{
public:
    // OOP Concept: Polymorphism - Override pure virtual function
    std::vector<Task *> schedule(const std::vector<Task *> &tasks) override;

    std::string getName() const override;
};

#endif // PRIORITY_SCHEDULER_H
