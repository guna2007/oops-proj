#include "hierarchical_scheduler.h"
#include <algorithm>

using namespace std;

// Schedule tasks in hierarchical order (parents before children)
vector<Task *> HierarchicalScheduler::schedule(const vector<Task *> &tasks)
{
    vector<Task *> scheduled;
    set<int> visited;

    // Identify root tasks and subtasks
    set<int> allTaskIds, subtaskIds;
    for (Task *task : tasks)
    {
        allTaskIds.insert(task->getId());
        for (Task *subtask : task->getSubtasks())
            subtaskIds.insert(subtask->getId());
    }

    // Collect root tasks (not subtasks of any other task)
    vector<Task *> rootTasks;
    for (Task *task : tasks)
    {
        if (subtaskIds.find(task->getId()) == subtaskIds.end())
            rootTasks.push_back(task);
    }

    // Comparator for priority-based sorting
    struct PriorityCompare
    {
        bool operator()(const Task *a, const Task *b) const
        {
            return a->getPriority() > b->getPriority();
        }
    };

    // Sort root tasks by priority
    sort(rootTasks.begin(), rootTasks.end(), PriorityCompare());

    // Traverse hierarchy depth-first
    for (Task *root : rootTasks)
        collectTasksInOrder(root, scheduled, visited);

    return scheduled;
}

// Recursively collect tasks in hierarchical order
void HierarchicalScheduler::collectTasksInOrder(Task *task, vector<Task *> &result, set<int> &visited)
{
    if (task == nullptr || visited.find(task->getId()) != visited.end())
        return;

    visited.insert(task->getId());
    result.push_back(task);

    // Recursively add subtasks
    for (Task *subtask : task->getSubtasks())
        collectTasksInOrder(subtask, result, visited);
}

// Return scheduler name
string HierarchicalScheduler::getName() const
{
    return "HierarchicalScheduler";
}
