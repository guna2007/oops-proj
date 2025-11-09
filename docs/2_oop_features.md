# 2. OOP FEATURES IMPLEMENTATION

## Overview of OOP Concepts

This project implements all seven fundamental Object-Oriented Programming concepts as required. Each concept is strategically utilized in specific components of the system to demonstrate both theoretical understanding and practical application.

## 1. Encapsulation

### Definition

Encapsulation is the bundling of data and methods that operate on that data within a single unit, restricting direct access to internal object state.

### Implementation in HTSE

**Task Class (task.h, task.cpp)**

The Task class fully encapsulates task-related data with private member variables:

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
    // Controlled access through public methods
    int getId() const;
    string getName() const;
    int getPriority() const;
    // ... other getters
};
```

All member variables are private, accessible only through public getter methods. This prevents external code from directly modifying task state, ensuring data integrity.

**TaskManager Class (task_manager.h, task_manager.cpp)**

Encapsulates the entire task management system logic:

```cpp
class TaskManager {
private:
    vector<unique_ptr<Task>> all_tasks;
    map<int, Task*> task_map;
    TaskExecutor executor;
    int next_task_id;
    // Internal helper methods
    void printHeader() const;
    void printMenu() const;
public:
    void run();  // Public interface
    Task* createTask(...);
};
```

The implementation details of task storage, menu display, and execution are hidden from external users.

### Benefits Demonstrated

1. Data protection from unauthorized access
2. Flexibility to change internal implementation without affecting external code
3. Clear interface separation between public and private members

## 2. Abstraction

### Definition

Abstraction involves hiding complex implementation details and exposing only essential features through simplified interfaces.

### Implementation in HTSE

**Scheduler Abstract Class (scheduler.h)**

Defines a pure virtual interface for scheduling algorithms:

```cpp
class Scheduler {
public:
    virtual vector<Task*> schedule(const vector<Task*>& tasks) = 0;
    virtual string getName() const = 0;
    virtual ~Scheduler() {}
};
```

Users interact with the Scheduler interface without needing to understand the internal sorting algorithms.

**TaskManager Run Method**

The main run() method abstracts away all complexity of the CLI loop, input validation, and feature execution:

```cpp
void TaskManager::run() {
    // Simple interface hiding complex implementation
    while (true) {
        displayMenu();
        processUserChoice();
    }
}
```

### Benefits Demonstrated

1. Simplified user interaction with complex systems
2. Focus on "what" rather than "how"
3. Reduced cognitive load for system users

## 3. Inheritance

### Definition

Inheritance allows a class to derive properties and behaviors from another class, promoting code reuse and hierarchical relationships.

### Implementation in HTSE

**Scheduler Inheritance Hierarchy**

Three concrete scheduler classes inherit from the abstract Scheduler base class:

```cpp
class PriorityScheduler : public Scheduler {
public:
    vector<Task*> schedule(const vector<Task*>& tasks) override;
    string getName() const override;
};

class DeadlineScheduler : public Scheduler {
public:
    vector<Task*> schedule(const vector<Task*>& tasks) override;
    string getName() const override;
};

class HierarchicalScheduler : public Scheduler {
public:
    vector<Task*> schedule(const vector<Task*>& tasks) override;
    string getName() const override;
};
```

Each derived class inherits the interface contract from Scheduler and provides specific implementation.

### Benefits Demonstrated

1. Code reuse through inheritance
2. Polymorphic behavior through method overriding
3. IS-A relationship (PriorityScheduler IS-A Scheduler)

## 4. Polymorphism

### Definition

Polymorphism enables objects of different classes to be treated through a common interface, with behavior determined at runtime.

### Implementation in HTSE

**Runtime Scheduler Selection (Final Mode Only)**

The TaskManager uses polymorphism to work with different schedulers:

```cpp
class TaskManager {
private:
    unique_ptr<Scheduler> current_scheduler;  // Base class pointer
public:
    void setScheduler(unique_ptr<Scheduler> sched) {
        current_scheduler = move(sched);  // Accepts any derived scheduler
    }

    void executeAll() {
        // Runtime polymorphic behavior
        vector<Task*> scheduled = current_scheduler->schedule(tasks);
    }
};
```

The actual scheduling algorithm is determined at runtime based on user selection:

```cpp
// User can switch schedulers dynamically
setScheduler(make_unique<PriorityScheduler>());
// or
setScheduler(make_unique<DeadlineScheduler>());
// or
setScheduler(make_unique<HierarchicalScheduler>());
```

### Virtual Method Dispatch

Virtual methods ensure correct function is called based on actual object type:

```cpp
Scheduler* sched = new PriorityScheduler();
sched->schedule(tasks);  // Calls PriorityScheduler::schedule()
sched->getName();         // Returns "PriorityScheduler"
```

### Benefits Demonstrated

1. Dynamic behavior selection at runtime
2. Flexibility to add new schedulers without modifying existing code
3. Strategy Pattern implementation through polymorphism

## 5. Operator Overloading

### Definition

Operator overloading allows custom definitions of standard operators for user-defined types, making code more intuitive.

### Implementation in HTSE

**Task Comparison Operators**

Tasks can be compared using standard comparison operators based on priority:

```cpp
bool Task::operator<(const Task& other) const {
    return this->priority < other.priority;
}

