# 4. SOURCE CODE SAMPLES

This section provides representative code samples from the project with brief explanations of design decisions and implementation techniques.

## Sample 1: Task Class - Core Entity

**File:** task.cpp

**Purpose:** Demonstrates encapsulation and operator overloading.

```cpp
class Task {
private:
    int id;
    string name;
    int priority;
    int deadline;
    TaskStatus status;
    int estimated_time;
    vector<Task*> subtasks;
    vector<Task*> dependencies;

public:
    Task(int _id, string _name, int _prio, int _deadline, int _time)
        : id(_id), name(_name), priority(_prio),
          deadline(_deadline), status(PENDING), estimated_time(_time) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getPriority() const { return priority; }
    int getDeadline() const { return deadline; }
    TaskStatus getStatus() const { return status; }

    bool operator<(const Task& other) const {
        return priority < other.priority;
    }

    Task operator+(int value) const {
        Task temp = *this;
        temp.priority += value;
        return temp;
    }

    Task& operator+=(int value) {
        priority += value;
        return *this;
    }
};
```

**Design Reasoning:**

- Private member variables enforce encapsulation
- Const methods for getters prevent accidental modification
- Operator overloading provides intuitive task manipulation
- Initializer list in constructor ensures efficient initialization

## Sample 2: Scheduler Abstraction

**File:** scheduler.h

**Purpose:** Demonstrates abstraction and polymorphism foundation.

```cpp
class Scheduler {
public:
    virtual vector<Task*> schedule(const vector<Task*>& tasks) = 0;
    virtual string getName() const = 0;
    virtual ~Scheduler() {}
};
```

**Design Reasoning:**

- Pure virtual methods create abstract interface
- No data members, only behavior contract
- Virtual destructor ensures proper cleanup in derived classes
- Enables runtime polymorphism through base class pointers

## Sample 3: PriorityScheduler Implementation

**File:** priority_scheduler.cpp

**Purpose:** Demonstrates inheritance and concrete implementation.

```cpp
class PriorityScheduler : public Scheduler {
public:
    vector<Task*> schedule(const vector<Task*>& tasks) override {
        vector<Task*> sorted_tasks = tasks;
        sort(sorted_tasks.begin(), sorted_tasks.end(), comparePriority);
        return sorted_tasks;
    }

    string getName() const override {
        return "Priority Scheduler";
    }

private:
    static bool comparePriority(const Task* a, const Task* b) {
        return a->getPriority() > b->getPriority();
    }
};
```

**Design Reasoning:**

- Inherits from Scheduler base class
- Override keyword ensures method signature matches base
- Static comparison function avoids unnecessary object context
- Simple, focused implementation of single responsibility

## Sample 4: Polymorphic Scheduler Selection

**File:** task_manager.cpp (Final mode only)

**Purpose:** Demonstrates runtime polymorphism.

```cpp
void TaskManager::chooseSchedulingStrategy() {
    cout << "\nAvailable Scheduling Strategies:" << endl;
    cout << "1. Priority Scheduler" << endl;
    cout << "2. Deadline Scheduler" << endl;
    cout << "3. Hierarchical Scheduler" << endl;

    int choice = getValidatedInt("\nSelect strategy (1-3): ", 1, 3);

    switch (choice) {
        case 1:
            current_scheduler = make_unique<PriorityScheduler>();
            break;
        case 2:
            current_scheduler = make_unique<DeadlineScheduler>();
            break;
        case 3:
            current_scheduler = make_unique<HierarchicalScheduler>();
            break;
    }

    printSuccess("Scheduler set to: " + current_scheduler->getName());
}
```

**Design Reasoning:**

- unique_ptr manages scheduler lifetime automatically
- Base class pointer can hold any derived scheduler
- make_unique ensures exception-safe allocation
- Polymorphic getName() call works on any scheduler type

## Sample 5: Template Statistics Class

**File:** template_utils.h (Final mode only)

**Purpose:** Demonstrates templates and exception handling.

