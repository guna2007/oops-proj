# Project Metadata

Project Name: Hierarchical Task Scheduling Engine (HTSE)
Type: OOP Semester Project
Primary Language: C++
Complexity Level: Medium (Educational Demonstration Project)
Primary Goal: Demonstrate OOP principles through an in-memory task scheduling simulation
Focus: Hierarchical Tasks, Scheduling Algorithms, CLI Interface
Storage: In-memory only (no file or database persistence)
Target Output: Console-based, structured ASCII output with clear task hierarchy visualization

# Project Overview

The Hierarchical Task Scheduling Engine (HTSE) is a console-based simulation system that models task management and scheduling using core object-oriented programming (OOP) principles in C++. The system allows users to:

- Create tasks and nested subtasks (hierarchical structure).
- Define dependencies between tasks (a task may require other tasks to finish first).
- Assign priority and deadline attributes to tasks.
- Choose between multiple scheduling strategies at runtime.
- Simulate execution of tasks and produce a readable console report.

The goal is to simulate scheduling logic and to highlight OOP design patterns and concepts in a clear academic project. The project is not intended to manage real OS-level processes or use persistent storage.

# Core Objectives

1. Apply OOP design principles: Encapsulation, Inheritance, Abstraction, and Polymorphism.
2. Implement a hierarchical structure of tasks (parent-child relationships).
3. Provide multiple scheduling strategies and allow strategy selection at runtime.
4. Provide a clear, interactive CLI interface and structured ASCII console output.
5. Keep all data in memory; no persistence required.

# Functional Requirements

1. Allow creation of Task objects with attributes: id, name, priority, deadline, status.
2. Each Task can contain a list of subtasks (Task objects) to form a hierarchy.
3. Tasks can have dependencies on other tasks; a task cannot execute until all dependencies are completed.
4. Support three scheduling strategies:

   - Priority-based scheduling
   - Deadline-based scheduling
   - Hierarchical scheduling (parent before children)

5. Allow the user to select the desired scheduler at runtime.
6. Simulate task execution, updating and printing status changes.
7. Provide a CLI menu to add tasks, add subtasks, set dependencies, choose scheduler, display hierarchy, execute tasks, and view the report.
8. Provide a summary report after execution.
9. All data stored in program memory (no files, no databases).
10. Document explicitly how each class maps to OOP concepts.

# Non-Functional Requirements

- Code must be modular and easily extendable.
- Console output must be neat, plain ASCII-only, and easy to read.
- Hierarchical printing must be implemented with recursion but limited depth (recommended max 3-4 levels in UI examples).
- Implementation should favor clarity for education; do not use advanced concurrency or OS features.
- Include comments that explain which OOP concept each class or method demonstrates.
- Provide simple unit-test style examples in the report (optional but recommended).

# Class Design Summary

Use the following classes and structure. Each class should be in its own header and source file when possible.

Class: Task

- Responsibility: Base unit of work.
- Key Attributes: int id, string name, int priority, int deadline, enum status {PENDING, RUNNING, COMPLETED}, vector<Task*> subtasks, vector<Task*> dependencies, int estimated_time (simulated).
- Key Methods:

  - Task(int id, const string &name, int priority, int deadline, int time)
  - void addSubtask(Task\* t)
  - void addDependency(Task\* t)
  - bool isReady() const // returns true if all dependencies are COMPLETED
  - void execute() // simulate run and set status
  - void markComplete()
  - void displayInfo(int indent) const

- OOP Concept: Encapsulation, Composition

Class: HierarchicalTask (optional; can reuse Task with methods)

- Responsibility: Additional utility methods for tree operations.
- Inherits: Task
- Extra Methods:

  - int getTotalSubtasks() const
  - void displayHierarchy(int indent) const

- OOP Concept: Inheritance, Recursion

Class: Scheduler (abstract - interface)

- Responsibility: Define scheduling behavior.
- Key Methods:

  - virtual vector<Task*> schedule(const vector<Task*> &tasks) = 0

- OOP Concept: Abstraction, Polymorphism

Class: PriorityScheduler

- Responsibility: Order tasks by descending priority (higher priority first).
- Inherits: Scheduler
- Methods:

  - vector<Task*> schedule(const vector<Task*> &tasks) override

- OOP Concept: Polymorphism

Class: DeadlineScheduler

- Responsibility: Order tasks by ascending deadline (earliest deadline first).
- Inherits: Scheduler
- Methods:

  - vector<Task*> schedule(const vector<Task*> &tasks) override

- OOP Concept: Polymorphism

Class: HierarchicalScheduler

- Responsibility: Schedule by hierarchy: ensure parent tasks are scheduled before children, while respecting dependencies.
- Inherits: Scheduler
- Methods:

  - vector<Task*> schedule(const vector<Task*> &tasks) override

- OOP Concept: Polymorphism, use of recursion/tree traversal

Class: TaskExecutor

