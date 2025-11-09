# 1. INTRODUCTION

## Project Overview

The Hierarchical Task Scheduling Engine (HTSE) is a comprehensive C++ application designed to demonstrate advanced Object-Oriented Programming concepts through a practical task management system. The system implements intelligent task scheduling algorithms, hierarchical task relationships, dependency management, and progress tracking.

## Project Title

**Hierarchical Task Scheduling Engine (HTSE)**

## Team Members

| S.No | Name          | Role                | Responsibilities                                |
| ---- | ------------- | ------------------- | ----------------------------------------------- |
| 1    | Team Member 1 | Team Lead           | Architecture design, scheduler implementations  |
| 2    | Team Member 2 | Core Developer      | Task class, operator overloading implementation |
| 3    | Team Member 3 | Backend Developer   | TaskManager, dependency management              |
| 4    | Team Member 4 | Template Specialist | Generic programming, template utilities         |
| 5    | Team Member 5 | Testing Lead        | Test cases, execution framework                 |

## Objectives

### Primary Objectives

1. Demonstrate all seven fundamental OOP concepts in a single cohesive application
2. Implement a functional task scheduling system with multiple scheduling strategies
3. Provide interactive command-line interface for task management
4. Support hierarchical task structures with parent-child relationships
5. Handle task dependencies with circular dependency detection

### Secondary Objectives

1. Implement operator overloading for intuitive task manipulation
2. Utilize template programming for generic utility functions
3. Provide visual progress tracking during task execution
4. Support dual build modes for different feature demonstrations
5. Ensure clean compilation with zero warnings using strict compiler flags

## System Features

### Core Functionality

The system provides comprehensive task management capabilities including:

- Task creation with customizable priority, deadline, and execution time
- Hierarchical task organization with parent-child subtask relationships
- Task dependency management with automatic readiness verification
- Multiple scheduling strategies: Priority-based, Deadline-based, and Hierarchical
- Visual task execution with animated progress bars
- Detailed execution reports with statistics

### User Interaction

The application offers an interactive menu-driven interface with the following capabilities:

- Add new tasks with validated user input
- Establish subtask relationships between tasks
- Define task dependencies
- Switch between different scheduling algorithms
- Display task hierarchy in tree format
- Execute all tasks respecting dependencies
- View comprehensive execution reports
- Demonstrate operator overloading features
- Explore template-based generic programming utilities

## Technical Specifications

### Programming Language

C++17 Standard

### Compiler Requirements

- GCC/G++ 7.0 or higher
- Support for C++17 features
- Compiler flags: `-std=c++17 -Wall -Wextra -O2`

### Build Modes

The project supports two distinct build configurations:

**D2_MODE (Deadline 2 Mode):**

- Demonstrates 4 core OOP concepts
- Hides polymorphism and template features
- Focused on: Encapsulation, Abstraction, Inheritance, Operator Overloading
- Compile command: `g++ -std=c++17 -Wall -Wextra -O2 -DD2_MODE src/*.cpp -o htse.exe`

**Final Mode (Complete):**

- Demonstrates all 7 OOP concepts
- Full feature set including polymorphism and templates
- Includes advanced scheduling strategies and generic programming
- Compile command: `g++ -std=c++17 -Wall -Wextra -O2 src/*.cpp -o htse.exe`

### Project Statistics

- Total Source Files: 16
- Total Lines of Code: 1,865
- Implementation Files: 7 (.cpp)
- Header Files: 9 (.h)
- Classes Implemented: 8
- Abstract Interfaces: 1
- Template Classes: 3

## Development Environment

### Platform Compatibility

- Primary: Windows (tested with MinGW-w64)
- Secondary: Linux (GCC), macOS (Clang)
- Terminal: Bash shell recommended

### External Dependencies

The project uses only C++ Standard Library with no external dependencies:

- iostream - Input/output operations
- vector - Dynamic array containers
- string - String manipulation
- memory - Smart pointers (unique_ptr)
- algorithm - Sorting algorithms
- map - Associative containers
- set - Set containers
- iomanip - Output formatting
- windows.h - Sleep function for execution simulation (Windows only)

### Color Support

The application implements ANSI color codes for enhanced terminal output:

- Cyan: Headers and section titles
- Green: Success messages and completed tasks
- Yellow: Warnings and menu highlights
- Red: Error messages
- Blue: Running task status
- Magenta: Execution progress headers

Color support can be disabled through the ENABLE_COLOR flag in config.h.

## Problem Statement

Traditional task management systems lack comprehensive demonstration of OOP principles in a single application. This project addresses the need for:

1. A practical application showcasing all fundamental OOP concepts
2. Real-world implementation of design patterns (Strategy Pattern for schedulers)
3. Demonstration of generic programming through templates
4. Handling complex relationships (hierarchies and dependencies)
5. Educational tool for understanding OOP in action

## Scope

### In Scope

1. Task creation, modification, and deletion capabilities
2. Hierarchical task organization with unlimited nesting levels
3. Dependency management with cycle detection
4. Three scheduling algorithms with runtime selection
5. Visual execution tracking with progress indicators
6. Statistical analysis using template functions
7. Operator overloading for task comparison and manipulation
8. Comprehensive error handling and input validation

### Out of Scope

1. Persistent storage (database or file system)
2. Multi-user support or authentication
3. Network communication or distributed scheduling
4. Graphical user interface (GUI)
5. Real-time task execution on actual system processes
6. Integration with external task management tools

## Expected Outcomes

Upon project completion, the system will:

1. Successfully demonstrate all seven OOP concepts in working code
2. Compile without warnings in both D2_MODE and Final mode
3. Handle edge cases gracefully (empty lists, circular dependencies, invalid input)
4. Provide intuitive user interface for task management
5. Execute tasks in correct order based on dependencies and scheduling strategy
6. Generate comprehensive reports with execution statistics
7. Serve as educational reference for OOP concepts in C++
