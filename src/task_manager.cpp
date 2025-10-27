#include "task_manager.h"
#include "priority_scheduler.h"
#include "deadline_scheduler.h"
#include "hierarchical_scheduler.h"
#include <iostream>
#include <limits>
#include <set>

using namespace std;

// OOP Concept: Encapsulation - All task management logic encapsulated in this class

TaskManager::TaskManager()
    : next_task_id(1), completed_tasks(0), total_simulated_time(0),
      last_scheduler_name("None")
{
    // Default scheduler is PriorityScheduler
    current_scheduler = make_unique<PriorityScheduler>();
}

// OOP Concept: Abstraction - Main interface hiding complex CLI logic
void TaskManager::run()
{
    int choice;

    // Print branded header
    cout << "\033[1;36m"; // Cyan bold
    cout << "+============================================================+" << endl;
    cout << "|     HIERARCHICAL TASK SCHEDULING ENGINE (HTSE)            |" << endl;
    cout << "|                    [OOP Project Demo]                     |" << endl;
    cout << "+============================================================+" << endl;
    cout << "\033[0m"; // Reset color
    cout << endl;

    while (true)
    {
        displayMenu();

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            addNewTask();
            break;
        case 2:
            addSubtaskToTask();
            break;
        case 3:
            setTaskDependency();
            break;
        case 4:
            chooseSchedulingStrategy();
            break;
        case 5:
            displayTaskHierarchy();
            break;
        case 6:
            executeAllTasks();
            break;
        case 7:
            printSummaryReport();
            break;
        case 0:
            cout << "\n\033[1;36m";
            cout << "+============================================================+" << endl;
            cout << "|         Thank you for using HTSE! Goodbye!                |" << endl;
            cout << "+============================================================+\033[0m" << endl;
            return;
        default:
            cout << "\033[1;31m[!] Invalid choice! Please try again.\033[0m" << endl;
        }

        cout << endl;
    }
}

void TaskManager::displayMenu() const
{
    cout << "\033[1;33m"; // Yellow bold
    cout << "\n>>> MAIN MENU <<<\n";
    cout << "\033[0m"; // Reset

    cout << "+-----------------------------------------------+" << endl;
    cout << "| [1] >> Add New Task                          |" << endl;
    cout << "| [2] >> Add Subtask to Existing Task          |" << endl;
    cout << "| [3] >> Set Task Dependency                   |" << endl;
    cout << "| [4] >> Choose Scheduling Strategy            |" << endl;
    cout << "| [5] >> Display Task Hierarchy                |" << endl;
    cout << "| [6] >> Execute All Tasks                     |" << endl;
    cout << "| [7] >> View Execution Report                 |" << endl;
    cout << "| [0] >> Exit                                  |" << endl;
    cout << "+-----------------------------------------------+" << endl;
    cout << "\n\033[1;37mEnter your choice: \033[0m";
}

