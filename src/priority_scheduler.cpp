#include "priority_scheduler.h"
#include <algorithm>

using namespace std;

// Comparator function for sorting by priority
static bool comparePriority(const Task *a, const Task *b)
{
    return a->getPriority() > b->getPriority(); // Higher priority first
}

// Schedule tasks by priority (highest first)
vector<Task *> PriorityScheduler::schedule(const vector<Task *> &tasks)
{
    vector<Task *> scheduled = tasks;
    sort(scheduled.begin(), scheduled.end(), comparePriority);
    return scheduled;
}

// Return scheduler name
string PriorityScheduler::getName() const
{
    return "PriorityScheduler";
}
