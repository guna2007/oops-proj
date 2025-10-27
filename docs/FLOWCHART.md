# HTSE Execution Flowchart (Text-Based)

## Main Program Flow

```
┌─────────────────┐
│  START: main()  │
└────────┬────────┘
         │
         ▼
┌─────────────────────────┐
│ Create TaskManager      │
└────────┬────────────────┘
         │
         ▼
┌─────────────────────────┐
│ Call manager.run()      │
│ (Enter CLI loop)        │
└────────┬────────────────┘
         │
         ▼
     ┌───────────────────┐
     │  Display Menu     │
     └────────┬──────────┘
              │
              ▼
     ┌───────────────────┐
     │  Wait for Input   │
     └────────┬──────────┘
              │
              ▼
     ┌───────────────────┐
     │  Process Choice   │──────┐
     └────────┬──────────┘      │
              │                 │
    ┌─────────┴──────┬──────────┴──────┬───────────┬─────────┐
    │                │                 │           │         │
    ▼                ▼                 ▼           ▼         ▼
┌────────┐   ┌────────────┐   ┌──────────┐  ┌──────────┐  ...
│  Add   │   │Add Subtask │   │   Set    │  │  Choose  │
│  Task  │   │            │   │Dependency│  │Scheduler │
└────┬───┘   └────┬───────┘   └────┬─────┘  └────┬─────┘
     │            │                 │             │
     └────────────┴─────────────────┴─────────────┘
                       │
                       ▼
              ┌───────────────────┐
              │   Choice = 0?     │────No───┐
              └────────┬──────────┘         │
                       │Yes                 │
                       ▼                    │
              ┌───────────────────┐         │
              │       EXIT        │         │
              └───────────────────┘         │
                                            │
                                            │
                    ┌───────────────────────┘
                    │
                    └──────▶ (Loop back to Display Menu)
```

## Task Creation Flow (Menu Option 1)

```
┌────────────────────┐
│  addNewTask()      │
└─────────┬──────────┘
          │
          ▼
┌─────────────────────┐
│  Prompt: Task Name  │
└─────────┬───────────┘
          │
          ▼
┌─────────────────────────┐
│  Prompt: Priority       │
│  Validate: 1-10         │
└─────────┬───────────────┘
          │
          ▼
┌─────────────────────────┐
│  Prompt: Deadline       │
│  Validate: >= 0         │
└─────────┬───────────────┘
          │
          ▼
┌─────────────────────────┐
│  Prompt: Time           │
│  Validate: > 0          │
└─────────┬───────────────┘
          │
          ▼
┌─────────────────────────┐
│  createTask(...)        │
│  - Create Task object   │
│  - Assign unique ID     │
│  - Store in all_tasks   │
│  - Store in task_map    │
└─────────┬───────────────┘
          │
          ▼
┌─────────────────────────┐
│  Display: "Task added   │
│           with ID X"    │
└─────────────────────────┘
```

## Task Execution Flow (Menu Option 6)

```
┌────────────────────────┐
│  executeAllTasks()     │
└─────────┬──────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Check: Any tasks exist?    │──No──▶ Display "No tasks"
└─────────┬───────────────────┘
          │Yes
          ▼
┌─────────────────────────────┐
│  Check: Scheduler selected? │──No──▶ Use default
└─────────┬───────────────────┘
          │Yes
          ▼
┌─────────────────────────────┐
│  hasCircularDependencies()? │──Yes─▶ Display Error
└─────────┬───────────────────┘       └──▶ ABORT
          │No
          ▼
┌─────────────────────────────┐
│  Call executeAll()          │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Collect all Task pointers  │
└─────────┬───────────────────┘
          │
          ▼
┌────────────────────────────────┐
│  Call scheduler->schedule()    │ ◀── Polymorphic call
└─────────┬──────────────────────┘
          │
          ▼
┌────────────────────────────────┐
│  Returns ordered task list     │
└─────────┬──────────────────────┘
          │
          ▼
┌────────────────────────────────┐
│  Call executor.runTasks()      │
└─────────┬──────────────────────┘
          │
          ▼
    [See Executor Flow]
          │
          ▼
┌────────────────────────────────┐
│  Update statistics             │
│  - completed_tasks             │
│  - total_simulated_time        │
└────────────────────────────────┘
```

## TaskExecutor.runTasks() Flow

```
┌─────────────────────────────┐
│  runTasks(ordered_tasks)    │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Print: "STARTING EXECUTION"│
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  remaining = ordered_tasks  │
│  pass = 0                   │
└─────────┬───────────────────┘
          │
          │  ◀───────────────────────┐ LOOP
          ▼                          │
┌─────────────────────────────┐     │
│  For each task in remaining │     │
└─────────┬───────────────────┘     │
          │                          │
          ▼                          │
┌─────────────────────────────┐     │
│  Check: task.isReady()?     │     │
└─────────┬───────┬───────────┘     │
          │Yes    │No               │
          │       │                 │
          │       ▼                 │
          │   ┌────────────────┐   │
          │   │ Add to deferred│   │
          │   └────────────────┘   │
          │                         │
          ▼                         │
┌───────────────────────────────┐  │
│  executeTaskWithSubtasks()    │  │
│  - Print RUNNING              │  │
│  - Execute subtasks (recurse) │  │
│  - Execute task               │  │
│  - Print COMPLETED            │  │
└───────────────────────────────┘  │
          │                         │
          ▼                         │
┌───────────────────────────────┐  │
│  Mark progress_made = true    │  │
└───────────────────────────────┘  │
          │                         │
          ▼                         │
┌───────────────────────────────┐  │
│  remaining = deferred         │  │
└─────────┬─────────────────────┘  │
          │                         │
          ▼                         │
┌───────────────────────────────┐  │
│  progress_made? AND           │  │
│  remaining not empty?         │──Yes─┘
└─────────┬─────────────────────┘
          │No
          ▼
┌───────────────────────────────┐
│  Any remaining tasks?         │
└─────────┬─────────┬───────────┘
          │No       │Yes
          │         │
          │         ▼
          │   ┌──────────────────────┐
          │   │ Print "NOT READY"    │
          │   │ for each remaining   │
          │   └──────────────────────┘
          │
          ▼
┌───────────────────────────────┐
│  Print completion message     │
└───────────────────────────────┘
```

