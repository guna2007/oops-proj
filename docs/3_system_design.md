# 3. SYSTEM DESIGN

## Architecture Overview

The system follows a modular architecture with clear separation of concerns. The design uses the Model-View-Controller pattern adapted for command-line interface, where Task entities serve as the Model, TaskManager handles Controller logic, and console output serves as the View.

## Class Diagram Structure

### Core Classes

1. Task - Represents individual work items
2. TaskManager - Orchestrates the entire system
3. TaskExecutor - Handles task execution logic
4. Scheduler (Abstract) - Defines scheduling interface
5. PriorityScheduler - Concrete scheduler implementation
6. DeadlineScheduler - Concrete scheduler implementation
7. HierarchicalScheduler - Concrete scheduler implementation

### Utility Classes

1. Statistics - Template class for statistical calculations
2. Container - Template class for generic storage
3. Comparator - Template class for comparison operations
4. Pair - Template class for key-value pairs

## Detailed Class Descriptions

### 1. Task Class

**File:** task.h, task.cpp  
**Lines of Code:** 94 (header) + 284 (implementation) = 378 total

**Purpose:** Represents a single task with properties and relationships.

**Private Members:**

```
- int id                        // Unique task identifier
- string name                   // Task name/description
- int priority                  // Priority level (1-10)
- int deadline                  // Days until deadline
- TaskStatus status             // Current status (PENDING/RUNNING/COMPLETED)
- int estimated_time            // Execution time in units
- vector<Task*> subtasks        // Child tasks
- vector<Task*> dependencies    // Tasks that must complete first
```

**Public Methods:**

```
Constructors & Destructor:
- Task(int id, string name, int priority, int deadline, int time)
- ~Task()

Getters (Read-only access):
- int getId() const
- string getName() const
- int getPriority() const
- int getDeadline() const
- TaskStatus getStatus() const
- int getEstimatedTime() const
- const vector<Task*>& getSubtasks() const
- const vector<Task*>& getDependencies() const

Relationship Management:
- void addSubtask(Task* t)
- void addDependency(Task* t)

State Management:
- bool isReady() const
- void execute()
- void markComplete()

Display Methods:
- void displayInfo(int indent) const
- void displayHierarchy(int indent) const
- int getTotalSubtasks() const

Operator Overloading:
- bool operator<(const Task& other) const
- bool operator>(const Task& other) const
- bool operator<=(const Task& other) const
- bool operator>=(const Task& other) const
- bool operator==(const Task& other) const
- bool operator!=(const Task& other) const
- Task operator+(int value) const
- Task operator-(int value) const
- Task& operator+=(int value)
- Task& operator-=(int value)
- Task& operator++()
- Task operator++(int)
- Task& operator--()
- Task operator--(int)
- Task& operator=(const Task& other)
- friend ostream& operator<<(ostream& os, const Task& task)
```

**OOP Concepts:** Encapsulation, Operator Overloading

### 2. TaskManager Class

**File:** task_manager.h, task_manager.cpp  
**Lines of Code:** 107 (header) + 626 (implementation) = 733 total

**Purpose:** Central controller managing all tasks and user interaction.

**Private Members:**

```
Storage:
- vector<unique_ptr<Task>> all_tasks        // Owns all task objects
- map<int, Task*> task_map                  // Quick ID lookup
- int next_task_id                          // Auto-increment ID counter

Scheduling (Build-mode dependent):
#ifdef D2_MODE:
- PriorityScheduler* priority_scheduler     // Direct pointer
#else:
- unique_ptr<Scheduler> current_scheduler   // Polymorphic pointer
#endif

Execution:
- TaskExecutor executor                     // Task execution engine
- int completed_tasks                       // Completion counter
- int total_simulated_time                  // Total execution time
- string last_scheduler_name                // Last used scheduler name
```

**Private Helper Methods:**

