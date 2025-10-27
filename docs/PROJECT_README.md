# Hierarchical Task Scheduling Engine (HTSE)

## Object-Oriented Programming Semester Project

---

## 1. Project Title and Objective

### Title

**Hierarchical Task Scheduling Engine (HTSE)**

### Objective

To design and implement a task scheduling and management system in C++ that demonstrates comprehensive understanding of Object-Oriented Programming (OOP) principles including:

- Encapsulation
- Inheritance
- Polymorphism
- Abstraction
- Composition
- Recursion

The system simulates real-world task scheduling scenarios with support for hierarchical task structures, dependency management, and multiple scheduling algorithms.

---

## 2. System Specifications

### Hardware Requirements

- **Processor**: Any modern x86/x64 processor
- **RAM**: Minimum 512 MB
- **Storage**: 10 MB free space

### Software Requirements

- **Operating System**: Windows 10/11, Linux, or macOS
- **Compiler**: g++ (GCC 6.3.0 or higher) with C++17 support
- **Build Tools**: Make (optional)
- **Terminal**: Any terminal supporting ANSI escape codes for colored output

### Development Environment

- **Language**: C++ (Standard: C++17)
- **Paradigm**: Object-Oriented Programming
- **Build System**: Makefile / Manual compilation
- **Libraries**: C++ Standard Library only (no external dependencies)

---

## 3. Incorporated OOP Concepts

### 3.1 Encapsulation

**Definition**: Bundling data and methods within a class while restricting direct access to internal state.

**Implementation**:

- **Task Class**: All attributes (id, name, priority, deadline, status) are private with public getter/setter methods
- **TaskManager Class**: Internal data structures (task lists, maps) are private, exposed only through controlled methods
- **TaskExecutor Class**: Execution logic encapsulated within the class

**Files**: `task.h`, `task.cpp`, `task_manager.h`, `task_manager.cpp`

### 3.2 Inheritance

**Definition**: Creating new classes (derived) from existing classes (base) to promote code reuse.

**Implementation**:

- **Base Class**: `Scheduler` (abstract)
- **Derived Classes**:
  - `PriorityScheduler` - Inherits from Scheduler
  - `DeadlineScheduler` - Inherits from Scheduler
  - `HierarchicalScheduler` - Inherits from Scheduler

**Files**: `scheduler.h`, `priority_scheduler.h/.cpp`, `deadline_scheduler.h/.cpp`, `hierarchical_scheduler.h/.cpp`

### 3.3 Polymorphism

**Definition**: Ability to process objects differently based on their data type or class, typically through virtual functions.

**Implementation**:

- Virtual methods `schedule()` and `getName()` in base `Scheduler` class
- Runtime polymorphism: TaskManager uses base class pointer to call scheduler methods
- Actual behavior determined at runtime based on selected scheduler type

**Files**: All scheduler files, `task_manager.cpp` (uses polymorphic scheduler pointer)

### 3.4 Abstraction

**Definition**: Hiding complex implementation details and showing only essential features.

**Implementation**:

- **Scheduler**: Abstract base class with pure virtual functions defines interface contract
- **High-level methods**: `TaskManager::run()`, `executeAll()` abstract complex logic
- Users interact with simple interfaces without knowing internal algorithms

**Files**: `scheduler.h`, `task_manager.cpp`

### 3.5 Composition

**Definition**: "Has-a" relationship where objects contain other objects.

**Implementation**:

- **Task has subtasks**: `vector<Task*>` represents parent-child relationships
- **Task has dependencies**: `vector<Task*>` represents prerequisite tasks
- **TaskManager owns Tasks**: `vector<unique_ptr<Task>>` demonstrates ownership
- **TaskExecutor has output stream**: `ostream&` composition

**Files**: `task.h`, `task_manager.h`, `task_executor.h`

### 3.6 Recursion

**Definition**: Method calling itself to solve problems with hierarchical structure.

**Implementation**:

- **Hierarchy Display**: `Task::displayHierarchy()` recursively displays task tree
- **Subtask Execution**: `TaskExecutor::executeTaskWithSubtasks()` uses recursion
- **Cycle Detection**: `TaskManager::detectCycle()` uses recursive Depth-First Search
- **Hierarchical Scheduling**: `HierarchicalScheduler::collectTasksInOrder()` traverses tree recursively

**Files**: `task.cpp`, `task_executor.cpp`, `task_manager.cpp`, `hierarchical_scheduler.cpp`

---

## 4. Design and Working Details

### 4.1 System Architecture

```
┌─────────────────────────────────────────────┐
│              User Interface                  │
│           (Interactive CLI Menu)             │
└──────────────────┬──────────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────────┐
│            TaskManager                       │
│  • Central coordinator                       │
│  • Manages all tasks                         │
│  • Handles user input                        │
│  • Controls execution flow                   │
└────┬──────────┬──────────┬──────────────────┘
     │          │          │
     ▼          ▼          ▼
┌────────┐ ┌─────────┐ ┌──────────────┐
│  Task  │ │Scheduler│ │TaskExecutor  │
│Objects │ │Strategy │ │              │
└────────┘ └─────────┘ └──────────────┘
```

