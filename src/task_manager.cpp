#include "task_manager.h"
#include "priority_scheduler.h"
#include "deadline_scheduler.h"
#include "hierarchical_scheduler.h"
#include <iostream>
#include <limits>
#include <set>

// OOP Concept: Encapsulation - All task management logic encapsulated in this class

TaskManager::TaskManager()
    : next_task_id(1), completed_tasks(0), total_simulated_time(0),
      last_scheduler_name("None")
{
    // Default scheduler is PriorityScheduler
    current_scheduler = std::make_unique<PriorityScheduler>();
}

// OOP Concept: Abstraction - Main interface hiding complex CLI logic
void TaskManager::run()
{
    int choice;

    std::cout << "========================================" << std::endl;
    std::cout << "HIERARCHICAL TASK SCHEDULING ENGINE" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    while (true)
    {
        displayMenu();

        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
            std::cout << "Exiting HTSE. Goodbye!" << std::endl;
            return;
        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
        }

        std::cout << std::endl;
    }
}

void TaskManager::displayMenu() const
{
    std::cout << "========================================" << std::endl;
    std::cout << "MAIN MENU" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Add New Task" << std::endl;
    std::cout << "2. Add Subtask to Existing Task" << std::endl;
    std::cout << "3. Set Task Dependency" << std::endl;
    std::cout << "4. Choose Scheduling Strategy" << std::endl;
    std::cout << "5. Display Task Hierarchy" << std::endl;
    std::cout << "6. Execute All Tasks" << std::endl;
    std::cout << "7. View Execution Report" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Enter your choice: ";
}

void TaskManager::addNewTask()
{
    std::string name;
    int priority, deadline, time;

    std::cout << "Enter Task Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Priority (1-10, 10 highest): ";
    while (!(std::cin >> priority) || priority < 1 || priority > 10)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid priority! Enter a number between 1 and 10: ";
    }

    std::cout << "Enter Deadline (integer days from now): ";
    while (!(std::cin >> deadline) || deadline < 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid deadline! Enter a positive number: ";
    }

    std::cout << "Enter Estimated Execution Time (units): ";
    while (!(std::cin >> time) || time < 1)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid time! Enter a positive number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Task *new_task = createTask(name, priority, deadline, time);
    std::cout << "Task [" << name << "] added with ID " << new_task->getId() << std::endl;
}

