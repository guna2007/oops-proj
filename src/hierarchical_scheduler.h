#ifndef HIERARCHICAL_SCHEDULER_H
#define HIERARCHICAL_SCHEDULER_H

#include "scheduler.h"
#include <set>

// OOP Concept: Inheritance - HierarchicalScheduler inherits from Scheduler
// OOP Concept: Polymorphism - Implements abstract schedule() method

class HierarchicalScheduler : public Scheduler
{
private:
    // Helper methods for hierarchical traversal
    // OOP Concept: Recursion - Used in tree traversal
    void collectTasksInOrder(Task *task, std::vector<Task *> &result, std::set<int> &visited);

public:
    // OOP Concept: Polymorphism - Override pure virtual function
    std::vector<Task *> schedule(const std::vector<Task *> &tasks) override;

    std::string getName() const override;
};

#endif // HIERARCHICAL_SCHEDULER_H