### 4.2 Class Structure

**Core Classes**:

1. **Task**: Represents individual task with properties and behavior
2. **Scheduler** (Abstract): Defines scheduling interface
3. **PriorityScheduler**: Schedules by priority (highest first)
4. **DeadlineScheduler**: Schedules by deadline (earliest first)
5. **HierarchicalScheduler**: Schedules parent tasks before children
6. **TaskExecutor**: Handles task execution simulation
7. **TaskManager**: Main coordinator managing all components
8. **Main**: Entry point of application

### 4.3 Key Features

**Task Management**:

- Create tasks with name, priority (1-10), deadline (days), execution time
- Build hierarchical structures (parent-child relationships)
- Define dependencies (prerequisite tasks)
- View task hierarchy in tree format

**Scheduling Algorithms**:

1. **Priority Scheduler**: Orders tasks by priority level (10 → 1)
2. **Deadline Scheduler**: Orders tasks by deadline (earliest first)
3. **Hierarchical Scheduler**: Ensures parent tasks execute before children

**Execution Features**:

- Multi-pass dependency resolution
- Circular dependency detection (prevents deadlocks)
- Simulated execution with time delays
- Real-time progress visualization with progress bars
- Color-coded status indicators

**User Interface**:

- Interactive menu-driven CLI
- ANSI color-coded output (green=success, red=error, yellow=warning, blue=running)
- ASCII box borders for visual clarity
- Tree-style hierarchy display
- Execution summary reports

### 4.4 Working Flow

**1. Task Creation**:

```
User Input → Validation → Create Task Object → Store in Manager
```

**2. Relationship Building**:

```
Select Parent → Select Child → Create Link → Update Structure
```

**3. Scheduling**:

```
Collect All Tasks → Apply Selected Algorithm → Return Ordered List
```

**4. Execution**:

```
Check Dependencies → Execute Ready Tasks → Mark Complete → Repeat
```

### 4.5 Dependency Resolution

The system uses a multi-pass execution algorithm:

- **Pass 1**: Execute tasks with no dependencies
- **Pass 2**: Execute tasks whose dependencies completed in Pass 1
- **Pass N**: Continue until all tasks complete or no progress possible

### 4.6 Circular Dependency Detection

Uses Depth-First Search (DFS) algorithm with recursion stack:

- Detects cycles in dependency graph before execution
- Prevents infinite loops and deadlock situations
- Alerts user if circular dependencies exist

---

## 5. Project Structure

```
OOPs-Proj/
├── src/                                    # Source code files
│   ├── task.h / task.cpp                   # Task entity class
│   ├── scheduler.h                         # Abstract scheduler base
│   ├── priority_scheduler.h / .cpp         # Priority algorithm
│   ├── deadline_scheduler.h / .cpp         # Deadline algorithm
│   ├── hierarchical_scheduler.h / .cpp     # Hierarchical algorithm
│   ├── task_executor.h / .cpp              # Execution engine
│   ├── task_manager.h / .cpp               # Main coordinator
│   └── main.cpp                            # Entry point
│
├── docs/                                   # Documentation
│   ├── FEATURES.md                         # Technical handbook
│   ├── CLASS_DIAGRAM.md                    # UML class diagrams
│   └── FLOWCHART.md                        # Execution flowcharts
│
├── README.md                               # This file
├── Makefile                                # Build configuration
└── cmds.txt                                # Build & test commands
```

---

## 6. Compilation and Execution

### Method 1: Using Makefile (Recommended)

```bash
# Compile the project
make

# Run the executable
make run

# Clean build files
make clean
```

### Method 2: Manual Compilation

```bash
# Compile all source files
g++ -std=c++17 -Wall -Wextra -O2 \
    src/main.cpp \
    src/task.cpp \
    src/priority_scheduler.cpp \
    src/deadline_scheduler.cpp \
    src/hierarchical_scheduler.cpp \
    src/task_executor.cpp \
    src/task_manager.cpp \
    -o htse

# Run the program
./htse
```

### Compilation Flags

- `-std=c++17`: Use C++17 standard
- `-Wall`: Enable all warnings
- `-Wextra`: Enable extra warnings
- `-O2`: Optimization level 2

---

## 7. Usage Instructions

### Main Menu Options

```
+============================================================+
|        HIERARCHICAL TASK SCHEDULING ENGINE (HTSE)         |
|                    [OOP Project Demo]                     |
+============================================================+

[1] Add New Task
[2] Add Subtask to Existing Task
[3] Set Task Dependency
[4] Choose Scheduling Strategy
[5] Display Task Hierarchy
[6] Execute All Tasks
[7] View Execution Report
[0] Exit
```