void TaskManager::addSubtaskToTask()
{
    if (all_tasks.empty())
    {
        std::cout << "No tasks available! Create tasks first." << std::endl;
        return;
    }

    int parent_id, subtask_id;

    std::cout << "Enter Parent Task ID: ";
    if (!(std::cin >> parent_id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input!" << std::endl;
        return;
    }

    std::cout << "Enter Subtask ID: ";
    if (!(std::cin >> subtask_id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input!" << std::endl;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!validateTaskId(parent_id) || !validateTaskId(subtask_id))
    {
        std::cout << "Invalid task ID(s)!" << std::endl;
        return;
    }

    if (parent_id == subtask_id)
    {
        std::cout << "Error: A task cannot be its own subtask!" << std::endl;
        return;
    }

    addSubtask(parent_id, subtask_id);
    std::cout << "Subtask " << subtask_id << " added under Parent " << parent_id << std::endl;
}

void TaskManager::setTaskDependency()
{
    if (all_tasks.empty())
    {
        std::cout << "No tasks available! Create tasks first." << std::endl;
        return;
    }

    int task_id, dependency_id;

    std::cout << "Enter Task ID: ";
    if (!(std::cin >> task_id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input!" << std::endl;
        return;
    }

    std::cout << "Enter Dependency Task ID: ";
    if (!(std::cin >> dependency_id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input!" << std::endl;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!validateTaskId(task_id) || !validateTaskId(dependency_id))
    {
        std::cout << "Invalid task ID(s)!" << std::endl;
        return;
    }

    if (task_id == dependency_id)
    {
        std::cout << "Error: A task cannot depend on itself!" << std::endl;
        return;
    }

    addDependency(task_id, dependency_id);

    // Check for circular dependencies
    if (hasCircularDependencies())
    {
        // Note: For simplicity, we'll just warn; in production, would rollback
        std::cout << "WARNING: This dependency may create a cycle!" << std::endl;
    }

    std::cout << "Dependency added: Task " << task_id << " depends on " << dependency_id << std::endl;
}

void TaskManager::chooseSchedulingStrategy()
{
    int choice;

    std::cout << "Select Scheduling Strategy:" << std::endl;
    std::cout << "1. Priority Based" << std::endl;
    std::cout << "2. Deadline Based" << std::endl;
    std::cout << "3. Hierarchical" << std::endl;
    std::cout << "Enter your choice: ";

    if (!(std::cin >> choice))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input!" << std::endl;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice)
    {
    case 1:
        setScheduler(std::make_unique<PriorityScheduler>());
        std::cout << "PriorityScheduler selected" << std::endl;
        break;
    case 2:
        setScheduler(std::make_unique<DeadlineScheduler>());
        std::cout << "DeadlineScheduler selected" << std::endl;
        break;
    case 3:
        setScheduler(std::make_unique<HierarchicalScheduler>());
        std::cout << "HierarchicalScheduler selected" << std::endl;
        break;
    default:
        std::cout << "Invalid choice! Keeping current scheduler." << std::endl;
    }
}

void TaskManager::displayTaskHierarchy() const
{
    if (all_tasks.empty())
    {
        std::cout << "No tasks to display!" << std::endl;
        return;
    }

    std::cout << "========================================" << std::endl;
    std::cout << "TASK HIERARCHY" << std::endl;
    std::cout << "========================================" << std::endl;

    // Find root tasks (tasks that are not subtasks of others)
    std::set<int> subtask_ids;
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

    std::cout << "========================================" << std::endl;
}

void TaskManager::executeAllTasks()
{
    if (all_tasks.empty())
    {
        std::cout << "No tasks to execute!" << std::endl;
        return;
    }

    if (!current_scheduler)
    {
        std::cout << "No scheduler selected! Using default PriorityScheduler." << std::endl;
        current_scheduler = std::make_unique<PriorityScheduler>();
    }

    // Check for circular dependencies before execution
    if (hasCircularDependencies())
    {
        std::cout << "ERROR: Circular dependencies detected! Cannot execute." << std::endl;
        std::cout << "Please review and fix task dependencies." << std::endl;
        return;
    }

    executeAll();
}

void TaskManager::printSummaryReport() const
{
    std::cout << "========================================" << std::endl;
    std::cout << "EXECUTION REPORT" << std::endl;
    std::cout << "========================================" << std::endl;

    int total_tasks = all_tasks.size();
    int total_subtasks = 0;
    int completed = 0;

    for (const auto &task_ptr : all_tasks)
    {
        total_subtasks += task_ptr->getTotalSubtasks();
        if (task_ptr->getStatus() == COMPLETED)
        {
            completed++;
        }
    }

    std::cout << "Total Tasks: " << total_tasks << std::endl;
    std::cout << "Total Subtasks: " << total_subtasks << std::endl;
    std::cout << "Completed: " << completed << " / " << total_tasks << std::endl;
    std::cout << "Scheduler Used: " << last_scheduler_name << std::endl;
    std::cout << "Simulated Execution Time: " << total_simulated_time << " units" << std::endl;
    std::cout << "========================================" << std::endl;
}

// OOP Concept: Encapsulation - Task creation logic encapsulated
Task *TaskManager::createTask(const std::string &name, int priority, int deadline, int time)
{
    auto task = std::make_unique<Task>(next_task_id, name, priority, deadline, time);
    Task *task_ptr = task.get();
    task_map[next_task_id] = task_ptr;
    all_tasks.push_back(std::move(task));
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
void TaskManager::setScheduler(std::unique_ptr<Scheduler> sched)
{
    current_scheduler = std::move(sched);
}

void TaskManager::executeAll()
{
    if (!current_scheduler)
    {
        std::cout << "No scheduler set!" << std::endl;
        return;
    }

    // Collect all tasks as raw pointers
    std::vector<Task *> task_ptrs;
    for (const auto &task_ptr : all_tasks)
    {
        task_ptrs.push_back(task_ptr.get());
    }

    // OOP Concept: Polymorphism - schedule() calls the appropriate scheduler implementation
    std::vector<Task *> scheduled_tasks = current_scheduler->schedule(task_ptrs);

    // Store scheduler name for report
    last_scheduler_name = current_scheduler->getName();

    // Reset executor
    executor.resetExecutionTime();

    // Execute tasks
    executor.runTasks(scheduled_tasks);

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
bool TaskManager::detectCycle(Task *start, std::set<int> &visited, std::set<int> &rec_stack) const
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
    std::set<int> visited;
    std::set<int> rec_stack;

    for (const auto &task_ptr : all_tasks)
    {
        if (detectCycle(task_ptr.get(), visited, rec_stack))
        {
            return true;
        }
    }

    return false;
}
