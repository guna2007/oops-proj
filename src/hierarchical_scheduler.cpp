#include "hierarchical_scheduler.h"
#include <algorithm>

// OOP Concept: Polymorphism - Concrete implementation of abstract interface
// OOP Concept: Recursion - Uses recursive tree traversal

std::vector<Task *> HierarchicalScheduler::schedule(const std::vector<Task *> &tasks)
{
    std::vector<Task *> scheduled;
    std::set<int> visited;

    // First, identify root tasks (tasks that are not subtasks of others)
    std::set<int> allTaskIds;
    std::set<int> subtaskIds;

    for (Task *task : tasks)
    {
        allTaskIds.insert(task->getId());
        for (Task *subtask : task->getSubtasks())
        {
            subtaskIds.insert(subtask->getId());
        }
    }

    // Root tasks are those not in subtaskIds
    std::vector<Task *> rootTasks;
    for (Task *task : tasks)
    {
        if (subtaskIds.find(task->getId()) == subtaskIds.end())
        {
            rootTasks.push_back(task);
        }
    }

    // Sort root tasks by priority for consistent ordering
    std::sort(rootTasks.begin(), rootTasks.end(),
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
void HierarchicalScheduler::collectTasksInOrder(Task *task, std::vector<Task *> &result, std::set<int> &visited)
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

std::string HierarchicalScheduler::getName() const
{
    return "HierarchicalScheduler";
}
