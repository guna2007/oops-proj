# Program Execution Flowchart - HTSE

## 1. Main Program Flow

```
           ┌─────────┐
           │  START  │
           └────┬────┘
                │
                ▼
        ┌───────────────┐
        │ Create        │
        │ TaskManager   │
        └───────┬───────┘
                │
                ▼
        ┌───────────────┐
        │ Display Menu  │
        └───────┬───────┘
                │
                ▼
        ┌───────────────┐
        │ Get User      │
        │ Choice        │
        └───────┬───────┘
                │
       ┌────────┴────────┐
       │                 │
       ▼                 ▼
   Choice = 0?       Process
      YES             Choice
       │                 │
       ▼                 │
    ┌──────┐            │
    │ EXIT │            │
    └──────┘            │
                        │
                        └──────┐
                               │
                    (Loop back to Display Menu)
```

---

## 2. Add Task Flow (Option 1)

```
    ┌──────────────┐
    │ Add New Task │
    └──────┬───────┘
           │
           ▼
    ┌──────────────┐
    │ Input Name   │
    └──────┬───────┘
           │
           ▼
    ┌──────────────┐
    │ Input        │
    │ Priority     │
    │ (1-10)       │
    └──────┬───────┘
           │
           ▼
    ┌──────────────┐
    │ Input        │
    │ Deadline     │
    └──────┬───────┘
           │
           ▼
    ┌──────────────┐
    │ Input Time   │
    └──────┬───────┘
           │
           ▼
    ┌──────────────┐
    │ Create Task  │
    │ Object       │
    └──────┬───────┘
           │
           ▼
    ┌──────────────┐
    │ Store in     │
    │ TaskManager  │
    └──────┬───────┘
           │
           ▼
    ┌──────────────┐
    │ Display      │
    │ Success      │
    └──────────────┘
```

---

## 3. Task Execution Flow (Option 6)

```
    ┌──────────────────┐
    │ Execute All      │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐      NO
    │ Tasks Exist?     │──────────▶ Display Error
    └────────┬─────────┘
             │ YES
             ▼
    ┌──────────────────┐      YES
    │ Has Circular     │──────────▶ Display Error
    │ Dependencies?    │           & Abort
    └────────┬─────────┘
             │ NO
             ▼
    ┌──────────────────┐
    │ Get All Tasks    │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ Apply Selected   │ ◀── Polymorphic Call
    │ Scheduler        │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ Get Ordered      │
    │ Task List        │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ Execute Tasks    │
    │ (Multi-pass)     │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ Update           │
    │ Statistics       │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ Display          │
    │ Completion       │
    └──────────────────┘
```

---

## 4. Multi-Pass Execution Algorithm

```
    ┌──────────────────┐
    │ Start Execution  │
    │ pass = 0         │
    └────────┬─────────┘
             │
         ┌───▼───────────────┐
         │ For each task:    │◀──────┐
         └────────┬──────────┘       │
                  │                  │
                  ▼                  │
         ┌──────────────────┐        │
         │ Check:           │        │
         │ Dependencies     │        │
         │ Satisfied?       │        │
         └────┬────────┬────┘        │
              │        │             │
             YES       NO            │
              │        │             │
              ▼        ▼             │
       ┌──────────┐ ┌───────┐       │
       │ Execute  │ │ Defer │       │
       │ Task     │ │ Task  │       │
       └────┬─────┘ └───┬───┘       │
            │           │            │
            └─────┬─────┘            │
                  │                  │
                  ▼                  │
         ┌──────────────────┐        │
         │ More Deferred    │        │
         │ Tasks?           │        │
         └────┬────────┬────┘        │
              │        │             │
             YES       NO            │
              │        │             │
              │        ▼             │
              │   ┌────────┐        │
              │   │ DONE   │        │
              │   └────────┘        │
              │                     │
              └─────────────────────┘
                  (Next Pass)
```

---

## 5. Dependency Check (isReady)

