#include "task_manager.h"
#include "priority_scheduler.h"
#ifndef D2_MODE
#include "deadline_scheduler.h"
#include "hierarchical_scheduler.h"
#endif
#include <iostream>
#include <limits>
#include <set>

using namespace std;

// OOP Concept: Encapsulation
TaskManager::TaskManager() : next_task_id(1), completed_tasks(0), total_simulated_time(0), last_scheduler_name("PriorityScheduler")
{
#ifdef D2_MODE
    priority_scheduler = new PriorityScheduler();
#else
    current_scheduler = make_unique<PriorityScheduler>();
#endif
}

void TaskManager::printHeader() const
{
    cout << COLOR_CYAN << UI_BORDER << "\n|     HIERARCHICAL TASK SCHEDULING ENGINE (HTSE)            |\n"
         << "|                   OOP Project Demonstration               |\n"
         << UI_BORDER << COLOR_RESET << endl;
}

void TaskManager::printMenu() const
{
    cout << COLOR_YELLOW << "\n>>> MAIN MENU <<<" << COLOR_RESET << "\n+--------------------------------------------------------------+\n"
         << "| TASK MANAGEMENT                                              |\n| [1] Add New Task                                             |\n"
         << "| [2] Add Subtask to Existing Task                             |\n| [3] Set Task Dependency                                      |\n";
#ifndef D2_MODE
    cout << "| [4] Choose Scheduling Strategy                               |\n";
#endif
    cout << "| [5] Display Task Hierarchy                                   |\n| [6] Execute All Tasks                                        |\n"
         << "| [7] View Execution Report                                    |\n|                                                              |\n"
         << "| OPERATOR OVERLOADING DEMOS                                   |\n| [8] Compare Tasks (>, <, ==, !=)                             |\n"
         << "| [9] Modify Task Priority (+, -, ++, --)                      |\n| [10] Display Tasks with << Operator                          |\n";
#ifndef D2_MODE
    cout << "|                                                              |\n| TEMPLATE DEMONSTRATIONS                                      |\n"
         << "| [11] Task Statistics (Template)                              |\n| [12] Generic Container Demo                                  |\n"
         << "| [13] Generic Comparator Demo                                 |\n";
#endif
    cout << "|                                                              |\n| [0] Exit                                                     |\n"
         << "+--------------------------------------------------------------+\nEnter your choice: ";
}

void TaskManager::printSection(const string &title) const { cout << "\n"
                                                                 << COLOR_CYAN << "--- " << title << " ---" << COLOR_RESET << endl; }
void TaskManager::printLine() const { cout << "+--------------------------------------------------------------+" << endl; }
void TaskManager::printSuccess(const string &msg) const { cout << "\n"
                                                               << COLOR_GREEN << "[SUCCESS] " << msg << COLOR_RESET << endl; }
void TaskManager::printWarning(const string &msg) const { cout << "\n"
                                                               << COLOR_YELLOW << "[WARNING] " << msg << COLOR_RESET << endl; }
void TaskManager::printError(const string &msg) const { cout << "\n"
                                                             << COLOR_RED << "[!] " << msg << COLOR_RESET << endl; }
void TaskManager::displayMenu() const { printMenu(); }

// OOP Concept: Abstraction
void TaskManager::run()
{
    int choice;
    printHeader();
    while (true)
    {
        displayMenu();
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printError("Invalid input! Please enter a number.");
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
#ifndef D2_MODE
        case 4:
            chooseSchedulingStrategy();
            break;
#endif
        case 5:
            displayTaskHierarchy();
            break;
        case 6:
            executeAllTasks();
            break;
        case 7:
            printSummaryReport();
            break;
        case 8:
            compareTasksDemo();
            break;
        case 9:
            modifyTaskPriorityDemo();
            break;
        case 10:
            displayTasksWithOperator();
            break;
#ifndef D2_MODE
        case 11:
            statisticsDemo();
            break;
        case 12:
            containerDemo();
            break;
        case 13:
            comparatorDemo();
            break;
#endif
        case 0:
            cout << "\n"
                 << COLOR_CYAN << UI_BORDER << "\n|         Thank you for using HTSE! Goodbye!                |\n"
                 << UI_BORDER << COLOR_RESET << endl;
            return;
        default:
            printError("Invalid choice! Please try again.");
        }
        cout << endl;
    }
}

int TaskManager::getValidatedInt(const string &prompt, int min, int max)
{
    int value;
    cout << prompt;
    while (!(cin >> value) || value < min || value > max)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << COLOR_RED << "[!] Invalid! Enter " << min << "-" << max << ": " << COLOR_RESET;
    }
    return value;
}