- Responsibility: Simulate executing an ordered list of tasks.
- Attributes: reference to logger or output stream (use std::ostream &)
- Methods:

  - void runTasks(const vector<Task\*> &ordered_tasks)
  - void simulateWork(int time_units) // e.g., sleep for demonstration (use std::this_thread::sleep_for if used; but keep optional)

- OOP Concept: Composition

Class: TaskManager

- Responsibility: High-level coordination, CLI interface, maintain task list and current scheduler.
- Attributes: vector<Task\*> all_tasks, unique_ptr<Scheduler> current_scheduler
- Methods:

  - Task\* createTask(const string &name, int priority, int deadline, int time)
  - void addSubtask(int parent_id, int subtask_id)
  - void addDependency(int task_id, int dependency_id)
  - void setScheduler(unique_ptr<Scheduler> sched)
  - void executeAll()
  - void displayTaskHierarchy() const
  - void printSummaryReport() const

- OOP Concept: Encapsulation, Composition

# System Flow (Execution Steps)

1. Program starts and creates a TaskManager instance.
2. The CLI displays the main menu and accepts user input.
3. User creates tasks and subtasks; the TaskManager stores pointers to Task objects in a list.
4. User assigns dependencies by referencing task IDs. Task objects maintain pointers to dependency tasks.
5. User selects a scheduling strategy. TaskManager sets the current scheduler to an instance of the selected scheduler (via polymorphism).
6. User requests execution. TaskManager asks the Scheduler to produce an ordered list of tasks.
7. TaskExecutor iterates over the ordered list:

   - Before executing a task, check Task::isReady() to ensure dependencies are completed. If not ready, skip or handle according to scheduler logic (document this behavior).
   - Call Task::execute() (simulated time) and Task::markComplete().
   - Print status to console for each step.

8. After all tasks are handled, TaskManager prints a summary report.

# CLI Menu Design

All console text must be ASCII-only.

Main Menu:

```
1. Add New Task
2. Add Subtask to Existing Task
3. Set Task Dependency
4. Choose Scheduling Strategy
5. Display Task Hierarchy
6. Execute All Tasks
7. View Execution Report
0. Exit
Enter your choice:
```

Add Task Flow:

```
Enter Task Name:
Enter Priority (1-10, 10 highest):
Enter Deadline (integer days from now):
Enter Estimated Execution Time (units):
Task [<name>] added with ID <id>
```

Add Subtask Flow:

```
Enter Parent Task ID:
Enter Subtask ID:
Subtask <subtask_id> added under Parent <parent_id>
```

Set Dependency Flow:

```
Enter Task ID:
Enter Dependency Task ID:
Dependency added: Task <task_id> depends on <dependency_id>
```

Choose Scheduler Flow:

```
Select Scheduling Strategy:
1. Priority Based
2. Deadline Based
3. Hierarchical
Enter your choice:
[SchedulerName] selected
```

Execute All Flow:

- Print header lines with ASCII dividers.
- For each task attempt:

  - Print "RUNNING: Task <id> : <name> (priority=<p>, deadline=<d>)"
  - If has subtasks, print their execution lines indented by two spaces per level.
  - After completion print "COMPLETED: Task <id>"

- At end print "ALL TASKS COMPLETED" or a message about skipped tasks.

# Console Output Guidelines

- Use only ASCII characters.
- Use simple dividers such as:

  - "========================================"
  - "----------------------------------------"

- Use words for status markers:

  - "RUNNING", "COMPLETED", "SKIPPED", "NOT READY"

- Indent subtasks with two spaces per hierarchy level.
- Do not use Unicode arrows, box characters, emojis, or special symbols outside basic ASCII.
- Example:

```
========================================
HIERARCHICAL TASK SCHEDULING ENGINE
========================================
RUNNING: Task 1 : Design Module (priority=4, deadline=5)
  RUNNING: Task 2 : Create Wireframes (priority=3, deadline=3)
  COMPLETED: Task 2 : Create Wireframes
COMPLETED: Task 1 : Design Module
----------------------------------------
EXECUTION REPORT
Total Tasks: 3
Total Subtasks: 1
Completed: 4 / 4
Scheduler Used: PriorityScheduler
Simulated Execution Time: 6 units
========================================
```

# OOP Concepts Mapping

- Encapsulation: Task attributes should be private or protected; expose getters/setters for needed access. Status and dependency lists should be manipulated through methods, not directly.
- Inheritance: If HierarchicalTask is implemented, it should derive from Task and add tree utilities.
- Abstraction: Scheduler is an abstract base class that defines the scheduling interface.
- Polymorphism: Implement multiple scheduler classes inheriting from Scheduler and override schedule().
- Composition: TaskManager contains collections of Task objects and a Scheduler pointer.
- Aggregation: Tasks refer to other tasks as dependencies (not ownership).
- Recursion: Use in displayHierarchy and in HierarchicalScheduler traversals.

# Scheduling Behavior Rules (specify clearly)