## Scheduler Algorithm Flow (Polymorphic)

### Priority Scheduler

```
┌─────────────────────────────┐
│  schedule(tasks)            │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Copy task list             │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Sort by priority           │
│  (descending: 10 → 1)       │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Return sorted list         │
└─────────────────────────────┘
```

### Deadline Scheduler

```
┌─────────────────────────────┐
│  schedule(tasks)            │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Copy task list             │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Sort by deadline           │
│  (ascending: 1 → 10)        │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Return sorted list         │
└─────────────────────────────┘
```

### Hierarchical Scheduler

```
┌─────────────────────────────┐
│  schedule(tasks)            │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Identify root tasks        │
│  (not subtasks of others)   │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Sort roots by priority     │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  For each root task:        │
│    collectTasksInOrder()    │ ◀── Recursive DFS
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Return ordered list        │
│  (parents before children)  │
└─────────────────────────────┘
```

## Dependency Resolution Flow

```
┌─────────────────────────────┐
│  Task.isReady()             │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  For each dependency task:  │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  Check: dep.status ==       │
│         COMPLETED?          │
└─────────┬─────────┬─────────┘
          │No       │Yes
          │         │
          ▼         ▼
      ┌──────┐  ┌──────┐
      │Return│  │Continue
      │FALSE │  │checking│
      └──────┘  └────┬───┘
                     │
          ┌──────────┘
          │ (all checked)
          ▼
      ┌──────────┐
      │ Return   │
      │ TRUE     │
      └──────────┘
```

## Cycle Detection Flow

```
┌─────────────────────────────┐
│  detectCycle(task, visited, │
│              rec_stack)      │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  task in rec_stack?         │──Yes──▶ Return TRUE (cycle!)
└─────────┬───────────────────┘
          │No
          ▼
┌─────────────────────────────┐
│  task in visited?           │──Yes──▶ Return FALSE
└─────────┬───────────────────┘
          │No
          ▼
┌─────────────────────────────┐
│  Add to visited             │
│  Add to rec_stack           │
└─────────┬───────────────────┘
          │
          ▼
┌─────────────────────────────┐
│  For each dependency:       │
│    detectCycle(dep, ...)    │ ◀── Recursive
└─────────┬─────────┬─────────┘
          │         │
      Found│      All│clear
      cycle│         │
          │         ▼
          │    ┌─────────────────┐
          │    │ Remove from     │
          │    │ rec_stack       │
          │    └────────┬────────┘
          │             │
          │             ▼
          │    ┌─────────────────┐
          │    │ Return FALSE    │
          │    └─────────────────┘
          │
          ▼
┌─────────────────────┐
│  Return TRUE        │
└─────────────────────┘
```

## Complete User Session Example

```
START
  │
  ▼
Create TaskManager ─┐
  │                 │
  ▼                 │
Display Menu        │
  │                 │
  ▼                 │
User: "1"           │ ← Add Task
  │                 │
  ▼                 │
Enter: "Design"     │
Enter: 4            │
Enter: 10           │
Enter: 3            │
  │                 │
  ▼                 │
Task created (ID=1) │
  │                 │
  ▼                 │
Display Menu        │
  │                 │
  ▼                 │
User: "1"           │ ← Add Task
  │                 │
  ▼                 │
Enter: "Code"       │
Enter: 8            │
Enter: 5            │
Enter: 4            │
  │                 │
  ▼                 │
Task created (ID=2) │
  │                 │
  ▼                 │
Display Menu        │
  │                 │
  ▼                 │
User: "3"           │ ← Set Dependency
  │                 │
  ▼                 │
Enter: 2            │ ← Task 2
Enter: 1            │ ← depends on Task 1
  │                 │
  ▼                 │
Dependency added    │
  │                 │
  ▼                 │
Display Menu        │
  │                 │
  ▼                 │
User: "4"           │ ← Choose Scheduler
  │                 │
  ▼                 │
Enter: 1            │ ← Priority
  │                 │
  ▼                 │
Scheduler set       │
  │                 │
  ▼                 │
Display Menu        │
  │                 │
  ▼                 │
User: "6"           │ ← Execute
  │                 │
  ▼                 │
Check dependencies  │
  │                 │
  ▼                 │
Schedule tasks      │
PriorityScheduler   │
  │                 │
  ▼                 │
Order: [2, 1]       │ ← By priority (8, 4)
  │                 │
  ▼                 │
Execute loop:       │
  Pass 1:           │
    Task 2: NOT READY (depends on 1)
    Task 1: READY → Execute → Complete
  Pass 2:           │
    Task 2: READY → Execute → Complete
  │                 │
  ▼                 │
Print completion    │
  │                 │
  ▼                 │
Display Menu        │
  │                 │
  ▼                 │
User: "0"           │ ← Exit
  │                 │
  ▼                 │
EXIT ───────────────┘
```

---

**Note**: These are text-based flowcharts. For graphical flowcharts,
export this logic to draw.io, Lucidchart, or similar tools.