### Sample Workflow

**Step 1**: Create Tasks

```
Select: 1 (Add New Task)
Enter Name: "Database Design"
Enter Priority: 8
Enter Deadline: 10
Enter Time: 5
→ Task created with ID 1
```

**Step 2**: Build Hierarchy

```
Select: 2 (Add Subtask)
Parent Task ID: 1
Subtask Task ID: 2
→ Subtask relationship created
```

**Step 3**: Set Dependencies

```
Select: 3 (Set Dependency)
Task ID: 3
Depends on ID: 1
→ Dependency added
```

**Step 4**: Choose Scheduler

```
Select: 4 (Choose Strategy)
Options:
  1. Priority Scheduler
  2. Deadline Scheduler
  3. Hierarchical Scheduler
Choice: 1
→ Priority Scheduler selected
```

**Step 5**: Execute

```
Select: 6 (Execute All Tasks)
→ System checks dependencies
→ Applies scheduling algorithm
→ Executes tasks in order
→ Displays progress with animations
```

---

## 8. Example Scenarios

### Scenario 1: Priority-Based Scheduling

```
Tasks:
  Task 1: "Design" (Priority=8, Deadline=10d)
  Task 2: "Code" (Priority=5, Deadline=5d)
  Task 3: "Test" (Priority=9, Deadline=7d)

Scheduler: Priority
Execution Order: Task 3 → Task 1 → Task 2
```

### Scenario 2: Dependency Chain

```
Tasks:
  Task A: "Requirements"
  Task B: "Design" (depends on A)
  Task C: "Implementation" (depends on B)

Execution Order: A → B → C
```

### Scenario 3: Hierarchical Structure

```
Project (Task 1)
  ├── Backend (Task 2)
  │     ├── Database (Task 3)
  │     └── API (Task 4)
  └── Frontend (Task 5)

Hierarchical Order: Project → Backend → Database → API → Frontend
```

---

## 9. Visual Features

### Color Coding

- **Green**: Success messages, completed tasks
- **Yellow**: Warnings, pending tasks
- **Red**: Error messages
- **Blue**: Running tasks
- **Cyan**: Headers and borders
- **Purple**: Execution status

### Progress Animation

```
[~] RUNNING: Task 3 - Implementation
    Progress: [======] 100%
[+] COMPLETED: Task 3 - Implementation
```

### Tree Display

```
[*] Task 1: Project [P=9, D=30d, COMPLETED]
 |-- Task 2: Backend [P=8, D=20d, COMPLETED]
 |   +-- Task 3: Database [P=7, D=10d, COMPLETED]
```

---

## 10. Technical Details

### Memory Management

- Uses smart pointers (`unique_ptr`) for automatic memory management
- No manual memory allocation/deallocation required
- RAII (Resource Acquisition Is Initialization) principle

### Data Structures

- `vector`: Dynamic arrays for task lists
- `map`: Fast task lookup by ID
- `set`: Cycle detection visited tracking

### Algorithms

- **Sorting**: STL `sort()` with custom comparators
- **Graph Traversal**: Depth-First Search for cycle detection
- **Multi-pass**: Iterative dependency resolution

---

## 11. Error Handling

The system handles:

- **Invalid Input**: Prompts for re-entry
- **Circular Dependencies**: Detects and prevents execution
- **Missing Tasks**: Validates task IDs before operations
- **Incomplete Dependencies**: Defers execution until ready

---

## 12. Educational Value

This project demonstrates:
✅ Class design and separation of concerns  
✅ Abstract interfaces and concrete implementations  
✅ Runtime polymorphism through virtual functions  
✅ Smart pointer usage for memory safety  
✅ STL container utilization  
✅ Algorithm implementation (sorting, graph traversal)  
✅ Design patterns (Strategy, Composite)  
✅ Professional code organization

---

## 13. Future Enhancements

Potential improvements:

- Persistent storage (file I/O or database)
- Multi-threaded execution
- Graphical User Interface (GUI)
- Network-based distributed scheduling
- Real-time task monitoring dashboard
- Export reports to PDF/HTML

---

## 14. Conclusion

The Hierarchical Task Scheduling Engine successfully demonstrates all core OOP principles in a practical, real-world scenario. The project showcases professional software engineering practices including proper abstraction, modular design, and clean code organization.

---

## Author Information

**Project Type**: Academic Semester Project  
**Subject**: Object-Oriented Programming (OOP)  
**Language**: C++ (C++17 Standard)  
**Development Period**: October 2025

---

## License

Educational project - Free to use and modify for learning purposes.

---

**For detailed technical documentation, see `docs/FEATURES.md`**  
**For UML diagrams, see `docs/CLASS_DIAGRAM.md`**  
**For flowcharts, see `docs/FLOWCHART.md`**