- PriorityScheduler:

  - Consider only tasks that are ready (isReady()) or optionally schedule all and skip not ready at runtime. Define chosen behavior in comments. Recommended: schedule all tasks sorted by priority but TaskExecutor must check isReady() before executing; if not ready, postpone to end of current pass and try again until no progress can be made.

- DeadlineScheduler:

  - Sort by numeric deadline ascending. Similar runtime readiness policy as PriorityScheduler.

- HierarchicalScheduler:

  - Prefer parent tasks before children when possible. Also respect explicit dependencies across branches.

- Dependency Enforcement:

  - A task's isReady returns true only if all dependency tasks have status COMPLETED.
  - If a dependency cycle is detected, report the cycle and do not attempt execution for tasks in the cycle.

# Error Handling and Edge Cases (academic emphasis)

- Detect cycles in dependencies using DFS; print a clear message showing the cycle by task ids.
- If a task depends on a non-existing id, do not crash; print an error and ignore the dependency.
- If a task is not ready at execution time and no progress can be made in an iteration, report remaining tasks as "NOT READY" and stop execution.
- Validate user input in CLI; for invalid values print error messages and prompt again.

# Implementation Roadmap (step-by-step, minimal ambiguity)

1. Create the Task class with private attributes, constructor, getters/setters, addSubtask, addDependency, isReady, execute (simulation only), markComplete, displayInfo.
2. Option A: Implement HierarchicalTask as subclass for display helpers; Option B: implement hierarchy methods within Task. Use whichever is clearer for your design but document which you chose.
3. Implement the Scheduler abstract class with virtual schedule().
4. Implement PriorityScheduler, DeadlineScheduler, HierarchicalScheduler; each returns a vector<Task\*> ordered according to policy.
5. Implement TaskExecutor to run tasks in the order provided. Executor must check isReady() before executing a task; if not ready, it should postpone execution and attempt a finite number of passes until no progress; then report problems.
6. Implement TaskManager to maintain tasks, map ids to Task pointers, and provide the CLI. TaskManager will own created Task objects and clean them up (use smart pointers preferred).
7. Implement cycle detection for dependencies and provide clear error messages.
8. Provide a main.cpp that instantiates TaskManager and runs the CLI loop.
9. Add inline comments mapping each class/method to the OOP concept it demonstrates.
10. Test with sample data and prepare console screenshots.

# Testing and Sample Data

Provide at least two testing scenarios:

Scenario A: Simple linear set

- Task 1: A (priority 3, deadline 5)
- Task 2: B (priority 2, deadline 6) depends on A
- Scheduler: PriorityScheduler
  Expected: A runs then B.

Scenario B: Hierarchy and dependency

- Task 1: Design (priority 4)

  - Subtask 2: Wireframes (priority 3)
  - Subtask 3: UI Mockup (priority 2) depends on Wireframes

- Task 4: Backend (priority 3) depends on Design
- Scheduler: HierarchicalScheduler
  Expected: Wireframes then UI Mockup then Design then Backend.

# Deliverables (for grading)

- Source code in C++ (separate headers and sources; clean project structure). Use C++17 or later.
- UML Class Diagram (image file included in project/docs).
- Flowchart of Execution (image file included in project/docs).
- Console output screenshots demonstrating scenarios and scheduler behaviors.
- A short written report explaining which OOP concept is used where and design reasoning.

# Code Style and Best Practices (academic)

- Use classes, private members, and public interfaces. Prefer smart pointers (std::unique_ptr or std::shared_ptr) for ownership where appropriate.
- Keep methods short and single-responsibility.
- Comment methods with a short note mapping to OOP concepts.
- Use standard library containers (vector, map) for storage.
- Avoid multithreading and advanced OS APIs; focus on clean OOP demonstration.

# AI Usage Notes (for agentic agents)

- Follow the class structure in this document precisely. Do not skip implementing the Scheduler abstraction and at least the three concrete schedulers.
- Generate code that is educational and readable rather than production-optimized. Favor clarity and comments that map to OOP concepts.
- Keep all I/O to standard console (std::cout, std::cin). Avoid file I/O or networking.
- If code generation is requested, produce header files (.h/.hpp), source files (.cpp), and a main.cpp that compiles with a standard C++ compiler (g++ or clang++).
- Include a minimal Makefile or compile instructions in README (g++ -std=c++17 main.cpp task.cpp scheduler.cpp ... -o htse).

# Example Minimal File Layout

project_root/
src/
task.h
task.cpp
scheduler.h
priority_scheduler.cpp
deadline_scheduler.cpp
hierarchical_scheduler.cpp
task_executor.h
task_executor.cpp
task_manager.h
task_manager.cpp
main.cpp
docs/
instructions.md <-- this file
UML_ClassDiagram.png
Flowchart.png
README.md

# Final Notes

- This instructions.md is intended to be unambiguous and complete for an academic implementation in C++ focusing on OOP concepts.
- All console output examples use plain ASCII only.
- When implementing, explicitly document which OOP concept each class or method demonstrates; this is important for grading.
