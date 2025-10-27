#ifndef DEADLINE_SCHEDULER_H
#define DEADLINE_SCHEDULER_H

#include "scheduler.h"

// OOP Concept: Inheritance - DeadlineScheduler inherits from Scheduler
// OOP Concept: Polymorphism - Implements abstract schedule() method

class DeadlineScheduler : public Scheduler
{
public:
    // OOP Concept: Polymorphism - Override pure virtual function
    std::vector<Task *> schedule(const std::vector<Task *> &tasks) override;

    std::string getName() const override;
};

#endif // DEADLINE_SCHEDULER_H
