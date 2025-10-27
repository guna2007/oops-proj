#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

#include "scheduler.h"

using namespace std;

// OOP Concept: Inheritance - PriorityScheduler inherits from Scheduler
// OOP Concept: Polymorphism - Implements abstract schedule() method

class PriorityScheduler : public Scheduler
{
public:
    // OOP Concept: Polymorphism - Override pure virtual function
    vector<Task *> schedule(const vector<Task *> &tasks) override;

    string getName() const override;
};

#endif // PRIORITY_SCHEDULER_H