```cpp
template <typename T>
class Statistics {
public:
    static double average(const vector<T>& data) {
        if (data.empty()) {
            throw runtime_error("Cannot calculate average of empty dataset");
        }

        T total = 0;
        for (const T& val : data) {
            total += val;
        }
        return static_cast<double>(total) / data.size();
    }

    static T median(vector<T> data) {
        if (data.empty()) {
            throw runtime_error("Cannot calculate median of empty dataset");
        }

        sort(data.begin(), data.end());
        size_t mid = data.size() / 2;

        if (data.size() % 2 == 0) {
            return (data[mid - 1] + data[mid]) / 2;
        }
        return data[mid];
    }

    static T range(const vector<T>& data) {
        if (data.empty()) {
            throw runtime_error("Cannot calculate range of empty dataset");
        }

        T min = *min_element(data.begin(), data.end());
        T max = *max_element(data.begin(), data.end());
        return max - min;
    }
};
```

**Design Reasoning:**

- Template parameter T allows use with any numeric type
- Static methods eliminate need for object instantiation
- Exception throwing handles edge cases safely
- Generic implementation works for int, double, float, etc.

## Sample 6: Progress Animation with Flush

**File:** task_executor.cpp

**Purpose:** Demonstrates real-time output using flush().

```cpp
void TaskExecutor::showProgressAnimation(Task* task, int indent) {
    int total_steps = 20;
    int time_per_step = (task->getEstimatedTime() * EXEC_DELAY_MS) / total_steps;

    string indentation(indent * 2, ' ');
    output << indentation << "Progress: [";
    output.flush();  // Critical: force display of opening bracket

    for (int i = 0; i < total_steps; i++) {
        output << "=";
        output.flush();  // Critical: update bar after each step
        Sleep(time_per_step);
    }

    output << "] 100%" << endl;
}
```

**Design Reasoning:**

- flush() forces immediate display instead of buffered output
- Without flush(), progress bar appears all at once after completion
- Sleep() creates visual delay between steps
- Indentation parameter enables hierarchical visual nesting

## Sample 7: Color Implementation

**File:** config.h

**Purpose:** Demonstrates preprocessor-based color management.

```cpp
#define ENABLE_COLOR 1

#if ENABLE_COLOR
    #define COLOR_CYAN "\033[1;36m"
    #define COLOR_GREEN "\033[1;32m"
    #define COLOR_YELLOW "\033[1;33m"
    #define COLOR_RED "\033[1;31m"
    #define COLOR_BLUE "\033[1;34m"
    #define COLOR_MAGENTA "\033[1;35m"
    #define COLOR_RESET "\033[0m"
#else
    #define COLOR_CYAN ""
    #define COLOR_GREEN ""
    #define COLOR_YELLOW ""
    #define COLOR_RED ""
    #define COLOR_BLUE ""
    #define COLOR_MAGENTA ""
    #define COLOR_RESET ""
#endif
```

**Usage in task.cpp:**

```cpp
void Task::displayInfo(int indent) const {
    string indentation(indent * 2, ' ');
    cout << indentation << COLOR_CYAN << "[Task #" << id << "]" << COLOR_RESET << endl;
    cout << indentation << "Name: " << COLOR_GREEN << name << COLOR_RESET << endl;
    cout << indentation << "Priority: " << COLOR_YELLOW << priority << COLOR_RESET << endl;
    cout << indentation << "Deadline: " << COLOR_RED << deadline << " days" << COLOR_RESET << endl;
}
```

**Design Reasoning:**

- ANSI escape codes enable terminal colors on compatible systems
- Preprocessor flag allows easy disabling for incompatible terminals
- Macros eliminate string duplication throughout codebase
- COLOR_RESET prevents color bleeding to subsequent output

## Sample 8: D2_MODE Conditional Compilation

**File:** task_manager.cpp

**Purpose:** Demonstrates build mode configuration.

