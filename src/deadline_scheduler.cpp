#include "deadline_scheduler.h"
#include <algorithm>

using namespace std;

// Comparator function for sorting by deadline
static bool compareDeadline(const Task *a, const Task *b)
{
    return a->getDeadline() < b->getDeadline(); // Earliest deadline first
}

// Schedule tasks by deadline (earliest first)
vector<Task *> DeadlineScheduler::schedule(const vector<Task *> &tasks)
{
    vector<Task *> scheduled = tasks;
    sort(scheduled.begin(), scheduled.end(), compareDeadline);
    return scheduled;
}

// Return scheduler name
string DeadlineScheduler::getName() const
{
    return "DeadlineScheduler";
}