bool TaskManager::getTaskIds(int &id1, int &id2, const string &label1, const string &label2)
{
    cout << label1;
    if (!(cin >> id1))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    cout << label2;
    if (!(cin >> id2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return validateTaskId(id1) && validateTaskId(id2);
}

void TaskManager::addNewTask()
{
    string name;
    printSection("Add New Task");
    cout << "Task Name: ";
    getline(cin, name);
    int priority = getValidatedInt("Priority (1-10, 10=highest): ", 1, 10);
    int deadline = getValidatedInt("Deadline (days from now): ", 0, 9999);
    int time = getValidatedInt("Execution Time (units): ", 1, 9999);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Task *new_task = createTask(name, priority, deadline, time);
    printSuccess("Task created!");
    cout << "  ID: " << new_task->getId() << " | Name: \"" << name << "\" | Priority: " << priority << " | Deadline: " << deadline << "d | Time: " << time << "u" << endl;
}

void TaskManager::addSubtaskToTask()
{
    if (all_tasks.empty())
    {
        printError("No tasks available! Create tasks first.");
        return;
    }
    int parent_id, subtask_id;
    printSection("Add Subtask Relationship");
    if (!getTaskIds(parent_id, subtask_id, "Parent Task ID: ", "Child/Subtask ID: "))
    {
        printError("Invalid input!");
        return;
    }
    if (parent_id == subtask_id)
    {
        printError("A task cannot be its own subtask!");
        return;
    }
    addSubtask(parent_id, subtask_id);
    printSuccess("Subtask relationship created!");
    cout << "  Parent Task #" << parent_id << " --> Child Task #" << subtask_id << endl;
}

void TaskManager::setTaskDependency()
{
    if (all_tasks.empty())
    {
        printError("No tasks available! Create tasks first.");
        return;
    }
    int task_id, dependency_id;
    printSection("Set Task Dependency");
    if (!getTaskIds(task_id, dependency_id, "Task ID (will depend on another): ", "Dependency Task ID (must complete first): "))
    {
        printError("Invalid input!");
        return;
    }
    if (task_id == dependency_id)
    {
        printError("A task cannot depend on itself!");
        return;
    }
    addDependency(task_id, dependency_id);
    if (hasCircularDependencies())
        printWarning("This dependency may create a cycle!");
    printSuccess("Dependency added!");
    cout << "  Task #" << task_id << " now depends on Task #" << dependency_id << endl;
}

#ifndef D2_MODE
void TaskManager::chooseSchedulingStrategy()
{
    cout << "\n"
         << COLOR_CYAN << "+--------------------------------------------------------------+\n|              SELECT SCHEDULING STRATEGY                      |\n"
         << "+--------------------------------------------------------------+" << COLOR_RESET << "\n  [1] Priority Based (highest priority first)\n"
         << "  [2] Deadline Based (earliest deadline first)\n  [3] Hierarchical (parent tasks first)\n\nYour choice: ";
    int choice;
    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printError("Invalid input!");
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (choice)
    {
    case 1:
        setScheduler(make_unique<PriorityScheduler>());
        printSuccess("PriorityScheduler activated!");
        break;
    case 2:
        setScheduler(make_unique<DeadlineScheduler>());
        printSuccess("DeadlineScheduler activated!");
        break;
    case 3:
        setScheduler(make_unique<HierarchicalScheduler>());
        printSuccess("HierarchicalScheduler activated!");
        break;
    default:
        printError("Invalid choice! Keeping current scheduler.");
    }
}
#endif

void TaskManager::displayTaskHierarchy() const
{
    if (all_tasks.empty())
    {
        printError("No tasks to display!");
        return;
    }
    cout << "\n"
         << COLOR_CYAN << "+============================================+\n|           TASK HIERARCHY VIEW              |\n"
         << "+============================================+" << COLOR_RESET << "\n\nLegend: [P=Priority, D=Deadline(days)]\n"
         << endl;
    set<int> subtask_ids;
    for (const auto &task_ptr : all_tasks)
        for (const Task *subtask : task_ptr->getSubtasks())
            subtask_ids.insert(subtask->getId());
    for (const auto &task_ptr : all_tasks)
        if (subtask_ids.find(task_ptr->getId()) == subtask_ids.end())
            task_ptr->displayHierarchy(0);
    cout << "\n+============================================+" << endl;
}

void TaskManager::executeAllTasks()
{
    if (all_tasks.empty())
    {
        printError("No tasks to execute!");
        return;
    }
#ifdef D2_MODE
    if (!priority_scheduler)
        priority_scheduler = new PriorityScheduler();
#else
    if (!current_scheduler)
    {
        printWarning("No scheduler selected. Using default PriorityScheduler.");
        current_scheduler = make_unique<PriorityScheduler>();
    }
#endif
    if (hasCircularDependencies())
    {
        cout << "\n"
             << COLOR_RED << "+============================================+\n|               ERROR DETECTED               |\n"
             << "+============================================+" << COLOR_RESET << "\n  Circular dependencies found!\n  Please review and fix task dependencies." << endl;
        return;
    }
    executeAll();
}

void TaskManager::printSummaryReport() const
{
    cout << "\n"
         << COLOR_GREEN << "+============================================+\n|          EXECUTION SUMMARY REPORT          |\n"
         << "+============================================+" << COLOR_RESET << endl;
    int total_root_tasks = 0, total_subtasks = 0, completed = 0;
    set<int> subtask_ids;
    for (const auto &task_ptr : all_tasks)
        for (const Task *subtask : task_ptr->getSubtasks())
            subtask_ids.insert(subtask->getId());
    for (const auto &task_ptr : all_tasks)
    {
        total_subtasks += task_ptr->getTotalSubtasks();
        if (task_ptr->getStatus() == COMPLETED)
            completed++;
        if (subtask_ids.find(task_ptr->getId()) == subtask_ids.end())
            total_root_tasks++;
    }
    int overall_tasks = all_tasks.size();
    cout << "\n  >> Total Root Tasks: " << total_root_tasks << "\n  >> Total Subtasks (nested): " << total_subtasks
         << "\n  >> Overall Tasks Executed: " << overall_tasks << "\n  >> Completed Successfully: " << COLOR_GREEN << completed << COLOR_RESET << " / " << overall_tasks
         << "\n  >> Scheduler Used: " << COLOR_YELLOW << last_scheduler_name << COLOR_RESET << "\n  >> Simulated Execution Time: " << total_simulated_time << " units\n"
         << "\n+============================================+" << endl;
}

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
    Task *parent = findTaskById(parent_id), *subtask = findTaskById(subtask_id);
    if (parent && subtask)
        parent->addSubtask(subtask);
}

void TaskManager::addDependency(int task_id, int dependency_id)
{
    Task *task = findTaskById(task_id), *dependency = findTaskById(dependency_id);
    if (task && dependency)
        task->addDependency(dependency);
}

#ifndef D2_MODE
void TaskManager::setScheduler(unique_ptr<Scheduler> sched) { current_scheduler = move(sched); }
#endif

void TaskManager::executeAll()
{
    vector<Task *> task_ptrs;
    for (const auto &task_ptr : all_tasks)
        task_ptrs.push_back(task_ptr.get());
#ifdef D2_MODE
    vector<Task *> scheduled_tasks = priority_scheduler->schedule(task_ptrs);
    last_scheduler_name = priority_scheduler->getName();
#else
    vector<Task *> scheduled_tasks = current_scheduler->schedule(task_ptrs);
    last_scheduler_name = current_scheduler->getName();
#endif
    executor.resetExecutionTime();
    executor.runTasks(scheduled_tasks, last_scheduler_name);
    total_simulated_time = executor.getTotalExecutionTime();
    completed_tasks = 0;
    for (const auto &task_ptr : all_tasks)
        if (task_ptr->getStatus() == COMPLETED)
            completed_tasks++;
}

Task *TaskManager::findTaskById(int id) const
{
    auto it = task_map.find(id);
    return (it != task_map.end()) ? it->second : nullptr;
}

bool TaskManager::validateTaskId(int id) const { return task_map.find(id) != task_map.end(); }

bool TaskManager::detectCycle(Task *start, set<int> &visited, set<int> &rec_stack) const
{
    if (!start)
        return false;
    int id = start->getId();
    if (rec_stack.find(id) != rec_stack.end())
        return true;
    if (visited.find(id) != visited.end())
        return false;
    visited.insert(id);
    rec_stack.insert(id);
    for (const Task *dep : start->getDependencies())
        if (detectCycle(const_cast<Task *>(dep), visited, rec_stack))
            return true;
    rec_stack.erase(id);
    return false;
}

bool TaskManager::hasCircularDependencies() const
{
    set<int> visited, rec_stack;
    for (const auto &task_ptr : all_tasks)
        if (detectCycle(task_ptr.get(), visited, rec_stack))
            return true;
    return false;
}

// OOP Concept: Operator Overloading Demonstrations
void TaskManager::compareTasksDemo()
{
    if (all_tasks.size() < 2)
    {
        printError("Need at least 2 tasks to compare!");
        return;
    }
    cout << "\n"
         << COLOR_CYAN << "+============================================+\n|    OPERATOR OVERLOADING: TASK COMPARISON   |\n"
         << "+============================================+" << COLOR_RESET << endl;
    int id1, id2;
    cout << "\nEnter first task ID: ";
    if (!(cin >> id1) || !validateTaskId(id1))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printError("Invalid task ID!");
        return;
    }
    cout << "Enter second task ID: ";
    if (!(cin >> id2) || !validateTaskId(id2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printError("Invalid task ID!");
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Task *task1 = findTaskById(id1), *task2 = findTaskById(id2);
    cout << "\n"
         << COLOR_YELLOW << "--- Comparing Tasks ---" << COLOR_RESET << "\nTask 1: " << *task1 << "\nTask 2: " << *task2 << endl;
    cout << "\n"
         << COLOR_GREEN << "--- Comparison Results ---" << COLOR_RESET
         << "\nTask " << id1 << " > Task " << id2 << " ? " << (*task1 > *task2 ? "TRUE" : "FALSE")
         << "\nTask " << id1 << " < Task " << id2 << " ? " << (*task1 < *task2 ? "TRUE" : "FALSE")
         << "\nTask " << id1 << " >= Task " << id2 << " ? " << (*task1 >= *task2 ? "TRUE" : "FALSE")
         << "\nTask " << id1 << " <= Task " << id2 << " ? " << (*task1 <= *task2 ? "TRUE" : "FALSE")
         << "\nTask " << id1 << " == Task " << id2 << " ? " << (*task1 == *task2 ? "TRUE" : "FALSE")
         << "\nTask " << id1 << " != Task " << id2 << " ? " << (*task1 != *task2 ? "TRUE" : "FALSE")
         << "\n\n+============================================+" << endl;
}

void TaskManager::modifyTaskPriorityDemo()
{
    if (all_tasks.empty())
    {
        printError("No tasks available!");
        return;
    }
    cout << "\n"
         << COLOR_CYAN << "+============================================+\n|  OPERATOR OVERLOADING: PRIORITY MODIFICATION|\n"
         << "+============================================+" << COLOR_RESET << endl;
    int id;
    cout << "\nEnter task ID to modify: ";
    if (!(cin >> id) || !validateTaskId(id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printError("Invalid task ID!");
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Task *task = findTaskById(id);
    cout << "\nOriginal Task: " << *task << "\n\n"
         << COLOR_YELLOW << "--- Demonstrating Arithmetic Operators ---" << COLOR_RESET
         << "\n\n[1] Using += operator (increase by 2):";
    *task += 2;
    cout << "\n    Result: " << *task << "\n\n[2] Using -= operator (decrease by 1):";
    *task -= 1;
    cout << "\n    Result: " << *task << "\n\n[3] Using ++ operator (pre-increment):";
    ++(*task);
    cout << "\n    Result: " << *task << "\n\n[4] Using -- operator (pre-decrement):";
    --(*task);
    cout << "\n    Result: " << *task << "\n\n[5] Using + operator (task + 3) - creates new Task:";
    Task newTask = *task + 3;
    cout << "\n    Original: " << *task << "\n    New Task: " << newTask << "\n\n[6] Using - operator (task - 2) - creates new Task:";
    Task anotherTask = *task - 2;
    cout << "\n    Original: " << *task << "\n    New Task: " << anotherTask << endl;
    printSuccess("Priority automatically clamped to [1-10]");
    cout << "+============================================+" << endl;
}

void TaskManager::displayTasksWithOperator()
{
    if (all_tasks.empty())
    {
        printError("No tasks available!");
        return;
    }
    cout << "\n"
         << COLOR_CYAN << "+============================================+\n|  OPERATOR OVERLOADING: STREAM OUTPUT (<<)  |\n"
         << "+============================================+" << COLOR_RESET << "\n\nAll tasks using << operator:\n"
         << endl;
    for (const auto &task_ptr : all_tasks)
        cout << "  " << *task_ptr << endl;
    cout << "\n+============================================+" << endl;
}

#ifndef D2_MODE
// OOP Concept: Templates
void TaskManager::statisticsDemo()
{
    if (all_tasks.empty())
    {
        printError("No tasks available!");
        return;
    }
    cout << "\n"
         << COLOR_CYAN << "+============================================+\n|      TEMPLATE: STATISTICS CALCULATOR       |\n"
         << "+============================================+" << COLOR_RESET << endl;
    vector<int> priorities, deadlines, times;
    for (const auto &task_ptr : all_tasks)
    {
        priorities.push_back(task_ptr->getPriority());
        deadlines.push_back(task_ptr->getDeadline());
        times.push_back(task_ptr->getEstimatedTime());
    }
    cout << "\n"
         << COLOR_YELLOW << "--- Priority Statistics ---" << COLOR_RESET
         << "\n  Total Tasks: " << priorities.size() << "\n  Average Priority: " << Statistics<int>::average(priorities)
         << "\n  Sum of Priorities: " << Statistics<int>::sum(priorities) << "\n  Median Priority: " << Statistics<int>::median(priorities)
         << "\n  Priority Range: " << Statistics<int>::range(priorities) << "\n\n"
         << COLOR_YELLOW << "--- Deadline Statistics ---" << COLOR_RESET
         << "\n  Average Deadline: " << Statistics<int>::average(deadlines) << " days\n  Median Deadline: " << Statistics<int>::median(deadlines)
         << " days\n  Deadline Range: " << Statistics<int>::range(deadlines) << " days\n\n"
         << COLOR_YELLOW << "--- Execution Time Statistics ---" << COLOR_RESET
         << "\n  Total Time: " << Statistics<int>::sum(times) << " units\n  Average Time: " << Statistics<int>::average(times)
         << " units\n  Median Time: " << Statistics<int>::median(times) << " units\n\n+============================================+" << endl;
}

void TaskManager::containerDemo()
{
    cout << "\n"
         << COLOR_CYAN << "+============================================+\n|      TEMPLATE: GENERIC CONTAINER           |\n"
         << "+============================================+" << COLOR_RESET << "\n\n"
         << COLOR_YELLOW << "--- Container<int> Demo ---" << COLOR_RESET << endl;
    Container<int> intContainer;
    intContainer.add(42);
    intContainer.add(17);
    intContainer.add(99);
    intContainer.add(5);
    intContainer.display();
    cout << "\n"
         << COLOR_YELLOW << "--- Container<string> Demo ---" << COLOR_RESET << endl;
    Container<string> strContainer;
    strContainer.add("Alpha");
    strContainer.add("Beta");
    strContainer.add("Gamma");
    strContainer.display();
    cout << "\n"
         << COLOR_YELLOW << "--- Container<Pair<string, int>> Demo ---" << COLOR_RESET << endl;
    Container<Pair<string, int>> pairContainer;
    pairContainer.add(Pair<string, int>("Task Count", all_tasks.size()));
    pairContainer.add(Pair<string, int>("Next ID", next_task_id));
    pairContainer.add(Pair<string, int>("Completed", completed_tasks));
    pairContainer.display();
    cout << "\n+============================================+" << endl;
}

void TaskManager::comparatorDemo()
{
    if (all_tasks.empty())
    {
        printError("No tasks available!");
        return;
    }
    cout << "\n"
         << COLOR_CYAN << "+============================================+\n|      TEMPLATE: GENERIC COMPARATOR          |\n"
         << "+============================================+" << COLOR_RESET << endl;
    vector<Task *> taskPtrs;
    for (const auto &task_ptr : all_tasks)
        taskPtrs.push_back(task_ptr.get());
    cout << "\n"
         << COLOR_YELLOW << "--- Finding Max/Min Priority Tasks ---" << COLOR_RESET << endl;
    Task *maxTask = Comparator<Task *>::findMax(taskPtrs), *minTask = Comparator<Task *>::findMin(taskPtrs);
    cout << "  Highest Priority Task: " << *maxTask << "\n  Lowest Priority Task:  " << *minTask << endl;
    vector<int> priorities;
    for (const auto &task_ptr : all_tasks)
        priorities.push_back(task_ptr->getPriority());
    cout << "\n"
         << COLOR_YELLOW << "--- Sorting Priorities ---" << COLOR_RESET << "\n  Original: ";
    for (int p : priorities)
        cout << p << " ";
    cout << "\n  Ascending: ";
    vector<int> sorted_asc = Comparator<int>::sortAscending(priorities);
    for (int p : sorted_asc)
        cout << p << " ";
    cout << "\n  Descending: ";
    vector<int> sorted_desc = Comparator<int>::sortDescending(priorities);
    for (int p : sorted_desc)
        cout << p << " ";
    cout << "\n\n"
         << COLOR_YELLOW << "--- Priority Threshold Counts ---" << COLOR_RESET << endl;
    int threshold = 5;
    int high = Comparator<int>::countGreaterThan(priorities, threshold), low = Comparator<int>::countLessThan(priorities, threshold);
    cout << "  Tasks with priority > " << threshold << ": " << high << "\n  Tasks with priority < " << threshold << ": " << low
         << "\n\n+============================================+" << endl;
}
#endif