```cpp
void TaskManager::printMenu() const {
    cout << "| [1] Add New Task                                             |" << endl;
    cout << "| [2] Add Subtask                                              |" << endl;
    cout << "| [3] Set Task Dependency                                      |" << endl;

#ifndef D2_MODE
    cout << "| [4] Choose Scheduling Strategy                               |" << endl;
#endif

    cout << "| [5] Display Task Hierarchy                                   |" << endl;
    cout << "| [6] Execute All Tasks                                        |" << endl;
    cout << "| [7] View Execution Report                                    |" << endl;
    cout << "| [8] Compare Tasks (Operator)                                 |" << endl;
    cout << "| [9] Modify Task Priority (Operator)                          |" << endl;
    cout << "| [10] Display Tasks (Operator)                                |" << endl;

#ifndef D2_MODE
    cout << "| [11] Task Statistics (Template)                              |" << endl;
    cout << "| [12] Generic Container Demo                                  |" << endl;
    cout << "| [13] Generic Comparator Demo                                 |" << endl;
#endif

    cout << "| [0] Exit                                                     |" << endl;
}
```

**Design Reasoning:**

- D2_MODE build excludes options 4, 11, 12, 13
- Compilation command controls which features are available
- Same source files support both configurations
- Enables incremental feature demonstration in academic context

## Sample 9: Circular Dependency Detection

**File:** task_manager.cpp

**Purpose:** Demonstrates graph cycle detection algorithm.

```cpp
bool TaskManager::detectCycle(Task* start, set<int>& visited, set<int>& rec_stack) const {
    int id = start->getId();

    visited.insert(id);
    rec_stack.insert(id);

    for (Task* dep : start->getDependencies()) {
        int dep_id = dep->getId();

        if (rec_stack.find(dep_id) != rec_stack.end()) {
            return true;  // Back edge found, cycle detected
        }

        if (visited.find(dep_id) == visited.end()) {
            if (detectCycle(dep, visited, rec_stack)) {
                return true;
            }
        }
    }

    rec_stack.erase(id);
    return false;
}

bool TaskManager::hasCircularDependencies() const {
    set<int> visited;
    set<int> rec_stack;

    for (const auto& task_pair : all_tasks) {
        Task* task = task_pair.get();
        if (visited.find(task->getId()) == visited.end()) {
            if (detectCycle(task, visited, rec_stack)) {
                return true;
            }
        }
    }

    return false;
}
```

**Design Reasoning:**

- Depth-first search with recursion stack tracking
- Detects cycles by identifying back edges in dependency graph
- Two sets: visited tracks explored nodes, rec_stack tracks current path
- Prevents infinite loops during task execution

## Sample 10: Input Validation Helper

**File:** task_manager.cpp

**Purpose:** Demonstrates robust user input handling.

```cpp
int TaskManager::getValidatedInt(const string& prompt, int min, int max) {
    int value;
    cout << prompt;

    while (!(cin >> value) || value < min || value > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (value < min || value > max) {
            cout << "[!] Out of range! Enter " << min << "-" << max << ": ";
        } else {
            cout << "[!] Invalid input! Enter a number: ";
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}
```

**Design Reasoning:**

- cin >> value returns false on non-numeric input
- cin.clear() resets error flags after failed read
- cin.ignore() discards invalid characters from buffer
- Loop continues until valid input received
- Prevents crashes and provides clear user feedback

## Sample 11: Hierarchical Scheduler Recursion

**File:** hierarchical_scheduler.cpp

**Purpose:** Demonstrates recursive tree traversal.

```cpp
void HierarchicalScheduler::collectTasksInOrder(Task* task, vector<Task*>& result,
                                                 set<int>& visited) {
    if (visited.find(task->getId()) != visited.end()) {
        return;  // Already processed
    }

    visited.insert(task->getId());
    result.push_back(task);

    vector<Task*> children = task->getSubtasks();
    sort(children.begin(), children.end(), PriorityCompare());

    for (Task* child : children) {
        collectTasksInOrder(child, result, visited);
    }
}
```

**Design Reasoning:**

- Recursive depth-first traversal of task tree
- Visited set prevents duplicate processing
- Subtasks sorted by priority before recursion
- Builds flat execution order from hierarchical structure

## Sample 12: Operator Overloading Usage

**File:** task_manager.cpp

**Purpose:** Demonstrates operator overloading in practical context.

