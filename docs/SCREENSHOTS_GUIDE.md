# Output Screenshots Guide - HTSE

## Instructions for Capturing Program Screenshots

To demonstrate the complete functionality of the Hierarchical Task Scheduling Engine, capture the following screenshots during program execution.

---

## Required Screenshots

### Screenshot 1: Main Menu

**Label**: "Main Menu - Program Startup"

**What to show**:

- Program title banner
- All 8 menu options displayed
- User prompt for input

**How to capture**:

1. Run the program: `./htse`
2. Wait for main menu to display
3. Take screenshot

**Expected Output**:

```
+============================================================+
|     HIERARCHICAL TASK SCHEDULING ENGINE (HTSE)            |
|                    [OOP Project Demo]                     |
+============================================================+

+-----------------------------------------------+
| [1] >> Add New Task                          |
| [2] >> Add Subtask to Existing Task          |
| [3] >> Set Task Dependency                   |
| [4] >> Choose Scheduling Strategy            |
| [5] >> Display Task Hierarchy                |
| [6] >> Execute All Tasks                     |
| [7] >> View Execution Report                 |
| [0] >> Exit                                  |
+-----------------------------------------------+

Your choice:
```

---

### Screenshot 2: Creating Tasks

**Label**: "Task Creation Process"

**What to show**:

- Input prompts for task details
- Validation messages
- Success confirmation

**How to capture**:

1. Select option `1` (Add New Task)
2. Enter task details:
   - Name: "Database Design"
   - Priority: 8
   - Deadline: 10
   - Time: 5
3. Capture success message

**Expected Output**:

```
--- Add New Task ---

Task Name: Database Design
Priority (1-10): 8
Deadline (days): 10
Estimated Execution Time (units): 5

[SUCCESS] Task created!
  ID: 1 | Name: "Database Design"
  Priority: 8 | Deadline: 10d | Time: 5u
```

---

### Screenshot 3: Task Hierarchy Display

**Label**: "Hierarchical Task Structure"

**What to show**:

- Tree-style task hierarchy
- Color-coded status indicators
- Parent-child relationships
- Task properties (priority, deadline, status)

**Setup**:

1. Create multiple tasks with subtask relationships
2. Select option `5` (Display Task Hierarchy)

**Example Structure**:

```
Task 1: Project (Priority=9)
  Task 2: Backend (Priority=8)
    Task 3: Database (Priority=7)
  Task 4: Frontend (Priority=6)
```

**Expected Output**:

```
--- Task Hierarchy ---

[*] Task 1: Project [P=9, D=30d, PENDING]
 |-- Task 2: Backend [P=8, D=20d, PENDING]
 |   +-- Task 3: Database [P=7, D=10d, PENDING]
 |-- Task 4: Frontend [P=6, D=15d, PENDING]
```

---

### Screenshot 4: Scheduling Strategy Selection

**Label**: "Choosing Scheduling Algorithm"

**What to show**:

- Available scheduler options
- User selection
- Confirmation message

**How to capture**:

1. Select option `4` (Choose Scheduling Strategy)
2. View available options
3. Select a scheduler (e.g., Priority)

**Expected Output**:

```
--- Choose Scheduling Strategy ---

Available Schedulers:
  1. Priority Scheduler (Schedule by priority - highest first)
  2. Deadline Scheduler (Schedule by deadline - earliest first)
  3. Hierarchical Scheduler (Parents before children)

Select scheduler (1-3): 1

[SUCCESS] Scheduler set to: PriorityScheduler
```

---

### Screenshot 5: Task Execution with Progress

**Label**: "Task Execution in Progress"

**What to show**:

- Execution header
- Tasks in RUNNING state (blue color)
- Progress animation bars
- Completion messages (green color)

**How to capture**:

1. Set up some tasks
2. Select option `6` (Execute All Tasks)
3. Capture during/after execution

**Expected Output**:

```
+============================================+
|        TASK EXECUTION IN PROGRESS         |
+============================================+

Using Scheduler: PriorityScheduler

[~] RUNNING: Task 3 - Database Design (P=8, D=10d)
    Progress: [======] 100%
[+] COMPLETED: Task 3 - Database Design (P=8, D=10d)

[~] RUNNING: Task 2 - API Development (P=7, D=5d)
    Progress: [====] 100%
[+] COMPLETED: Task 2 - API Development (P=7, D=5d)

[~] RUNNING: Task 1 - Testing (P=5, D=3d)
    Progress: [===] 100%
[+] COMPLETED: Task 1 - Testing (P=5, D=3d)

All tasks executed successfully!
```

---

### Screenshot 6: Execution Report

**Label**: "Execution Summary Report"

**What to show**:

- Statistics (total tasks, completed, time)
- Scheduler used
- Professional formatting

**How to capture**:

1. After executing tasks
2. Select option `7` (View Execution Report)

**Expected Output**:

```
+============================================+
|          EXECUTION SUMMARY REPORT         |
+============================================+

Last Scheduler Used: PriorityScheduler
Total Tasks Completed: 3
Total Simulated Time: 12 time units

Task Completion Status:
  ✓ All tasks completed successfully
```