bool Task::operator>(const Task& other) const {
    return this->priority > other.priority;
}

bool Task::operator==(const Task& other) const {
    return this->id == other.id;
}

bool Task::operator!=(const Task& other) const {
    return this->id != other.id;
}
```

**Arithmetic Operators for Priority Modification**

Tasks support arithmetic operations to modify priority:

```cpp
Task Task::operator+(int value) const {
    Task result = *this;
    result.priority = min(10, max(1, this->priority + value));
    return result;
}

Task& Task::operator+=(int value) {
    this->priority = min(10, max(1, this->priority + value));
    return *this;
}

Task& Task::operator++() {  // Pre-increment
    if (this->priority < 10) this->priority++;
    return *this;
}
```

**Stream Insertion Operator**

Custom output format for tasks:

```cpp
ostream& operator<<(ostream& os, const Task& task) {
    os << "Task[ID=" << task.id << ", Name=\"" << task.name
       << "\", Priority=" << task.priority << "...]";
    return os;
}
```

Usage examples:

```cpp
Task t1, t2;
if (t1 > t2) { /* higher priority */ }
t1 += 2;           // Increase priority by 2
++t1;              // Increment priority
Task t3 = t1 + 5;  // Create new task with modified priority
cout << t1;        // Print task details
```

### Benefits Demonstrated

1. Intuitive syntax for task manipulation
2. Natural comparison operations
3. Custom output formatting

## 6. Templates (Generic Programming)

### Definition

Templates enable writing generic code that works with any data type, promoting code reusability and type safety.

### Implementation in HTSE

**Statistics Template Class (template_utils.h)**

Generic statistical calculations for any numeric type:

```cpp
template <typename T>
class Statistics {
public:
    static double average(const vector<T>& data);
    static T sum(const vector<T>& data);
    static T median(vector<T> data);
    static T range(const vector<T>& data);
};
```

Usage with different types:

```cpp
vector<int> priorities = {5, 8, 3, 9};
double avg = Statistics<int>::average(priorities);
int total = Statistics<int>::sum(priorities);
```

**Container Template Class**

Generic container for storing and displaying any type:

```cpp
template <typename T>
class Container {
private:
    vector<T> items;
public:
    void add(const T& item);
    void display() const;
    T get(size_t index) const;
    size_t size() const;
};
```

Usage with multiple types:

```cpp
Container<int> intContainer;
intContainer.add(42);

Container<string> strContainer;
strContainer.add("Task");

Container<Pair<string, int>> pairContainer;
pairContainer.add(Pair<string, int>("Priority", 10));
```

**Comparator Template Class**

Generic comparison and sorting utilities:

```cpp
template <typename T>
class Comparator {
public:
    static T findMax(const vector<T>& data);
    static T findMin(const vector<T>& data);
    static vector<T> sortAscending(vector<T> data);
    static vector<T> sortDescending(vector<T> data);
    static int countGreaterThan(const vector<T>& data, const T& threshold);
};
```

### Benefits Demonstrated

1. Type-safe generic programming
2. Code reuse across different data types
3. Compile-time type checking

## 7. Exception Handling

### Definition

Exception handling provides a mechanism to handle runtime errors gracefully without crashing the program.

### Implementation in HTSE

**Template Operations (template_utils.h)**

Exception handling in template methods prevents crashes from invalid operations:

```cpp
template <typename T>
static T median(vector<T> data) {
    try {
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
    catch (const exception& e) {
        cerr << "Error in median calculation: " << e.what() << endl;
        return T();
    }
}
```

**Container Bounds Checking**

Exception handling for invalid index access:

```cpp
template <typename T>
T Container<T>::get(size_t index) const {
    try {
        if (index >= items.size()) {
            throw out_of_range("Index out of range");
        }
        return items[index];
    }
    catch (const out_of_range& e) {
        cerr << "Container access error: " << e.what() << endl;
        throw;
    }
}
```

### Benefits Demonstrated

1. Graceful error handling without program termination
2. Informative error messages for debugging
3. Resource cleanup through RAII and exception safety

## Summary of OOP Features Usage

| OOP Concept          | Primary Implementation               | Files Involved                           |
| -------------------- | ------------------------------------ | ---------------------------------------- |
| Encapsulation        | Task, TaskManager classes            | task.h/cpp, task_manager.h/cpp           |
| Abstraction          | Scheduler interface, simplified APIs | scheduler.h, task_manager.cpp            |
| Inheritance          | Scheduler hierarchy                  | priority/deadline/hierarchical_scheduler |
| Polymorphism         | Runtime scheduler selection          | task_manager.cpp, scheduler.h            |
| Operator Overloading | Task operators                       | task.h/cpp                               |
| Templates            | Generic utilities                    | template_utils.h                         |
| Exception Handling   | Error management in templates        | template_utils.h                         |

All seven OOP concepts are demonstrated in working, tested code with practical applications.
