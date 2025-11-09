#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <memory>
#include <map>
#include <set>
#include "config.h"
#include "task.h"
#include "scheduler.h"
#include "task_executor.h"

#ifndef D2_MODE
#include "template_utils.h"
#endif

using namespace std;

// OOP Concept: Encapsulation - TaskManager encapsulates all task management logic
// OOP Concept: Composition - Contains collections of Task objects and a Scheduler

class TaskManager
{
private:
    // OOP Concept: Composition - TaskManager owns and manages Task objects
    vector<unique_ptr<Task>> all_tasks; // Owns tasks (smart pointers)
    map<int, Task *> task_map;          // Quick lookup by ID

#ifdef D2_MODE
    // Deadline 2 Mode: Direct scheduler (no polymorphism)
    class PriorityScheduler *priority_scheduler;
#else
    // Final Mode: Polymorphic scheduler
    unique_ptr<Scheduler> current_scheduler;
#endif

    TaskExecutor executor;
    int next_task_id;

    // Execution statistics
    int completed_tasks;
    int total_simulated_time;
    string last_scheduler_name;

    // UI Helper methods
    void printHeader() const;
    void printMenu() const;
    void printSection(const string &title) const;
    void printLine() const;
    void printSuccess(const string &msg) const;
    void printWarning(const string &msg) const;
    void printError(const string &msg) const;
    int getValidatedInt(const string &prompt, int min, int max);
    bool getTaskIds(int &id1, int &id2, const string &label1, const string &label2);

    // Feature methods
    void displayMenu() const;
    void addNewTask();
    void addSubtaskToTask();
    void setTaskDependency();
    void chooseSchedulingStrategy();
    void displayTaskHierarchy() const;
    void executeAllTasks();
    void printSummaryReport() const;

    // Operator Overloading demonstration methods
    void compareTasksDemo();
    void modifyTaskPriorityDemo();
    void displayTasksWithOperator();

#ifndef D2_MODE
    // Template demonstration methods (Final mode only)
    void statisticsDemo();
    void containerDemo();
    void comparatorDemo();
#endif

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

#ifndef D2_MODE
    // Scheduler management (Final mode only)
    // OOP Concept: Polymorphism - Accepts any Scheduler subclass
    void setScheduler(unique_ptr<Scheduler> sched);
#endif

    // Execution
    void executeAll();
};

#endif // TASK_MANAGER_H
