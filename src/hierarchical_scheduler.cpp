#include "hierarchical_scheduler.h"
#include <algorithm>

using namespace std;

// OOP Concept: Polymorphism - Concrete implementation of abstract interface
// OOP Concept: Recursion - Uses recursive tree traversal

vector<Task *> HierarchicalScheduler::schedule(const vector<Task *> &tasks)
{
    vector<Task *> scheduled;
    set<int> visited;

    // First, identify root tasks (tasks that are not subtasks of others)
    set<int> allTaskIds;
    set<int> subtaskIds;

    for (Task *task : tasks)
    {
        allTaskIds.insert(task->getId());
        for (Task *subtask : task->getSubtasks())
        {
            subtaskIds.insert(subtask->getId());
        }
    }

    // Root tasks are those not in subtaskIds
    vector<Task *> rootTasks;
    for (Task *task : tasks)
    {
        if (subtaskIds.find(task->getId()) == subtaskIds.end())
        {
            rootTasks.push_back(task);
        }
    }

    // Sort root tasks by priority for consistent ordering
    sort(rootTasks.begin(), rootTasks.end(),
         [](const Task *a, const Task *b)
         {
             return a->getPriority() > b->getPriority();
         });

    // OOP Concept: Recursion - Traverse each root task and its subtasks
    for (Task *root : rootTasks)
    {
        collectTasksInOrder(root, scheduled, visited);
    }

    return scheduled;
}

// OOP Concept: Recursion - Recursive method to collect tasks in hierarchical order
void HierarchicalScheduler::collectTasksInOrder(Task *task, vector<Task *> &result, set<int> &visited)
{
    if (task == nullptr || visited.find(task->getId()) != visited.end())
    {
        return;
    }

    // Mark as visited
    visited.insert(task->getId());

    // Add current task
    result.push_back(task);

    // Recursively add all subtasks
    for (Task *subtask : task->getSubtasks())
    {
        collectTasksInOrder(subtask, result, visited);
    }
}

string HierarchicalScheduler::getName() const
{
    return "HierarchicalScheduler";
}
