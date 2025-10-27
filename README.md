# Hierarchical Task Scheduling Engine (HTSE)

## Project Overview

The Hierarchical Task Scheduling Engine (HTSE) is a console-based C++ application that demonstrates core Object-Oriented Programming (OOP) principles through a task scheduling simulation. This educational project showcases:

- **Encapsulation**: Private data members with controlled public interfaces
- **Inheritance**: Scheduler hierarchy with base and derived classes
- **Abstraction**: Abstract base classes and high-level interfaces
- **Polymorphism**: Runtime selection of different scheduling strategies
- **Composition**: Task containment and manager-task relationships
- **Recursion**: Hierarchical task traversal and cycle detection

## Features

- Create tasks with priority, deadline, and estimated execution time
- Build hierarchical task structures (parent-child relationships)
- Define task dependencies (prerequisite tasks)
- Multiple scheduling strategies:
  - **Priority-based**: Schedule by task priority (highest first)
  - **Deadline-based**: Schedule by earliest deadline first
  - **Hierarchical**: Schedule parent tasks before children
- Interactive CLI menu system
- Execution simulation with status reporting
- Circular dependency detection
- ASCII-based console output (plain text, educational format)

## Project Structure

```
OOPs-Proj/
├── src/
│   ├── task.h / task.cpp                      # Task class (base unit)
│   ├── scheduler.h                             # Abstract scheduler interface
│   ├── priority_scheduler.h / .cpp             # Priority-based scheduler
│   ├── deadline_scheduler.h / .cpp             # Deadline-based scheduler
│   ├── hierarchical_scheduler.h / .cpp         # Hierarchical scheduler
│   ├── task_executor.h / .cpp                  # Task execution engine
│   ├── task_manager.h / .cpp                   # Main coordinator & CLI
│   └── main.cpp                                # Entry point
├── docs/
│   └── (diagrams and documentation)
├── instructions.md                             # Complete project specification
├── Makefile                                    # Build configuration
└── README.md                                   # This file
```

## OOP Concepts Mapping

### Encapsulation

- **Task class**: Private attributes (id, name, priority, etc.) with public getters/setters
- **TaskManager**: Encapsulates all task management and CLI logic

### Inheritance

- **Scheduler hierarchy**: `PriorityScheduler`, `DeadlineScheduler`, and `HierarchicalScheduler` inherit from abstract `Scheduler` base class

### Abstraction

- **Scheduler**: Abstract base class with pure virtual `schedule()` method
- **High-level interfaces**: `TaskManager::run()`, `executeAll()` hide complexity

### Polymorphism

- **Runtime scheduling**: Different scheduler implementations called through base class pointer
- **Virtual functions**: `schedule()` and `getName()` overridden in derived classes

### Composition

- **Task contains subtasks**: Vector of Task pointers represents hierarchy
- **TaskManager owns Tasks**: Uses `unique_ptr<Task>` for ownership
- **TaskExecutor uses output stream**: Composition with `std::ostream`

### Recursion

- **Hierarchy display**: `Task::displayHierarchy()` recursively displays subtasks
- **Subtask counting**: `Task::getTotalSubtasks()` uses recursion
- **Cycle detection**: DFS-based recursive cycle detection in dependencies

## Building the Project

### Requirements

- C++17 compatible compiler (g++, clang++)
- Make (optional, for using Makefile)

### Compilation

#### Using Makefile (recommended):

```bash
make
```

#### Manual compilation:

```bash
g++ -std=c++17 -Wall -Wextra -O2 \
    src/main.cpp \
    src/task.cpp \
    src/priority_scheduler.cpp \
    src/deadline_scheduler.cpp \
    src/hierarchical_scheduler.cpp \
    src/task_executor.cpp \
    src/task_manager.cpp \
    -o htse
```

### Running

```bash
./htse
```

Or with Makefile:

```bash
make run
```

### Cleaning build files

```bash
make clean
```

## Usage Guide

### Main Menu Options

1. **Add New Task**: Create a new task with name, priority (1-10), deadline (days), and execution time
2. **Add Subtask to Existing Task**: Make an existing task a subtask of another
3. **Set Task Dependency**: Define that one task depends on another (must complete first)
4. **Choose Scheduling Strategy**: Select Priority, Deadline, or Hierarchical scheduler
5. **Display Task Hierarchy**: View all tasks in hierarchical tree format
6. **Execute All Tasks**: Run the scheduler and execute tasks in order
7. **View Execution Report**: Display execution statistics
8. **Exit**: Quit the application

### Example Workflow

1. Create task "Design Module" (priority=4, deadline=5, time=3)
2. Create task "Create Wireframes" (priority=3, deadline=3, time=2)
3. Add "Create Wireframes" as subtask of "Design Module"
4. Choose Hierarchical Scheduler
5. Display Task Hierarchy to verify structure
6. Execute All Tasks
7. View Execution Report

## Sample Scenarios

### Scenario A: Linear Dependency Chain

```
Task 1: Task A (priority=3, deadline=5)
Task 2: Task B (priority=2, deadline=6) depends on Task A
Scheduler: PriorityScheduler
Expected: A executes, then B
```

### Scenario B: Hierarchical with Dependencies

```
Task 1: Design (priority=4)
  ├─ Task 2: Wireframes (priority=3)
  └─ Task 3: UI Mockup (priority=2) depends on Wireframes
Task 4: Backend (priority=3) depends on Design
Scheduler: HierarchicalScheduler
Expected: Wireframes → UI Mockup → Design → Backend
```

## Error Handling

- **Invalid input**: Prompts user to re-enter valid values
- **Circular dependencies**: Detected using DFS; prevents execution
- **Missing dependencies**: Tasks wait until dependencies are completed
- **Non-existent task IDs**: Validated before operations

## Educational Notes

This project is designed for educational purposes to demonstrate OOP concepts in C++. Key learning points:

- **Class design**: Separation of concerns, single responsibility
- **Smart pointers**: Using `unique_ptr` for automatic memory management
- **STL containers**: `vector`, `map`, `set` for data structures
- **Design patterns**: Strategy pattern (schedulers), Composite pattern (task hierarchy)
- **Const correctness**: Proper use of `const` methods and parameters
- **Header guards**: Preventing multiple inclusion
- **Code organization**: Separating interface (.h) from implementation (.cpp)

## Limitations (By Design)

- In-memory only (no persistence)
- Single-threaded (no concurrency)
- Console-based interface (no GUI)
- Simulated execution (no real OS process management)
- ASCII-only output (educational clarity)

## Author

Created as an OOP semester project demonstrating hierarchical task scheduling concepts.

## License

Educational project - free to use and modify for learning purposes.
