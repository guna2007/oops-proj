# HTSE Technical Documentation & Features Guide

> **Hierarchical Task Scheduling Engine - Complete Technical Reference**  
> A comprehensive OOP-based task management and scheduling system in C++

---

## Table of Contents

1. [Project Overview](#project-overview)
2. [OOP Concepts Implementation](#oop-concepts-implementation)
3. [Architecture & Design](#architecture--design)
4. [File-by-File Documentation](#file-by-file-documentation)
5. [Features Implementation](#features-implementation)
6. [Class Relationships](#class-relationships)
7. [Function Reference](#function-reference)
8. [UI/UX Features](#uiux-features)
9. [Execution Flow](#execution-flow)
10. [Technical Specifications](#technical-specifications)

---

## Project Overview

### Purpose

The Hierarchical Task Scheduling Engine (HTSE) is an educational C++ project demonstrating core Object-Oriented Programming principles through a practical task scheduling and execution simulation system.

### Key Capabilities

- ✅ Create and manage tasks with priorities, deadlines, and execution times
- ✅ Build hierarchical task structures (parent-child relationships)
- ✅ Define task dependencies (prerequisite requirements)
- ✅ Multiple scheduling algorithms (Priority, Deadline, Hierarchical)
- ✅ Real-time execution simulation with progress visualization
- ✅ Circular dependency detection
- ✅ Professional CLI interface with ANSI color support

---

## OOP Concepts Implementation

### 1. **Encapsulation**

**Definition**: Bundling data and methods that operate on that data within a single unit (class), hiding internal implementation details.

**Implementation Locations**:

| File                  | Class          | Implementation Details                                                                                                                                |
| --------------------- | -------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------- |
| `task.h/cpp`          | `Task`         | Private members: `id`, `name`, `priority`, `deadline`, `status`, `estimated_time`, `subtasks`, `dependencies`. Public getters/setters control access. |
| `task_manager.h/cpp`  | `TaskManager`  | Private members: `all_tasks`, `task_map`, `current_scheduler`, `executor`, `next_task_id`. All management logic is encapsulated.                      |
| `task_executor.h/cpp` | `TaskExecutor` | Private helper methods: `executeTaskWithSubtasks()`, `printTaskExecution()`, `showProgressAnimation()` hidden from caller.                            |

**Code Examples**:

```cpp
// task.h - Encapsulated Task class
class Task {
private:
    int id;                        // Hidden from external access
    string name;
    TaskStatus status;
    vector<Task*> subtasks;        // Composition relationship

public:
    int getId() const;             // Controlled read access
    void execute();                // Public interface
};
```

---

### 2. **Inheritance**

**Definition**: Mechanism where a derived class inherits properties and behavior from a base class.

**Implementation Locations**:

| Base Class  | Derived Classes         | File Location                                 | Purpose                             |
| ----------- | ----------------------- | --------------------------------------------- | ----------------------------------- |
| `Scheduler` | `PriorityScheduler`     | `scheduler.h`, `priority_scheduler.h/cpp`     | Priority-based scheduling algorithm |
| `Scheduler` | `DeadlineScheduler`     | `scheduler.h`, `deadline_scheduler.h/cpp`     | Deadline-based scheduling algorithm |
| `Scheduler` | `HierarchicalScheduler` | `scheduler.h`, `hierarchical_scheduler.h/cpp` | Hierarchical scheduling algorithm   |

**Code Examples**:

```cpp
// scheduler.h - Abstract base class
class Scheduler {
public:
    virtual vector<Task*> schedule(vector<Task*>& tasks) = 0;
    virtual string getName() const = 0;
    virtual ~Scheduler() = default;
};

// priority_scheduler.h - Derived class
class PriorityScheduler : public Scheduler {
public:
    vector<Task*> schedule(vector<Task*>& tasks) override;
    string getName() const override;
};
```

---

### 3. **Polymorphism**

**Definition**: Ability to treat objects of different types through a common interface, with behavior determined at runtime.

**Implementation Locations**:

| Location                              | Type                 | Implementation                                                         |
| ------------------------------------- | -------------------- | ---------------------------------------------------------------------- |
| `task_manager.cpp` - `setScheduler()` | Runtime Polymorphism | Accepts any `Scheduler*` type via base class pointer                   |
| `task_manager.cpp` - `executeAll()`   | Runtime Polymorphism | `current_scheduler->schedule()` calls appropriate derived class method |
| All scheduler classes                 | Virtual Functions    | `schedule()` and `getName()` are virtual/override                      |

**Code Examples**:

```cpp
// task_manager.cpp - Polymorphic usage
void TaskManager::setScheduler(unique_ptr<Scheduler> sched) {
    current_scheduler = move(sched);  // Can hold any Scheduler subclass
}

void TaskManager::executeAll() {
    // Polymorphic call - actual method depends on runtime type
    vector<Task*> scheduled_tasks = current_scheduler->schedule(task_ptrs);
}
```

---

### 4. **Abstraction**

**Definition**: Hiding complex implementation details and exposing only essential features through simple interfaces.

**Implementation Locations**:

| File                | Class/Function               | Abstraction Level                                     |
| ------------------- | ---------------------------- | ----------------------------------------------------- |
| `scheduler.h`       | `Scheduler` (abstract class) | Pure virtual functions define interface contract      |
| `task_manager.cpp`  | `run()`                      | High-level menu system hides complex CLI logic        |
| `task_executor.cpp` | `runTasks()`                 | Complex execution logic abstracted into single method |
| `task.cpp`          | `execute()`                  | Execution simulation details hidden from caller       |

**Code Examples**:

```cpp
// scheduler.h - Abstract interface
class Scheduler {
public:
    virtual vector<Task*> schedule(vector<Task*>& tasks) = 0;  // Pure virtual
    virtual string getName() const = 0;                        // Pure virtual
};

// task_manager.cpp - High-level abstraction
void TaskManager::run() {
    // Complex menu system abstracted into simple loop
    while (true) {
        displayMenu();
        // Handle user choices...
    }
}
```

---

### 5. **Composition**

**Definition**: "Has-a" relationship where one class contains objects of other classes.

**Implementation Locations**:

| Container Class | Contained Class              | File                  | Relationship Type              |
| --------------- | ---------------------------- | --------------------- | ------------------------------ |
| `Task`          | `vector<Task*>` subtasks     | `task.h/cpp`          | Parent task **has** subtasks   |
| `Task`          | `vector<Task*>` dependencies | `task.h/cpp`          | Task **has** dependencies      |
| `TaskManager`   | `vector<unique_ptr<Task>>`   | `task_manager.h/cpp`  | Manager **owns** tasks         |
| `TaskManager`   | `unique_ptr<Scheduler>`      | `task_manager.h/cpp`  | Manager **has** a scheduler    |
| `TaskManager`   | `TaskExecutor`               | `task_manager.h/cpp`  | Manager **has** an executor    |
| `TaskExecutor`  | `ostream&`                   | `task_executor.h/cpp` | Executor **has** output stream |

**Code Examples**:

```cpp
// task.h - Composition relationships
class Task {
private:
    vector<Task*> subtasks;        // HAS-A relationship (aggregation)
    vector<Task*> dependencies;    // HAS-A relationship (aggregation)
};

// task_manager.h - Composition and ownership
class TaskManager {
private:
    vector<unique_ptr<Task>> all_tasks;     // OWNS tasks
    unique_ptr<Scheduler> current_scheduler; // HAS-A scheduler
    TaskExecutor executor;                   // HAS-A executor
};
```

---

### 6. **Recursion**

**Definition**: Function calling itself to solve problems with hierarchical or nested structures.

**Implementation Locations**:

| File                         | Function                    | Purpose                                       |
| ---------------------------- | --------------------------- | --------------------------------------------- |
| `task.cpp`                   | `displayHierarchy()`        | Recursively display task and all subtasks     |
| `task.cpp`                   | `getTotalSubtasks()`        | Recursively count all nested subtasks         |
| `task_executor.cpp`          | `executeTaskWithSubtasks()` | Recursively execute task hierarchy            |
| `hierarchical_scheduler.cpp` | `collectTasksInOrder()`     | Recursively traverse task tree                |
| `task_manager.cpp`           | `detectCycle()`             | DFS-based cycle detection in dependency graph |

**Code Examples**:

```cpp
// task.cpp - Recursive hierarchy display
void Task::displayHierarchy(int indent) const {
    displayInfo(indent);  // Display this task

    // Recursively display all subtasks
    for (const Task* subtask : subtasks) {
        subtask->displayHierarchy(indent + 1);  // RECURSION
    }
}

// task_executor.cpp - Recursive execution
void TaskExecutor::executeTaskWithSubtasks(Task* task, int indent) {
    printTaskExecution(task, indent, "RUNNING");

    // Execute subtasks first (depth-first)
    for (Task* subtask : task->getSubtasks()) {
        executeTaskWithSubtasks(subtask, indent + 1);  // RECURSION
    }

    // Then execute this task
    task->execute();
}
```

---

## Architecture & Design

### System Architecture

```
┌─────────────────────────────────────────────────────────┐
│                    Main Entry Point                      │
│                      (main.cpp)                          │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│                   TaskManager                            │
│  • Manages all tasks and relationships                   │
│  • Handles user interaction (CLI)                        │
│  • Coordinates scheduling and execution                  │
└────┬───────────────┬──────────────┬─────────────────────┘
     │               │              │
     ▼               ▼              ▼
┌─────────┐   ┌──────────┐   ┌──────────────┐
│  Task   │   │Scheduler │   │TaskExecutor  │
│ Objects │   │(Polymor) │   │              │
└─────────┘   └──────────┘   └──────────────┘
     │               │              │
     │               ├──────────────┼──────────────┐
     │               ▼              ▼              ▼
     │        ┌─────────────────────────────────────┐
     │        │  Priority  │ Deadline │Hierarchical│
     │        │ Scheduler  │Scheduler │ Scheduler  │
     │        └─────────────────────────────────────┘
     │
     └──> Subtasks & Dependencies (Composition)
```

### Design Patterns Used

| Pattern               | Location                  | Purpose                               |
| --------------------- | ------------------------- | ------------------------------------- |
| **Strategy Pattern**  | Scheduler classes         | Interchangeable scheduling algorithms |
| **Factory Pattern**   | TaskManager::createTask() | Centralized task creation             |
| **Composite Pattern** | Task with subtasks        | Tree structure of tasks               |
| **Singleton-like**    | TaskManager               | Single manager coordinates everything |

---

## File-by-File Documentation

### Core Classes

#### 1. **task.h / task.cpp**

**Purpose**: Defines the Task entity with all its properties and behaviors.

**Class**: `Task`

**Enumerations**:

```cpp
enum TaskStatus {
    PENDING,
    RUNNING,
    COMPLETED
};
```

**Private Members**:
| Type | Name | Purpose |
|------|------|---------|
| `int` | `id` | Unique task identifier |
| `string` | `name` | Task name/description |
| `int` | `priority` | Priority level (1-10) |
| `int` | `deadline` | Deadline in days |
| `TaskStatus` | `status` | Current execution status |
| `int` | `estimated_time` | Estimated execution time in units |
| `vector<Task*>` | `subtasks` | Child tasks (composition) |
| `vector<Task*>` | `dependencies` | Tasks that must complete first |

**Public Methods**:

| Return Type            | Method               | Parameters                           | Description                   | OOP Concept         |
| ---------------------- | -------------------- | ------------------------------------ | ----------------------------- | ------------------- |
| -                      | `Task()`             | `id, name, priority, deadline, time` | Constructor                   | Encapsulation       |
| -                      | `~Task()`            | -                                    | Destructor                    | Resource Management |
| `int`                  | `getId()`            | -                                    | Get task ID                   | Encapsulation       |
| `string`               | `getName()`          | -                                    | Get task name                 | Encapsulation       |
| `int`                  | `getPriority()`      | -                                    | Get priority                  | Encapsulation       |
| `int`                  | `getDeadline()`      | -                                    | Get deadline                  | Encapsulation       |
| `TaskStatus`           | `getStatus()`        | -                                    | Get current status            | Encapsulation       |
| `int`                  | `getEstimatedTime()` | -                                    | Get estimated time            | Encapsulation       |
| `const vector<Task*>&` | `getSubtasks()`      | -                                    | Get subtask list              | Encapsulation       |
| `const vector<Task*>&` | `getDependencies()`  | -                                    | Get dependency list           | Encapsulation       |
| `void`                 | `addSubtask()`       | `Task* t`                            | Add child task                | Composition         |
| `void`                 | `addDependency()`    | `Task* t`                            | Add dependency                | Composition         |
| `bool`                 | `isReady()`          | -                                    | Check if all dependencies met | Business Logic      |
| `void`                 | `execute()`          | -                                    | Simulate task execution       | Abstraction         |
| `void`                 | `markComplete()`     | -                                    | Mark as completed             | State Management    |
| `void`                 | `displayInfo()`      | `int indent`                         | Display task details          | Abstraction         |
| `void`                 | `displayHierarchy()` | `int indent`                         | Display task tree             | Recursion           |
| `int`                  | `getTotalSubtasks()` | -                                    | Count all nested subtasks     | Recursion           |

**Key Implementation Details**:

```cpp
// Composition - Managing child tasks
void Task::addSubtask(Task* t) {
    if (t != nullptr) {
        subtasks.push_back(t);
    }
}

// Recursion - Hierarchical display
void Task::displayHierarchy(int indent) const {
    displayInfo(indent);
    for (const Task* subtask : subtasks) {
        subtask->displayHierarchy(indent + 1);  // Recursive call
    }
}

// Color-coded status display
void Task::displayInfo(int indent) const {
    string statusColor;
    switch (status) {
        case PENDING:  statusColor = "\033[1;33m"; break;  // Yellow
        case RUNNING:  statusColor = "\033[1;34m"; break;  // Blue
        case COMPLETED: statusColor = "\033[1;32m"; break; // Green
    }
    // Tree-style output with colors
}
```

---

#### 2. **scheduler.h**

**Purpose**: Abstract base class defining the scheduler interface.

**Class**: `Scheduler` (Abstract)

**Public Methods**:

| Return Type     | Method         | Parameters             | Description        | Type         |
| --------------- | -------------- | ---------------------- | ------------------ | ------------ |
| `vector<Task*>` | `schedule()`   | `vector<Task*>& tasks` | Schedule tasks     | Pure Virtual |
| `string`        | `getName()`    | -                      | Get scheduler name | Pure Virtual |
| -               | `~Scheduler()` | -                      | Virtual destructor | Virtual      |

**OOP Concepts**:

- **Abstraction**: Defines contract without implementation
- **Polymorphism**: Enables runtime scheduling algorithm selection
- **Interface Pattern**: Pure virtual functions

```cpp
class Scheduler {
public:
    virtual vector<Task*> schedule(vector<Task*>& tasks) = 0;
    virtual string getName() const = 0;
    virtual ~Scheduler() = default;
};
```

---

#### 3. **priority_scheduler.h / priority_scheduler.cpp**

**Purpose**: Implements priority-based scheduling (highest priority first).

**Class**: `PriorityScheduler` (inherits from `Scheduler`)

**Public Methods**:

| Return Type     | Method       | Parameters             | Description                   | Override |
| --------------- | ------------ | ---------------------- | ----------------------------- | -------- |
| `vector<Task*>` | `schedule()` | `vector<Task*>& tasks` | Sort by priority (descending) | ✓        |
| `string`        | `getName()`  | -                      | Returns "PriorityScheduler"   | ✓        |

**Algorithm**:

```cpp
vector<Task*> PriorityScheduler::schedule(vector<Task*>& tasks) {
    vector<Task*> result = tasks;

    // Sort by priority (highest first)
    sort(result.begin(), result.end(),
         [](Task* a, Task* b) {
             return a->getPriority() > b->getPriority();
         });

    return result;
}
```

**OOP Concepts**: Inheritance, Polymorphism, Lambda Functions

---

#### 4. **deadline_scheduler.h / deadline_scheduler.cpp**

**Purpose**: Implements deadline-based scheduling (earliest deadline first).

**Class**: `DeadlineScheduler` (inherits from `Scheduler`)

**Public Methods**:

| Return Type     | Method       | Parameters             | Description                  | Override |
| --------------- | ------------ | ---------------------- | ---------------------------- | -------- |
| `vector<Task*>` | `schedule()` | `vector<Task*>& tasks` | Sort by deadline (ascending) | ✓        |
| `string`        | `getName()`  | -                      | Returns "DeadlineScheduler"  | ✓        |

**Algorithm**:

```cpp
vector<Task*> DeadlineScheduler::schedule(vector<Task*>& tasks) {
    vector<Task*> result = tasks;

    // Sort by deadline (earliest first)
    sort(result.begin(), result.end(),
         [](Task* a, Task* b) {
             return a->getDeadline() < b->getDeadline();
         });

    return result;
}
```

**OOP Concepts**: Inheritance, Polymorphism

---

#### 5. **hierarchical_scheduler.h / hierarchical_scheduler.cpp**

**Purpose**: Implements hierarchical scheduling (parent tasks before children).

**Class**: `HierarchicalScheduler` (inherits from `Scheduler`)

**Private Members**:

```cpp
set<int> visited_ids;  // Track visited tasks to avoid duplicates
```

**Public Methods**:

| Return Type     | Method       | Parameters             | Description                     | Override |
| --------------- | ------------ | ---------------------- | ------------------------------- | -------- |
| `vector<Task*>` | `schedule()` | `vector<Task*>& tasks` | Schedule in hierarchical order  | ✓        |
| `string`        | `getName()`  | -                      | Returns "HierarchicalScheduler" | ✓        |

**Private Methods**:

| Return Type | Method                  | Parameters                          | Description              |
| ----------- | ----------------------- | ----------------------------------- | ------------------------ |
| `void`      | `collectTasksInOrder()` | `Task* task, vector<Task*>& result` | Recursive tree traversal |

**Algorithm**:

```cpp
void HierarchicalScheduler::collectTasksInOrder(Task* task, vector<Task*>& result) {
    if (!task || visited_ids.count(task->getId())) return;

    visited_ids.insert(task->getId());
    result.push_back(task);  // Add parent first

    // Then recursively add all subtasks
    for (Task* subtask : task->getSubtasks()) {
        collectTasksInOrder(subtask, result);  // RECURSION
    }
}
```

**OOP Concepts**: Inheritance, Polymorphism, Recursion

---

#### 6. **task_executor.h / task_executor.cpp**

**Purpose**: Handles task execution with dependency resolution and progress visualization.

**Class**: `TaskExecutor`

**Private Members**:
| Type | Name | Purpose |
|------|------|---------|
| `ostream&` | `output` | Output stream reference (composition) |
| `int` | `total_execution_time` | Accumulated execution time |

**Private Methods**:

| Return Type | Method                      | Parameters                              | Description                 | OOP Concept   |
| ----------- | --------------------------- | --------------------------------------- | --------------------------- | ------------- |
| `void`      | `executeTaskWithSubtasks()` | `Task* task, int indent`                | Recursive task execution    | Recursion     |
| `void`      | `printTaskExecution()`      | `Task* task, int indent, string action` | Print formatted task status | Encapsulation |
| `void`      | `showProgressAnimation()`   | `Task* task, int indent`                | Display progress bar        | Abstraction   |

**Public Methods**:

| Return Type | Method                    | Parameters                                    | Description                     |
| ----------- | ------------------------- | --------------------------------------------- | ------------------------------- |
| -           | `TaskExecutor()`          | `ostream& out = cout`                         | Constructor with default output |
| `void`      | `runTasks()`              | `vector<Task*>& tasks, string scheduler_name` | Execute task list               |
| `int`       | `getTotalExecutionTime()` | -                                             | Get total execution time        |
| `void`      | `resetExecutionTime()`    | -                                             | Reset execution time counter    |

**Key Features**:

1. **Multi-pass Dependency Resolution**:

```cpp
void TaskExecutor::runTasks(...) {
    const int MAX_PASSES = 10;

    for (int pass = 0; pass < MAX_PASSES && !remaining_tasks.empty(); ++pass) {
        for (Task* task : remaining_tasks) {
            if (task->isReady()) {
                executeTaskWithSubtasks(task, 0);
            } else {
                deferred_tasks.push_back(task);  // Try again next pass
            }
        }
    }
}
```

2. **Progress Animation**:

```cpp
void TaskExecutor::showProgressAnimation(Task* task, int indent) {
    int steps = min(task->getEstimatedTime(), 10);
    int delayPerStep = (task->getEstimatedTime() * 1000) / steps;

    output << "Progress: [";
    for (int i = 0; i < steps; i++) {
        output << "=" << flush;
        Sleep(delayPerStep);  // Animated progress
    }
    output << "] 100%" << endl;
}
```

**OOP Concepts**: Composition, Recursion, Encapsulation

---

#### 7. **task_manager.h / task_manager.cpp**

**Purpose**: Central coordinator managing all tasks, user interaction, and system components.

**Class**: `TaskManager`

**Private Members**:

| Type                       | Name                   | Purpose                     |
| -------------------------- | ---------------------- | --------------------------- |
| `vector<unique_ptr<Task>>` | `all_tasks`            | Owns all task objects       |
| `map<int, Task*>`          | `task_map`             | Quick task lookup by ID     |
| `unique_ptr<Scheduler>`    | `current_scheduler`    | Current scheduling strategy |
| `TaskExecutor`             | `executor`             | Task execution engine       |
| `int`                      | `next_task_id`         | Next available task ID      |
| `int`                      | `completed_tasks`      | Count of completed tasks    |
| `int`                      | `total_simulated_time` | Total execution time        |
| `string`                   | `last_scheduler_name`  | Last used scheduler name    |

**Private Helper Methods**:

| Return Type | Method                       | Purpose                          |
| ----------- | ---------------------------- | -------------------------------- |
| `void`      | `displayMenu()`              | Show main menu                   |
| `void`      | `addNewTask()`               | Add task workflow                |
| `void`      | `addSubtaskToTask()`         | Create parent-child relationship |
| `void`      | `setTaskDependency()`        | Set task dependencies            |
| `void`      | `chooseSchedulingStrategy()` | Select scheduler                 |
| `void`      | `displayTaskHierarchy()`     | Show task tree                   |
| `void`      | `executeAllTasks()`          | Execute all tasks                |
| `void`      | `printSummaryReport()`       | Show execution summary           |
| `Task*`     | `findTaskById()`             | Find task by ID                  |
| `bool`      | `validateTaskId()`           | Validate task ID exists          |
| `bool`      | `detectCycle()`              | DFS cycle detection              |
| `bool`      | `hasCircularDependencies()`  | Check for cycles                 |

**Public Methods**:

| Return Type | Method            | Parameters                       | Description              |
| ----------- | ----------------- | -------------------------------- | ------------------------ |
| -           | `TaskManager()`   | -                                | Constructor              |
| `void`      | `run()`           | -                                | Main CLI loop            |
| `Task*`     | `createTask()`    | `name, priority, deadline, time` | Factory method           |
| `void`      | `addSubtask()`    | `parent_id, subtask_id`          | Add subtask relationship |
| `void`      | `addDependency()` | `task_id, dependency_id`         | Add dependency           |
| `void`      | `setScheduler()`  | `unique_ptr<Scheduler>`          | Set scheduling strategy  |
| `void`      | `executeAll()`    | -                                | Execute all tasks        |

**Key Features**:

1. **Circular Dependency Detection** (Graph Algorithm):

```cpp
bool TaskManager::detectCycle(Task* start, set<int>& visited, set<int>& rec_stack) const {
    int id = start->getId();

    if (rec_stack.count(id)) return true;  // Cycle found!
    if (visited.count(id)) return false;   // Already processed

    visited.insert(id);
    rec_stack.insert(id);

    // Check dependencies recursively
    for (const Task* dep : start->getDependencies()) {
        if (detectCycle(const_cast<Task*>(dep), visited, rec_stack)) {
            return true;
        }
    }

    rec_stack.erase(id);
    return false;
}
```

2. **Polymorphic Scheduler Management**:

```cpp
void TaskManager::setScheduler(unique_ptr<Scheduler> sched) {
    current_scheduler = move(sched);  // Polymorphic assignment
}

void TaskManager::executeAll() {
    // Polymorphic call
    vector<Task*> scheduled = current_scheduler->schedule(task_ptrs);
}
```

**OOP Concepts**: Encapsulation, Composition, Polymorphism, Recursion, Factory Pattern

---

#### 8. **main.cpp**

**Purpose**: Application entry point.

**Code**:

```cpp
int main() {
    TaskManager manager;  // Create manager
    manager.run();        // Start application
    return 0;
}
```

**OOP Concepts**: Encapsulation, Abstraction (high-level interface)

---

## Features Implementation

### Feature 1: Task Creation

**Files**: `task_manager.cpp`, `task.cpp`  
**Functions**: `TaskManager::addNewTask()`, `TaskManager::createTask()`, `Task::Task()`

**Implementation**:

```cpp
void TaskManager::addNewTask() {
    string name;
    int priority, deadline, time;

    // Input with validation
    cout << "Task Name: ";
    getline(cin, name);

    // Priority validation (1-10)
    while (!(cin >> priority) || priority < 1 || priority > 10) {
        cout << "[!] Invalid! Enter 1-10: ";
    }

    Task* new_task = createTask(name, priority, deadline, time);
    cout << "[SUCCESS] Task created!" << endl;
}

Task* TaskManager::createTask(const string& name, int priority, int deadline, int time) {
    auto task = make_unique<Task>(next_task_id, name, priority, deadline, time);
    Task* task_ptr = task.get();
    task_map[next_task_id] = task_ptr;
    all_tasks.push_back(move(task));
    next_task_id++;
    return task_ptr;
}
```

**OOP Concepts**: Encapsulation, Factory Pattern, RAII (unique_ptr)

---

### Feature 2: Hierarchical Task Structure

**Files**: `task_manager.cpp`, `task.cpp`  
**Functions**: `TaskManager::addSubtask()`, `Task::addSubtask()`

**Implementation**:

```cpp
void TaskManager::addSubtask(int parent_id, int subtask_id) {
    Task* parent = findTaskById(parent_id);
    Task* subtask = findTaskById(subtask_id);

    if (parent && subtask) {
        parent->addSubtask(subtask);  // Composition
    }
}

void Task::addSubtask(Task* t) {
    if (t != nullptr) {
        subtasks.push_back(t);  // Vector of child tasks
    }
}
```

**OOP Concepts**: Composition, Encapsulation

---

### Feature 3: Task Dependencies

**Files**: `task_manager.cpp`, `task.cpp`  
**Functions**: `TaskManager::setTaskDependency()`, `Task::addDependency()`, `Task::isReady()`

**Implementation**:

```cpp
void Task::addDependency(Task* t) {
    if (t != nullptr) {
        dependencies.push_back(t);
    }
}

bool Task::isReady() const {
    for (const Task* dep : dependencies) {
        if (dep->getStatus() != COMPLETED) {
            return false;  // Not ready if any dependency incomplete
        }
    }
    return true;
}
```

**OOP Concepts**: Composition, Encapsulation, Business Logic

---

### Feature 4: Multiple Scheduling Strategies

**Files**: All scheduler files  
**Functions**: `schedule()` in each scheduler class

**Implementation**:

```cpp
// Priority-based
vector<Task*> PriorityScheduler::schedule(vector<Task*>& tasks) {
    sort(tasks.begin(), tasks.end(),
         [](Task* a, Task* b) { return a->getPriority() > b->getPriority(); });
    return tasks;
}

// Deadline-based
vector<Task*> DeadlineScheduler::schedule(vector<Task*>& tasks) {
    sort(tasks.begin(), tasks.end(),
         [](Task* a, Task* b) { return a->getDeadline() < b->getDeadline(); });
    return tasks;
}

// Hierarchical (recursive)
void HierarchicalScheduler::collectTasksInOrder(Task* task, vector<Task*>& result) {
    result.push_back(task);
    for (Task* subtask : task->getSubtasks()) {
        collectTasksInOrder(subtask, result);  // Depth-first
    }
}
```

**OOP Concepts**: Inheritance, Polymorphism, Strategy Pattern, Recursion

---

### Feature 5: Task Execution with Progress Animation

**Files**: `task_executor.cpp`, `task.cpp`  
**Functions**: `TaskExecutor::runTasks()`, `TaskExecutor::showProgressAnimation()`

**Implementation**:

```cpp
void TaskExecutor::showProgressAnimation(Task* task, int indent) {
    int steps = min(task->getEstimatedTime(), 10);
    int delayPerStep = (task->getEstimatedTime() * 1000) / steps;

    output << "Progress: [";
    for (int i = 0; i < steps; i++) {
        output << "=" << flush;
        Sleep(delayPerStep);  // Real-time animation
    }
    output << "] 100%" << endl;
}
```

**OOP Concepts**: Encapsulation, Abstraction

---

### Feature 6: Circular Dependency Detection

**Files**: `task_manager.cpp`  
**Functions**: `TaskManager::detectCycle()`, `TaskManager::hasCircularDependencies()`

**Algorithm**: Depth-First Search (DFS) with recursion stack

**Implementation**:

```cpp
bool TaskManager::detectCycle(Task* start, set<int>& visited, set<int>& rec_stack) const {
    int id = start->getId();

    // Cycle detected if in recursion stack
    if (rec_stack.count(id)) return true;

    // Already fully explored
    if (visited.count(id)) return false;

    visited.insert(id);
    rec_stack.insert(id);

    // Explore dependencies
    for (const Task* dep : start->getDependencies()) {
        if (detectCycle(const_cast<Task*>(dep), visited, rec_stack)) {
            return true;
        }
    }

    rec_stack.erase(id);  // Backtrack
    return false;
}
```

**OOP Concepts**: Recursion, Graph Algorithms

---

### Feature 7: Task Hierarchy Visualization

**Files**: `task.cpp`, `task_manager.cpp`  
**Functions**: `Task::displayHierarchy()`, `Task::displayInfo()`

**Implementation**:

```cpp
void Task::displayInfo(int indent) const {
    string prefix = (indent == 0) ? "[*] " : (indent == 1) ? " |-- " : " |   +-- ";
    string statusColor;

    switch (status) {
        case PENDING:   statusColor = "\033[1;33m"; break;  // Yellow
        case RUNNING:   statusColor = "\033[1;34m"; break;  // Blue
        case COMPLETED: statusColor = "\033[1;32m"; break;  // Green
    }

    cout << string(indent * 3, ' ') << prefix << "Task " << id << ": " << name
         << " [P=" << priority << ", D=" << deadline << "d, "
         << statusColor << statusStr << "\033[0m" << "]" << endl;
}

void Task::displayHierarchy(int indent) const {
    displayInfo(indent);
    for (const Task* subtask : subtasks) {
        subtask->displayHierarchy(indent + 1);  // Recursive
    }
}
```

**OOP Concepts**: Recursion, Abstraction, Encapsulation

---

## Class Relationships

### Inheritance Hierarchy

```
        Scheduler (Abstract)
             |
    +--------+--------+
    |        |        |
Priority  Deadline  Hierarchical
Scheduler Scheduler  Scheduler
```

### Composition Relationships

```
TaskManager
  |-- owns --> vector<unique_ptr<Task>>
  |-- has  --> unique_ptr<Scheduler>
  |-- has  --> TaskExecutor
  |-- has  --> map<int, Task*>

Task
  |-- has  --> vector<Task*> subtasks
  |-- has  --> vector<Task*> dependencies

TaskExecutor
  |-- has  --> ostream& output
```

### Association Diagram

```
     User
       |
       | interacts with
       v
  TaskManager  <-----> TaskExecutor
       |                    |
       | owns               | executes
       v                    v
     Task  <-----------> Scheduler
       |                    |
       | has                | implements
       v                    v
  Subtasks/Deps    [Priority|Deadline|Hierarchical]
```

---

## Function Reference

### Critical Functions by Purpose

#### Task Management

| Function           | File                       | Purpose                          |
| ------------------ | -------------------------- | -------------------------------- |
| `createTask()`     | task_manager.cpp           | Factory method for task creation |
| `addSubtask()`     | task_manager.cpp, task.cpp | Create parent-child relationship |
| `addDependency()`  | task_manager.cpp, task.cpp | Add task dependency              |
| `validateTaskId()` | task_manager.cpp           | Validate task exists             |
| `findTaskById()`   | task_manager.cpp           | Lookup task by ID                |

#### Scheduling

| Function         | File                | Purpose                    |
| ---------------- | ------------------- | -------------------------- |
| `schedule()`     | All scheduler files | Sort/order tasks           |
| `setScheduler()` | task_manager.cpp    | Change scheduling strategy |
| `getName()`      | All scheduler files | Get scheduler name         |

#### Execution

| Function                    | File              | Purpose                 |
| --------------------------- | ----------------- | ----------------------- |
| `runTasks()`                | task_executor.cpp | Execute task list       |
| `executeTaskWithSubtasks()` | task_executor.cpp | Recursive execution     |
| `execute()`                 | task.cpp          | Simulate task execution |
| `isReady()`                 | task.cpp          | Check dependencies      |
| `showProgressAnimation()`   | task_executor.cpp | Display progress        |

#### Visualization

| Function               | File              | Purpose                |
| ---------------------- | ----------------- | ---------------------- |
| `displayHierarchy()`   | task.cpp          | Show task tree         |
| `displayInfo()`        | task.cpp          | Show single task       |
| `printTaskExecution()` | task_executor.cpp | Print execution status |
| `printSummaryReport()` | task_manager.cpp  | Show statistics        |

#### Validation

| Function                    | File             | Purpose             |
| --------------------------- | ---------------- | ------------------- |
| `detectCycle()`             | task_manager.cpp | DFS cycle detection |
| `hasCircularDependencies()` | task_manager.cpp | Check for cycles    |
| `validateTaskId()`          | task_manager.cpp | ID validation       |

---

## UI/UX Features

### Visual Elements

#### 1. **Color Scheme**

| Color          | ANSI Code    | Usage                                 |
| -------------- | ------------ | ------------------------------------- |
| Cyan           | `\033[1;36m` | Headers, borders                      |
| Yellow         | `\033[1;33m` | Menu titles, warnings, PENDING status |
| Green          | `\033[1;32m` | Success messages, COMPLETED status    |
| Red            | `\033[1;31m` | Error messages                        |
| Blue           | `\033[1;34m` | RUNNING status                        |
| Purple/Magenta | `\033[1;35m` | Execution headers                     |
| White          | `\033[1;37m` | Input prompts                         |
| Reset          | `\033[0m`    | Reset to default                      |

#### 2. **Box Borders**

```
Main Header:
+============================================================+
|     HIERARCHICAL TASK SCHEDULING ENGINE (HTSE)            |
|                    [OOP Project Demo]                     |
+============================================================+

Menu:
+-----------------------------------------------+
| [1] >> Add New Task                          |
+-----------------------------------------------+

Section Headers:
--- Add New Task ---

Execution:
+============================================+
|        TASK EXECUTION IN PROGRESS         |
+============================================+
```

#### 3. **Tree Symbols**

```
[*]        - Root task
 |--       - First-level child
 |   +--   - Nested child
```

#### 4. **Status Indicators**

```
[SUCCESS]  - Green success message
[!]        - Yellow warning or red error
[~]        - Blue running indicator
[+]        - Green completion indicator
```

#### 5. **Progress Bar**

```
Progress: [=======] 100%
```

### Menu System

**Main Menu Options**:

1. Add New Task
2. Add Subtask to Existing Task
3. Set Task Dependency
4. Choose Scheduling Strategy
5. Display Task Hierarchy
6. Execute All Tasks
7. View Execution Report
8. Exit

---

## Execution Flow

### Main Program Flow

```
main()
  └─> TaskManager::TaskManager()
        └─> Initialize default PriorityScheduler
  └─> TaskManager::run()
        └─> Loop:
              ├─> displayMenu()
              ├─> Get user choice
              └─> Switch:
                    ├─> Case 1: addNewTask()
                    ├─> Case 2: addSubtaskToTask()
                    ├─> Case 3: setTaskDependency()
                    ├─> Case 4: chooseSchedulingStrategy()
                    ├─> Case 5: displayTaskHierarchy()
                    ├─> Case 6: executeAllTasks()
                    ├─> Case 7: printSummaryReport()
                    └─> Case 0: Exit
```

### Task Execution Flow

```
executeAllTasks()
  └─> Check if tasks exist
  └─> Check for circular dependencies
  └─> executeAll()
        └─> Collect all tasks as pointers
        └─> current_scheduler->schedule(tasks)  [POLYMORPHIC]
        └─> executor.runTasks(scheduled_tasks)
              └─> Multi-pass execution loop
                    ├─> For each task:
                    │     ├─> Check if ready (dependencies met)
                    │     └─> executeTaskWithSubtasks(task)  [RECURSIVE]
                    │           ├─> Print RUNNING status
                    │           ├─> Execute subtasks first (depth-first)
                    │           ├─> showProgressAnimation()
                    │           ├─> Mark task complete
                    │           └─> Print COMPLETED status
                    └─> Retry deferred tasks next pass
```

### Dependency Resolution

```
Multi-Pass Algorithm:
  Pass 1: Execute tasks with no dependencies
  Pass 2: Execute tasks whose dependencies completed in Pass 1
  Pass 3: Execute tasks whose dependencies completed in Pass 2
  ...
  Pass N: Continue until no progress or MAX_PASSES reached
```

---

## Technical Specifications

### Compilation

**Compiler**: g++ (MinGW) or any C++17 compatible compiler

**Command**:

```bash
g++ -std=c++17 -Wall -Wextra -O2 src/*.cpp -o htse
```

**Flags**:

- `-std=c++17`: Use C++17 standard
- `-Wall`: Enable all warnings
- `-Wextra`: Extra warnings
- `-O2`: Optimization level 2

### Dependencies

**Standard Library Headers**:

```cpp
#include <iostream>     // I/O operations
#include <vector>       // Dynamic arrays
#include <string>       // String handling
#include <memory>       // Smart pointers
#include <map>          // Associative containers
#include <set>          // Set containers
#include <limits>       // Numeric limits
#include <algorithm>    // sort, etc.
#include <iomanip>      // I/O formatting
#include <windows.h>    // Sleep() for Windows
```

### Platform-Specific Code

**Windows-specific**:

```cpp
#include <windows.h>
Sleep(milliseconds);  // Task execution delay
```

**For cross-platform**, replace with:

```cpp
#include <chrono>
#include <thread>
std::this_thread::sleep_for(std::chrono::milliseconds(ms));
```

### Memory Management

**Smart Pointers Used**:

- `unique_ptr<Task>`: Task ownership in TaskManager
- `unique_ptr<Scheduler>`: Scheduler ownership
- Raw pointers (`Task*`): Non-owning references for navigation

**RAII Principle**: Resources automatically managed via smart pointers

---

## Code Quality Metrics

### Lines of Code

| File                   | Header Lines | Implementation Lines | Total     |
| ---------------------- | ------------ | -------------------- | --------- |
| task.h                 | ~60          | -                    | 60        |
| task.cpp               | -            | ~168                 | 168       |
| scheduler.h            | ~20          | -                    | 20        |
| priority_scheduler     | ~30          | ~40                  | 70        |
| deadline_scheduler     | ~30          | ~40                  | 70        |
| hierarchical_scheduler | ~35          | ~70                  | 105       |
| task_executor          | ~40          | ~153                 | 193       |
| task_manager           | ~75          | ~540                 | 615       |
| main.cpp               | -            | ~15                  | 15        |
| **Total**              | **~290**     | **~1026**            | **~1316** |

### OOP Metrics

- **Classes**: 8 (Task, Scheduler, 3 Schedulers, TaskExecutor, TaskManager, Main)
- **Inheritance Depth**: 2 levels (Scheduler → Concrete Schedulers)
- **Polymorphic Methods**: 2 virtual methods × 3 implementations = 6
- **Composition Relationships**: 5 major compositions
- **Recursive Functions**: 5

---

## Testing Scenarios

### Test Case 1: Basic Task Creation

**Input**:

```
1                  (Add Task)
Test Task
5
7
3
```

**Expected Output**:

```
[SUCCESS] Task created!
  ID: 1 | Name: "Test Task"
  Priority: 5 | Deadline: 7d | Time: 3u
```

---

### Test Case 2: Hierarchical Structure

**Input**:

```
1 → Create Parent (Task 1)
1 → Create Child 1 (Task 2)
1 → Create Child 2 (Task 3)
2 → Add Task 2 as subtask of Task 1
2 → Add Task 3 as subtask of Task 1
5 → Display Hierarchy
```

**Expected Output**:

```
[*] Task 1: Parent [P=8, D=5d, PENDING]
 |-- Task 2: Child 1 [P=6, D=10d, PENDING]
 |-- Task 3: Child 2 [P=7, D=8d, PENDING]
```

---

### Test Case 3: Dependency Execution

**Input**:

```
1 → Create Task A (no deps)
1 → Create Task B (will depend on A)
3 → Set Task B depends on A
6 → Execute
```

**Expected Output**:

```
[~] RUNNING: Task A
Progress: [===] 100%
[+] COMPLETED: Task A

[~] RUNNING: Task B  (executed after A completes)
Progress: [===] 100%
[+] COMPLETED: Task B
```

---

### Test Case 4: Scheduler Comparison

**Input**: Create same tasks, execute with each scheduler

**Expected Behavior**:

- **Priority**: Executes highest priority first
- **Deadline**: Executes earliest deadline first
- **Hierarchical**: Executes parents before children

---

## Troubleshooting

### Common Issues

| Issue                 | Cause                 | Solution                     | File              |
| --------------------- | --------------------- | ---------------------------- | ----------------- |
| Tasks not executing   | Circular dependencies | Check dependency graph       | task_manager.cpp  |
| Compilation error     | Missing includes      | Add required headers         | All files         |
| Crash on exit         | Double deletion       | Use smart pointers correctly | task_manager.cpp  |
| Wrong execution order | Incorrect scheduler   | Verify scheduler selection   | All schedulers    |
| No progress bar       | Missing flush         | Add `output.flush()`         | task_executor.cpp |

---

## Future Enhancements

### Potential Features

1. **File I/O**: Save/load task configurations
2. **Multi-threading**: Parallel task execution
3. **Real-time Updates**: Live status display
4. **Task Editing**: Modify existing tasks
5. **Undo/Redo**: Command pattern implementation
6. **Logging**: Execution history tracking
7. **Network Support**: Distributed task scheduling
8. **GUI**: Graphical interface using Qt/wxWidgets

### Scalability Considerations

- **Database Integration**: Store tasks in SQLite
- **Load Balancing**: Distribute tasks across workers
- **Priority Queues**: More efficient scheduling
- **Caching**: Memoize scheduling results

---

## Conclusion

This project demonstrates comprehensive understanding of OOP principles through practical implementation:

✅ **Encapsulation**: Data hiding and controlled access  
✅ **Inheritance**: Code reuse through class hierarchies  
✅ **Polymorphism**: Runtime behavior selection  
✅ **Abstraction**: Interface-implementation separation  
✅ **Composition**: Complex object relationships  
✅ **Recursion**: Hierarchical problem solving

The HTSE system provides a solid foundation for understanding how professional software systems are architected using object-oriented design principles.

---

**Document Version**: 1.0  
**Last Updated**: October 27, 2025  
**Author**: Technical Documentation Team  
**Project**: Hierarchical Task Scheduling Engine (HTSE)
