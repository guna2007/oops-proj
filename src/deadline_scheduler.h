#ifndef DEADLINE_SCHEDULER_H
#define DEADLINE_SCHEDULER_H

#include "scheduler.h"

using namespace std;

// OOP Concept: Inheritance - DeadlineScheduler inherits from Scheduler
// OOP Concept: Polymorphism - Implements abstract schedule() method

class DeadlineScheduler : public Scheduler
{
public:
    // OOP Concept: Polymorphism - Override pure virtual function
    vector<Task *> schedule(const vector<Task *> &tasks) override;

    string getName() const override;
};

#endif // DEADLINE_SCHEDULER_H