```
    ┌──────────────────┐
    │ Task.isReady()   │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ For each         │
    │ dependency:      │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐        NO
    │ Dependency       │──────────▶ Return FALSE
    │ COMPLETED?       │
    └────────┬─────────┘
             │ YES
             ▼
    ┌──────────────────┐
    │ Check next       │
    │ dependency       │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ All checked?     │
    └────────┬─────────┘
             │ YES
             ▼
    ┌──────────────────┐
    │ Return TRUE      │
    └──────────────────┘
```

---

## 6. Scheduler Algorithms (Polymorphic)

### Priority Scheduler

```
    ┌──────────────────┐
    │ schedule(tasks)  │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ Sort tasks by    │
    │ Priority         │
    │ (High → Low)     │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ Return sorted    │
    │ list             │
    └──────────────────┘
```

### Deadline Scheduler

```
    ┌──────────────────┐
    │ schedule(tasks)  │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ Sort tasks by    │
    │ Deadline         │
    │ (Early → Late)   │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ Return sorted    │
    │ list             │
    └──────────────────┘
```

### Hierarchical Scheduler

```
    ┌──────────────────┐
    │ schedule(tasks)  │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ Find root tasks  │
    │ (no parents)     │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ For each root:   │
    │ Collect tree     │ ◀── Recursive
    │ (parent first)   │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────┐
    │ Return ordered   │
    │ list             │
    └──────────────────┘
```

---

## 7. Circular Dependency Detection

```
    ┌──────────────────────┐
    │ detectCycle(task)    │
    └──────────┬───────────┘
               │
               ▼
    ┌──────────────────────┐     YES
    │ Already in           │──────────▶ CYCLE FOUND!
    │ recursion stack?     │           Return TRUE
    └──────────┬───────────┘
               │ NO
               ▼
    ┌──────────────────────┐     YES
    │ Already visited?     │──────────▶ Return FALSE
    └──────────┬───────────┘
               │ NO
               ▼
    ┌──────────────────────┐
    │ Add to visited       │
    │ Add to rec_stack     │
    └──────────┬───────────┘
               │
               ▼
    ┌──────────────────────┐
    │ For each dependency: │
    │ detectCycle(dep)     │ ◀── Recursive
    └──────────┬───────────┘
               │
          ┌────┴────┐
          │         │
      Cycle      No Cycle
       Found        │
          │         ▼
          │    ┌──────────────┐
          │    │ Remove from  │
          │    │ rec_stack    │
          │    └──────┬───────┘
          │           │
          │           ▼
          │    ┌──────────────┐
          │    │Return FALSE  │
          │    └──────────────┘
          │
          ▼
    ┌──────────────┐
    │ Return TRUE  │
    └──────────────┘
```

---

## 8. Complete User Session Example

```
START
  │
  ▼
Create Manager
  │
  ▼
┌─────────────┐
│Display Menu │◀─────────┐
└──────┬──────┘          │
       │                 │
       ▼                 │
 Choice: 1 (Add Task)    │
       │                 │
       ▼                 │
 Enter: "Design"         │
 Priority: 8             │
 Deadline: 10            │
 Time: 5                 │
       │                 │
       ▼                 │
 Task Created (ID=1)     │
       │                 │
       ├─────────────────┘
       ▼
 Choice: 1 (Add Task)
       │
       ▼
 Enter: "Code"
 Priority: 9
 Deadline: 5
 Time: 4
       │
       ▼
 Task Created (ID=2)
       │
       ▼
 Choice: 3 (Set Dependency)
       │
       ▼
 Task 2 depends on Task 1
       │
       ▼
 Choice: 4 (Choose Scheduler)
       │
       ▼
 Select: Priority Scheduler
       │
       ▼
 Choice: 6 (Execute)
       │
       ▼
 Check Dependencies ✓
       │
       ▼
 Schedule: [Task 2, Task 1]
       │
       ▼
 Execute:
   Pass 1: Task 1 ✓
   Pass 2: Task 2 ✓
       │
       ▼
 Display Completion
       │
       ▼
 Choice: 0
       │
       ▼
      EXIT
```

---

_These flowcharts illustrate the program's execution logic and demonstrate the use of recursion, polymorphism, and algorithmic thinking in the HTSE system._

````
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
````