```
UI Helpers:
- void printHeader() const
- void printMenu() const
- void printSection(const string& title) const
- void printLine() const
- void printSuccess(const string& msg) const
- void printWarning(const string& msg) const
- void printError(const string& msg) const
- int getValidatedInt(const string& prompt, int min, int max)
- bool getTaskIds(int& id1, int& id2, const string& label1, const string& label2)

Feature Methods:
- void displayMenu() const
- void addNewTask()
- void addSubtaskToTask()
- void setTaskDependency()
- void chooseSchedulingStrategy()           // Final mode only
- void displayTaskHierarchy() const
- void executeAllTasks()
- void printSummaryReport() const

Operator Overloading Demos:
- void compareTasksDemo()
- void modifyTaskPriorityDemo()
- void displayTasksWithOperator()

Template Demos (Final mode only):
- void statisticsDemo()
- void containerDemo()
- void comparatorDemo()

Validation Helpers:
- Task* findTaskById(int id) const
- bool validateTaskId(int id) const
- bool detectCycle(Task* start, set<int>& visited, set<int>& rec_stack) const
- bool hasCircularDependencies() const
```

**Public Methods:**

```
- TaskManager()                             // Constructor
- void run()                                // Main CLI loop
- Task* createTask(...)                     // Task factory method
- void addSubtask(int parent_id, int subtask_id)
- void addDependency(int task_id, int dependency_id)
- void setScheduler(unique_ptr<Scheduler> sched)  // Final mode only
- void executeAll()
```

**OOP Concepts:** Encapsulation, Abstraction, Polymorphism (Final mode), Composition

### 3. TaskExecutor Class

**File:** task_executor.h, task_executor.cpp  
**Lines of Code:** 39 (header) + 164 (implementation) = 203 total

**Purpose:** Executes tasks with visual progress tracking.

**Private Members:**

```
- ostream& output                           // Output stream reference
- int total_execution_time                  // Accumulated execution time
```

**Private Methods:**

```
- void executeTaskWithSubtasks(Task* task, int indent)
- void showProgressAnimation(Task* task, int indent)
- void printTaskExecution(Task* task, int indent, const string& action)
```

**Public Methods:**

```
- TaskExecutor(ostream& out = cout)         // Constructor
- void runTasks(const vector<Task*>& ordered_tasks, const string& scheduler_name)
- int getTotalExecutionTime() const
- void resetExecutionTime()
```

**OOP Concepts:** Encapsulation, Composition

### 4. Scheduler (Abstract Base Class)

**File:** scheduler.h  
**Lines of Code:** 26

**Purpose:** Defines interface for scheduling algorithms.

**Pure Virtual Methods:**

```
- virtual vector<Task*> schedule(const vector<Task*>& tasks) = 0
- virtual string getName() const = 0
- virtual ~Scheduler() {}
```

**OOP Concepts:** Abstraction, Polymorphism

### 5. PriorityScheduler Class

**File:** priority_scheduler.h, priority_scheduler.cpp  
**Lines of Code:** 20 (header) + 24 (implementation) = 44 total

**Purpose:** Schedules tasks by priority (highest first).

**Implementation:**

```
Static Helper:
- static bool comparePriority(const Task* a, const Task* b)

Overridden Methods:
- vector<Task*> schedule(const vector<Task*>& tasks) override
- string getName() const override
```

**Algorithm:** Sorts tasks in descending order of priority using std::sort.

**OOP Concepts:** Inheritance, Polymorphism

### 6. DeadlineScheduler Class

**File:** deadline_scheduler.h, deadline_scheduler.cpp  
**Lines of Code:** 20 (header) + 24 (implementation) = 44 total

**Purpose:** Schedules tasks by deadline (earliest first).

**Implementation:**

```
Static Helper:
- static bool compareDeadline(const Task* a, const Task* b)

Overridden Methods:
- vector<Task*> schedule(const vector<Task*>& tasks) override
- string getName() const override
```

**Algorithm:** Sorts tasks in ascending order of deadline using std::sort.

