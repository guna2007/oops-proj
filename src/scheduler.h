#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "task.h"

using namespace std;

// OOP Concept: Abstraction - Scheduler is an abstract base class defining interface
// OOP Concept: Polymorphism - Different schedulers can be used interchangeably

class Scheduler
{
public:
    // Virtual destructor for proper cleanup of derived classes
    virtual ~Scheduler() = default;

    // OOP Concept: Abstraction - Pure virtual function defines interface
    // OOP Concept: Polymorphism - Derived classes provide specific implementations
    virtual vector<Task *> schedule(const vector<Task *> &tasks) = 0;

    // Virtual method to get scheduler name for reporting
    virtual string getName() const = 0;
};

#endif // SCHEDULER_H