void TaskManager::addNewTask()
{
    string name;
    int priority, deadline, time;

    cout << "\n\033[1;36m--- Add New Task ---\033[0m" << endl;
    cout << "Task Name: ";
    getline(cin, name);

    cout << "Priority (1-10, 10=highest): ";
    while (!(cin >> priority) || priority < 1 || priority > 10)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[1;31m[!] Invalid!\033[0m Enter 1-10: ";
    }

    cout << "Deadline (days from now): ";
    while (!(cin >> deadline) || deadline < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[1;31m[!] Invalid!\033[0m Enter positive number: ";
    }

    cout << "Execution Time (units): ";
    while (!(cin >> time) || time < 1)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[1;31m[!] Invalid!\033[0m Enter positive number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Task *new_task = createTask(name, priority, deadline, time);
    cout << "\n\033[1;32m[SUCCESS] Task created!\033[0m" << endl;
    cout << "  ID: " << new_task->getId() << " | Name: \"" << name << "\"" << endl;
    cout << "  Priority: " << priority << " | Deadline: " << deadline << "d | Time: " << time << "u" << endl;
}

void TaskManager::addSubtaskToTask()
{
    if (all_tasks.empty())
    {
        cout << "\n\033[1;31m[!] No tasks available! Create tasks first.\033[0m" << endl;
        return;
    }

    int parent_id, subtask_id;

    cout << "\n\033[1;36m--- Add Subtask Relationship ---\033[0m" << endl;
    cout << "Parent Task ID: ";
    if (!(cin >> parent_id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[1;31m[!] Invalid input!\033[0m" << endl;
        return;
    }

    cout << "Child/Subtask ID: ";
    if (!(cin >> subtask_id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[1;31m[!] Invalid input!\033[0m" << endl;
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!validateTaskId(parent_id) || !validateTaskId(subtask_id))
    {
        cout << "\033[1;31m[!] Invalid task ID(s)!\033[0m" << endl;
        return;
    }

    if (parent_id == subtask_id)
    {
        cout << "\033[1;31m[!] Error: A task cannot be its own subtask!\033[0m" << endl;
        return;
    }

    addSubtask(parent_id, subtask_id);
    cout << "\n\033[1;32m[SUCCESS] Subtask relationship created!\033[0m" << endl;
    cout << "  Parent Task #" << parent_id << " --> Child Task #" << subtask_id << endl;
}

void TaskManager::setTaskDependency()
{
    if (all_tasks.empty())
    {
        cout << "\n\033[1;31m[!] No tasks available! Create tasks first.\033[0m" << endl;
        return;
    }

    int task_id, dependency_id;

    cout << "\n\033[1;36m--- Set Task Dependency ---\033[0m" << endl;
    cout << "Task ID (will depend on another): ";
    if (!(cin >> task_id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[1;31m[!] Invalid input!\033[0m" << endl;
        return;
    }

    cout << "Dependency Task ID (must complete first): ";
    if (!(cin >> dependency_id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[1;31m[!] Invalid input!\033[0m" << endl;
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!validateTaskId(task_id) || !validateTaskId(dependency_id))
    {
        cout << "\033[1;31m[!] Invalid task ID(s)!\033[0m" << endl;
        return;
    }

    if (task_id == dependency_id)
    {
        cout << "\033[1;31m[!] Error: A task cannot depend on itself!\033[0m" << endl;
        return;
    }

    addDependency(task_id, dependency_id);

    // Check for circular dependencies
    if (hasCircularDependencies())
    {
        // Note: For simplicity, we'll just warn; in production, would rollback
        cout << "\n\033[1;33m[WARNING] This dependency may create a cycle!\033[0m" << endl;
    }

    cout << "\n\033[1;32m[SUCCESS] Dependency added!\033[0m" << endl;
    cout << "  Task #" << task_id << " now depends on Task #" << dependency_id << endl;
}

void TaskManager::chooseSchedulingStrategy()
{
    int choice;

    cout << "\n\033[1;36m+-------------------------------------------+" << endl;
    cout << "|      SELECT SCHEDULING STRATEGY           |" << endl;
    cout << "+-------------------------------------------+\033[0m" << endl;
    cout << "  [1] Priority Based (highest priority first)" << endl;
    cout << "  [2] Deadline Based (earliest deadline first)" << endl;
    cout << "  [3] Hierarchical (parent tasks first)" << endl;
    cout << "\nYour choice: ";

    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[1;31m[!] Invalid input!\033[0m" << endl;
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice)
    {
    case 1:
        setScheduler(make_unique<PriorityScheduler>());
        cout << "\n\033[1;32m[SUCCESS] PriorityScheduler activated!\033[0m" << endl;
        break;
    case 2:
        setScheduler(make_unique<DeadlineScheduler>());
        cout << "\n\033[1;32m[SUCCESS] DeadlineScheduler activated!\033[0m" << endl;
        break;
    case 3:
        setScheduler(make_unique<HierarchicalScheduler>());
        cout << "\n\033[1;32m[SUCCESS] HierarchicalScheduler activated!\033[0m" << endl;
        break;
    default:
        cout << "\n\033[1;31m[!] Invalid choice! Keeping current scheduler.\033[0m" << endl;
    }
}

void TaskManager::displayTaskHierarchy() const
{
    if (all_tasks.empty())
    {
        cout << "\033[1;31m[!] No tasks to display!\033[0m" << endl;
        return;
    }

    cout << "\n\033[1;36m";
    cout << "+============================================+" << endl;
    cout << "|           TASK HIERARCHY VIEW              |" << endl;
    cout << "+============================================+\033[0m" << endl;
    cout << "\nLegend: [P=Priority, D=Deadline(days)]\n"
         << endl;

    // Find root tasks (tasks that are not subtasks of others)
    set<int> subtask_ids;
    for (const auto &task_ptr : all_tasks)
    {
        for (const Task *subtask : task_ptr->getSubtasks())
        {
            subtask_ids.insert(subtask->getId());
        }
    }

    // Display hierarchy starting from root tasks
    for (const auto &task_ptr : all_tasks)
    {
        if (subtask_ids.find(task_ptr->getId()) == subtask_ids.end())
        {
            task_ptr->displayHierarchy(0);
        }
    }

    cout << "\n+============================================+" << endl;
}

void TaskManager::executeAllTasks()
{
    if (all_tasks.empty())
    {
        cout << "\n\033[1;31m[!] No tasks to execute!\033[0m" << endl;
        return;
    }

    if (!current_scheduler)
    {
        cout << "\n\033[1;33m[INFO] No scheduler selected. Using default PriorityScheduler.\033[0m" << endl;
        current_scheduler = make_unique<PriorityScheduler>();
    }

    // Check for circular dependencies before execution
    if (hasCircularDependencies())
    {
        cout << "\n\033[1;31m";
        cout << "+============================================+" << endl;
        cout << "|               ERROR DETECTED               |" << endl;
        cout << "+============================================+\033[0m" << endl;
        cout << "  Circular dependencies found!" << endl;
        cout << "  Please review and fix task dependencies." << endl;
        return;
    }

    executeAll();
}

void TaskManager::printSummaryReport() const
{
    cout << "\n\033[1;32m";
    cout << "+============================================+" << endl;
    cout << "|          EXECUTION SUMMARY REPORT          |" << endl;
    cout << "+============================================+\033[0m" << endl;

    int total_root_tasks = 0;
    int total_subtasks = 0;
    int completed = 0;

    // Find root tasks (not subtasks of any other task)
    set<int> subtask_ids;
    for (const auto &task_ptr : all_tasks)
    {
        for (const Task *subtask : task_ptr->getSubtasks())
        {
            subtask_ids.insert(subtask->getId());
        }
    }

    for (const auto &task_ptr : all_tasks)
    {
        total_subtasks += task_ptr->getTotalSubtasks();
        if (task_ptr->getStatus() == COMPLETED)
        {
            completed++;
        }
        // Count root tasks
        if (subtask_ids.find(task_ptr->getId()) == subtask_ids.end())
        {
            total_root_tasks++;
        }
    }

    int overall_tasks = all_tasks.size();

    cout << "\n  >> Total Root Tasks: " << total_root_tasks << endl;
    cout << "  >> Total Subtasks (nested): " << total_subtasks << endl;
    cout << "  >> Overall Tasks Executed: " << overall_tasks << endl;
    cout << "  >> Completed Successfully: \033[1;32m" << completed << "\033[0m / " << overall_tasks << endl;
    cout << "  >> Scheduler Used: \033[1;33m" << last_scheduler_name << "\033[0m" << endl;
    cout << "  >> Simulated Execution Time: " << total_simulated_time << " units" << endl;
    cout << "\n+============================================+" << endl;
}

// OOP Concept: Encapsulation - Task creation logic encapsulated
Task *TaskManager::createTask(const string &name, int priority, int deadline, int time)
{
    auto task = make_unique<Task>(next_task_id, name, priority, deadline, time);
    Task *task_ptr = task.get();
    task_map[next_task_id] = task_ptr;
    all_tasks.push_back(move(task));
    next_task_id++;
    return task_ptr;
}

void TaskManager::addSubtask(int parent_id, int subtask_id)
{
    Task *parent = findTaskById(parent_id);
    Task *subtask = findTaskById(subtask_id);

    if (parent && subtask)
    {
        parent->addSubtask(subtask);
    }
}

void TaskManager::addDependency(int task_id, int dependency_id)
{
    Task *task = findTaskById(task_id);
    Task *dependency = findTaskById(dependency_id);

    if (task && dependency)
    {
        task->addDependency(dependency);
    }
}

// OOP Concept: Polymorphism - Accepts any Scheduler subclass
void TaskManager::setScheduler(unique_ptr<Scheduler> sched)
{
    current_scheduler = move(sched);
}

void TaskManager::executeAll()
{
    if (!current_scheduler)
    {
        cout << "No scheduler set!" << endl;
        return;
    }

    // Collect all tasks as raw pointers
    vector<Task *> task_ptrs;
    for (const auto &task_ptr : all_tasks)
    {
        task_ptrs.push_back(task_ptr.get());
    }

    // OOP Concept: Polymorphism - schedule() calls the appropriate scheduler implementation
    vector<Task *> scheduled_tasks = current_scheduler->schedule(task_ptrs);

    // Store scheduler name for report
    last_scheduler_name = current_scheduler->getName();

    // Reset executor
    executor.resetExecutionTime();

    // Execute tasks with scheduler name displayed
    executor.runTasks(scheduled_tasks, last_scheduler_name);

    // Update statistics
    total_simulated_time = executor.getTotalExecutionTime();
    completed_tasks = 0;
    for (const auto &task_ptr : all_tasks)
    {
        if (task_ptr->getStatus() == COMPLETED)
        {
            completed_tasks++;
        }
    }
}

Task *TaskManager::findTaskById(int id) const
{
    auto it = task_map.find(id);
    if (it != task_map.end())
    {
        return it->second;
    }
    return nullptr;
}

bool TaskManager::validateTaskId(int id) const
{
    return task_map.find(id) != task_map.end();
}

// OOP Concept: Recursion - Cycle detection using DFS
bool TaskManager::detectCycle(Task *start, set<int> &visited, set<int> &rec_stack) const
{
    if (start == nullptr)
    {
        return false;
    }

    int id = start->getId();

    if (rec_stack.find(id) != rec_stack.end())
    {
        // Found a cycle
        return true;
    }

    if (visited.find(id) != visited.end())
    {
        // Already processed this node
        return false;
    }

    visited.insert(id);
    rec_stack.insert(id);

    // Check dependencies
    for (const Task *dep : start->getDependencies())
    {
        if (detectCycle(const_cast<Task *>(dep), visited, rec_stack))
        {
            return true;
        }
    }

    rec_stack.erase(id);
    return false;
}

bool TaskManager::hasCircularDependencies() const
{
    set<int> visited;
    set<int> rec_stack;

    for (const auto &task_ptr : all_tasks)
    {
        if (detectCycle(task_ptr.get(), visited, rec_stack))
        {
            return true;
        }
    }

    return false;
}