**OOP Concepts:** Inheritance, Polymorphism

### 7. HierarchicalScheduler Class

**File:** hierarchical_scheduler.h, hierarchical_scheduler.cpp  
**Lines of Code:** 26 (header) + 66 (implementation) = 92 total

**Purpose:** Schedules tasks respecting parent-child hierarchy.

**Private Methods:**

```
- void collectTasksInOrder(Task* task, vector<Task*>& result, set<int>& visited)
```

**Overridden Methods:**

```
- vector<Task*> schedule(const vector<Task*>& tasks) override
- string getName() const override
```

**Algorithm:**

1. Identify root tasks (not subtasks of any other task)
2. Sort root tasks by priority
3. Recursively traverse each root task and its subtasks depth-first

**OOP Concepts:** Inheritance, Polymorphism, Recursion

### 8. Statistics Template Class

**File:** template_utils.h  
**Lines of Code:** Included in 262-line template_utils.h

**Purpose:** Generic statistical calculations.

**Template Methods:**

```
- static double average(const vector<T>& data)
- static T sum(const vector<T>& data)
- static T median(vector<T> data)
- static T range(const vector<T>& data)
```

**OOP Concepts:** Templates, Exception Handling

### 9. Container Template Class

**File:** template_utils.h

**Purpose:** Generic storage container with display capability.

**Template Methods:**

```
- void add(const T& item)
- void display() const
- T get(size_t index) const
- size_t size() const
```

**OOP Concepts:** Templates, Encapsulation

### 10. Comparator Template Class

**File:** template_utils.h

**Purpose:** Generic comparison and sorting utilities.

**Template Methods:**

```
- static T findMax(const vector<T>& data)
- static T findMin(const vector<T>& data)
- static vector<T> sortAscending(vector<T> data)
- static vector<T> sortDescending(vector<T> data)
- static int countGreaterThan(const vector<T>& data, const T& threshold)
- static int countLessThan(const vector<T>& data, const T& threshold)
```

**OOP Concepts:** Templates, Exception Handling

## Configuration System

**File:** config.h  
**Lines of Code:** 71

**Purpose:** Centralized build configuration and constants.

**Configuration Flags:**

```
#define ENABLE_COLOR 1              // Enable ANSI color codes
#define EXEC_DELAY_MS 100           // Execution delay per time unit
#define UI_BORDER "+============================================================+"
```

**Conditional Compilation:**

The D2_MODE flag controls feature availability:

```cpp
#ifdef D2_MODE
    // D2 Mode: Limited features
    PriorityScheduler* priority_scheduler;
#else
    // Final Mode: All features
    unique_ptr<Scheduler> current_scheduler;
#endif
```

**Color Constants:**

```cpp
#if ENABLE_COLOR
    #define COLOR_CYAN "\033[1;36m"
    #define COLOR_GREEN "\033[1;32m"
    #define COLOR_YELLOW "\033[1;33m"
    #define COLOR_RED "\033[1;31m"
    #define COLOR_BLUE "\033[1;34m"
    #define COLOR_MAGENTA "\033[1;35m"
    #define COLOR_RESET "\033[0m"
#else
    // Empty definitions when colors disabled
    #define COLOR_CYAN ""
    ...
#endif
```

## Data Structures and Relationships

### Storage Strategy

**TaskManager uses multiple data structures:**

1. `vector<unique_ptr<Task>>` - Owns all task objects, automatic memory management
2. `map<int, Task*>` - Fast O(log n) lookup by task ID
3. `set<int>` - Track visited nodes during cycle detection

### Relationships

**Composition:**

- TaskManager HAS-A TaskExecutor
- TaskManager HAS-A vector of Tasks
- Task HAS-A vector of subtasks (aggregation)

**Inheritance:**

- PriorityScheduler IS-A Scheduler
- DeadlineScheduler IS-A Scheduler
- HierarchicalScheduler IS-A Scheduler

**Dependency:**