```cpp
void TaskManager::modifyTaskPriorityDemo() {
    cout << "\n=== Modify Task Priority Demo ===" << endl;

    if (all_tasks.empty()) {
        printWarning("No tasks available.");
        return;
    }

    int id = getValidatedInt("Enter task ID: ", 1, next_task_id - 1);
    Task* task = findTaskById(id);

    if (!task) {
        printError("Task not found.");
        return;
    }

    cout << "\n[Before] Priority: " << task->getPriority() << endl;

    Task temp = *task + 2;  // Uses operator+
    cout << "[After +2] Priority: " << temp.getPriority() << endl;

    *task += 1;  // Uses operator+=
    cout << "[After +=1] Priority: " << task->getPriority() << endl;

    (*task)++;  // Uses operator++
    cout << "[After ++] Priority: " << task->getPriority() << endl;
}
```

**Design Reasoning:**

- Demonstrates three different increment operators
- operator+ creates new object without modifying original
- operator+= modifies object in place
- operator++ provides prefix/postfix increment options
- Shows intuitive task priority manipulation

## Sample 13: Template Container Demo

**File:** task_manager.cpp (Final mode only)

**Purpose:** Demonstrates generic container template usage.

```cpp
void TaskManager::containerDemo() {
    cout << "\n=== Generic Container Demo ===" << endl;

    Container<int> int_container;
    int_container.add(5);
    int_container.add(10);
    int_container.add(15);

    cout << "\nInteger container:" << endl;
    int_container.display();

    Container<string> string_container;
    string_container.add("Task-A");
    string_container.add("Task-B");
    string_container.add("Task-C");

    cout << "\nString container:" << endl;
    string_container.display();

    try {
        int value = int_container.get(1);
        cout << "\nValue at index 1: " << value << endl;
    } catch (const exception& e) {
        printError(e.what());
    }
}
```

**Design Reasoning:**

- Same Container class works with both int and string
- Template instantiation occurs at compile time
- Exception handling demonstrates error management
- Shows code reuse benefit of generic programming

## Sample 14: Exception Handling in Templates

**File:** template_utils.h

**Purpose:** Demonstrates exception propagation and handling.

```cpp
// Template method that throws
template <typename T>
static double average(const vector<T>& data) {
    if (data.empty()) {
        throw runtime_error("Cannot calculate average of empty dataset");
    }
    // ... calculation
}

// Usage with exception handling (in task_manager.cpp)
void TaskManager::statisticsDemo() {
    try {
        vector<int> priorities = {1, 5, 3, 9, 2};
        double avg = Statistics<int>::average(priorities);
        cout << "Average: " << avg << endl;

        vector<int> empty;
        double bad_avg = Statistics<int>::average(empty);  // Throws
    } catch (const runtime_error& e) {
        printError(string("Error: ") + e.what());
    }
}
```

**Design Reasoning:**

- Template methods can throw exceptions
- Caller must handle potential exceptions
- runtime_error provides descriptive message
- Prevents crashes from invalid operations

## Sample 15: Smart Pointer Usage

**File:** task_manager.h and task_manager.cpp

**Purpose:** Demonstrates automatic memory management.

```cpp
// In task_manager.h
class TaskManager {
private:
    vector<unique_ptr<Task>> all_tasks;  // Owns tasks
    map<int, Task*> task_map;            // Non-owning lookup

#ifndef D2_MODE
    unique_ptr<Scheduler> current_scheduler;  // Owns scheduler
#endif
};

// In task_manager.cpp
Task* TaskManager::createTask(string name, int priority, int deadline, int time) {
    int id = next_task_id++;
    auto task = make_unique<Task>(id, name, priority, deadline, time);
    Task* task_ptr = task.get();

    all_tasks.push_back(move(task));  // Transfer ownership
    task_map[id] = task_ptr;          // Store non-owning pointer

    return task_ptr;
}
```

**Design Reasoning:**

- unique_ptr ensures tasks deleted when TaskManager destroyed
- make_unique exception-safe allocation
- move() transfers ownership to vector
- Non-owning raw pointer for fast lookup
- No manual delete needed, automatic cleanup
