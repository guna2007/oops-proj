#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <memory>
#include <map>
#include <set>
#include "task.h"
#include "scheduler.h"
#include "task_executor.h"

using namespace std;

// OOP Concept: Encapsulation - TaskManager encapsulates all task management logic
// OOP Concept: Composition - Contains collections of Task objects and a Scheduler

class TaskManager
{
private:
    // OOP Concept: Composition - TaskManager owns and manages Task objects
    vector<unique_ptr<Task>> all_tasks; // Owns tasks (smart pointers)
    map<int, Task *> task_map;          // Quick lookup by ID

    // OOP Concept: Polymorphism - Can hold any Scheduler subclass
    unique_ptr<Scheduler> current_scheduler;

    TaskExecutor executor;
    int next_task_id;

    // Execution statistics
    int completed_tasks;
    int total_simulated_time;
    string last_scheduler_name;

    // Helper methods
    void displayMenu() const;
    void addNewTask();
    void addSubtaskToTask();
    void setTaskDependency();
    void chooseSchedulingStrategy();
    void displayTaskHierarchy() const;
    void executeAllTasks();
    void printSummaryReport() const;

    // Validation helpers
    Task *findTaskById(int id) const;
    bool validateTaskId(int id) const;
    bool detectCycle(Task *start, set<int> &visited, set<int> &rec_stack) const;
    bool hasCircularDependencies() const;

public:
    // Constructor
    TaskManager();

    // Main CLI loop
    // OOP Concept: Abstraction - High-level interface for user interaction
    void run();

    // Task creation and management
    Task *createTask(const string &name, int priority, int deadline, int time);
    void addSubtask(int parent_id, int subtask_id);
    void addDependency(int task_id, int dependency_id);

    // Scheduler management
    // OOP Concept: Polymorphism - Accepts any Scheduler subclass
    void setScheduler(unique_ptr<Scheduler> sched);

    // Execution
    void executeAll();
};

#endif // TASK_MANAGER_H