- TaskExecutor depends on Task interface
- TaskManager depends on Scheduler interface

## Control Flow

### Program Execution Flow

```
1. main() creates TaskManager instance
2. TaskManager::run() starts main loop
3. Display menu and get user choice
4. Switch on choice:
   - Options 1-3: Task management
   - Option 4: Scheduler selection (Final mode)
   - Option 5: Display hierarchy
   - Option 6: Execute tasks
   - Option 7: View report
   - Options 8-10: Operator demos
   - Options 11-13: Template demos (Final mode)
   - Option 0: Exit
5. Repeat until user exits
```

### Task Execution Flow

```
1. User selects "Execute All Tasks"
2. TaskManager calls executeAll()
3. Collect all tasks into vector
4. Current scheduler sorts tasks
5. TaskExecutor::runTasks() receives sorted list
6. For each task in list:
   a. Check if dependencies met
   b. If ready: executeTaskWithSubtasks()
   c. If not ready: defer to next pass
7. Show progress animation during execution
8. Mark task complete
9. Update statistics
10. Display completion summary
```

### Dependency Resolution Flow

```
1. User attempts to execute tasks
2. System checks hasCircularDependencies()
3. For each task, perform DFS cycle detection
4. If cycle found: abort execution, show error
5. If no cycle: proceed with execution
6. During execution, check isReady() for each task
7. Task is ready only when all dependencies are COMPLETED
8. Defer unready tasks to later passes
9. Maximum 10 passes to prevent infinite loops
```

## Build System Design

### Compilation Modes

**D2_MODE Build:**

Command: `g++ -std=c++17 -Wall -Wextra -O2 -DD2_MODE src/*.cpp -o htse.exe`

Features:

- Option 4 (scheduler selection) hidden
- Options 11-13 (templates) hidden
- Uses direct PriorityScheduler pointer
- Demonstrates 4 core OOP concepts

**Final Mode Build:**

Command: `g++ -std=c++17 -Wall -Wextra -O2 src/*.cpp -o htse.exe`

Features:

- All 13 menu options available
- Polymorphic scheduler selection
- Full template demonstrations
- Demonstrates all 7 OOP concepts

### Preprocessor Guards

Template utilities conditionally compiled:

```cpp
#ifndef D2_MODE
    #include "template_utils.h"
#endif
```

Menu options conditionally displayed:

```cpp
#ifndef D2_MODE
    cout << "| [4] Choose Scheduling Strategy                               |" << endl;
    cout << "| [11] Task Statistics (Template)                              |" << endl;
    cout << "| [12] Generic Container Demo                                  |" << endl;
    cout << "| [13] Generic Comparator Demo                                 |" << endl;
#endif
```

## Technical Implementation Details

### Progress Animation

The system uses output stream flushing for real-time progress:

```cpp
void TaskExecutor::showProgressAnimation(Task* task, int indent) {
    output << "Progress: [";
    output.flush();  // Force immediate display

    for (int i = 0; i < steps; i++) {
        output << "=";
        output.flush();  // Update after each step
        Sleep(delayPerStep);
    }

    output << "] 100%" << endl;
}
```

The flush() calls ensure the progress bar updates incrementally rather than appearing all at once.

### Memory Management

Smart pointers prevent memory leaks:

```cpp
vector<unique_ptr<Task>> all_tasks;  // Automatic cleanup
unique_ptr<Scheduler> current_scheduler;  // RAII principle
```

When TaskManager is destroyed, all unique_ptr objects automatically delete their managed objects.

### Input Validation

Centralized validation with retry loops:

```cpp
int TaskManager::getValidatedInt(const string& prompt, int min, int max) {
    int value;
    cout << prompt;
    while (!(cin >> value) || value < min || value > max) {
        cin.clear();  // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard bad input
        cout << "[!] Invalid! Enter " << min << "-" << max << ": ";
    }
    return value;
}
```

This prevents crashes from non-numeric input or out-of-range values.