---

### Screenshot 7: Dependency Handling

**Label**: "Task Dependencies and Multi-Pass Execution"

**What to show**:

- Tasks waiting for dependencies
- Multi-pass execution
- Dependency resolution

**Setup**:

1. Create Task A
2. Create Task B with dependency on A
3. Execute all tasks

**Expected Output**:

```
+============================================+
|        TASK EXECUTION IN PROGRESS         |
+============================================+

Pass 1/10:
[~] RUNNING: Task 1 - Requirements (P=8, D=10d)
    Progress: [===] 100%
[+] COMPLETED: Task 1 - Requirements

[!] Task 2 - Implementation (P=9, D=5d) - Dependencies not met
    Waiting for: Task 1

Pass 2/10:
[~] RUNNING: Task 2 - Implementation (P=9, D=5d)
    Progress: [====] 100%
[+] COMPLETED: Task 2 - Implementation

All tasks executed successfully!
```

---

### Screenshot 8: Error Handling - Circular Dependencies

**Label**: "Circular Dependency Detection"

**What to show**:

- Error message for circular dependencies
- List of tasks in cycle
- Execution prevented

**Setup**:

1. Create Task A depends on Task B
2. Create Task B depends on Task A
3. Try to execute

**Expected Output**:

```
[!] ERROR: Circular dependency detected!

Cannot execute tasks due to dependency cycle.
Please review task dependencies and remove circular references.

Affected tasks may include:
  - Task 1: Design
  - Task 2: Implementation

Execution aborted.
```

---

### Screenshot 9: Different Scheduler Comparison

**Label**: "Priority vs Deadline Scheduler Comparison"

**What to show**:

- Same tasks executed with different schedulers
- Different execution orders

**Setup**:
Create tasks:

- Task 1: Priority=5, Deadline=3
- Task 2: Priority=8, Deadline=10
- Task 3: Priority=6, Deadline=5

Execute with Priority Scheduler, then Deadline Scheduler

**Priority Scheduler Output**:

```
Execution Order:
  1. Task 2 (Priority=8)
  2. Task 3 (Priority=6)
  3. Task 1 (Priority=5)
```

**Deadline Scheduler Output**:

```
Execution Order:
  1. Task 1 (Deadline=3)
  2. Task 3 (Deadline=5)
  3. Task 2 (Deadline=10)
```

---

### Screenshot 10: Program Exit

**Label**: "Clean Program Termination"

**What to show**:

- Exit message
- Professional goodbye banner

**How to capture**:

1. Select option `0` (Exit)

**Expected Output**:

```
+============================================+
|  Thank you for using HTSE!                |
|  Goodbye!                                  |
+============================================+

Exiting program...
```

---

## Screenshot Formatting Guidelines

### File Naming Convention

```
screenshot_01_main_menu.png
screenshot_02_task_creation.png
screenshot_03_task_hierarchy.png
screenshot_04_scheduler_selection.png
screenshot_05_execution_progress.png
screenshot_06_execution_report.png
screenshot_07_dependency_handling.png
screenshot_08_circular_dependency_error.png
screenshot_09_scheduler_comparison.png
screenshot_10_program_exit.png
```

### Technical Requirements

- **Format**: PNG or JPG
- **Resolution**: Minimum 1280x720
- **Terminal Settings**:
  - Font: Monospace (Consolas, Courier New)
  - Font Size: 12-14pt
  - Background: Dark (recommended for ANSI colors)
- **Cropping**: Include only terminal window content
- **Labels**: Add clear captions below each screenshot

### Color Display

Ensure your terminal supports ANSI colors:

- Windows: Use Windows Terminal or enable VT100 support
- Linux/Mac: Most terminals support colors by default

---

## Complete Test Scenario Script

For comprehensive demonstration, follow this sequence:

```bash
# Run the program
./htse

# Test Scenario 1: Basic Task Management
1 → "Database Design" → 8 → 10 → 5
1 → "API Development" → 7 → 5 → 4
1 → "Frontend UI" → 6 → 8 → 3
5 → (View hierarchy)

# Test Scenario 2: Hierarchical Structure
1 → "Project" → 9 → 30 → 10
1 → "Backend" → 8 → 20 → 8
2 → 1 → 2 (Add Backend as subtask of Project)
5 → (View hierarchy)

# Test Scenario 3: Dependencies
3 → 2 → 1 (Backend depends on Database Design)
6 → (Execute - see multi-pass)

# Test Scenario 4: Different Schedulers
4 → 1 (Priority)
6 → (Execute)
7 → (View report)

4 → 2 (Deadline)
6 → (Execute)

# Test Scenario 5: Error Handling
# (Create circular dependency and try to execute)

0 → (Exit)
```

---

## Submission Checklist

- [ ] All 10 screenshots captured
- [ ] Screenshots clearly labeled
- [ ] Terminal output is readable
- [ ] Colors are visible (if using colored terminal)
- [ ] File names follow convention
- [ ] Screenshots organized in `screenshots/` folder
- [ ] README includes screenshot descriptions

---

_This guide ensures complete documentation of program functionality for academic submission._
