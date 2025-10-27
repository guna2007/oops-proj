# UML Class Diagram - HTSE

## 1. Inheritance Hierarchy (Scheduler Classes)

```
                    ┌─────────────────────┐
                    │     Scheduler       │
                    │   <<abstract>>      │
                    ├─────────────────────┤
                    │                     │
                    │ + schedule()        │
                    │ + getName()         │
                    └──────────┬──────────┘
                               │
                               │ inherits
                    ┏━━━━━━━━━━┻━━━━━━━━━━┓
                    ▼                     ▼
         ┌──────────────────┐   ┌──────────────────┐
         │ PriorityScheduler│   │DeadlineScheduler │
         ├──────────────────┤   ├──────────────────┤
         │                  │   │                  │
         │ + schedule()     │   │ + schedule()     │
         │ + getName()      │   │ + getName()      │
         └──────────────────┘   └──────────────────┘

                    ▼
         ┌──────────────────────┐
         │HierarchicalScheduler │
         ├──────────────────────┤
         │                      │
         │ + schedule()         │
         │ + getName()          │
         └──────────────────────┘
```

**OOP Concept**: Inheritance & Polymorphism

---

## 2. Task Class (Encapsulation & Composition)

```
┌────────────────────────────────────────┐
│              Task                      │
├────────────────────────────────────────┤
│ - id: int                              │
│ - name: string                         │
│ - priority: int                        │
│ - deadline: int                        │
│ - status: TaskStatus                   │
│ - estimated_time: int                  │
│ - subtasks: vector<Task*>         ◀────┼──┐ Composition
│ - dependencies: vector<Task*>     ◀────┼──┘ (has-a)
├────────────────────────────────────────┤
│ + Task(...)                            │
│ + getId(): int                         │
│ + getName(): string                    │
│ + getPriority(): int                   │
│ + getDeadline(): int                   │
│ + getStatus(): TaskStatus              │
│ + addSubtask(Task*)                    │
│ + addDependency(Task*)                 │
│ + isReady(): bool                      │
│ + execute()                            │
│ + displayHierarchy(int)                │ Recursive
│ + getTotalSubtasks(): int              │ Recursive
└────────────────────────────────────────┘
```

**OOP Concepts**: Encapsulation (private data), Composition (contains other tasks)

---

## 3. TaskExecutor Class

```
┌────────────────────────────────────────┐
│          TaskExecutor                  │
├────────────────────────────────────────┤
│ - output: ostream&                     │ Composition
│ - total_execution_time: int            │
├────────────────────────────────────────┤
│ + TaskExecutor(ostream&)               │
│ + runTasks(vector<Task*>, string)     │
│ + getTotalExecutionTime(): int         │
│ + resetExecutionTime()                 │
│                                        │
│ - executeTaskWithSubtasks(Task*, int) │ Recursive
│ - printTaskExecution(...)              │
│ - showProgressAnimation(Task*, int)    │
└────────────────────────────────────────┘
```

**OOP Concepts**: Encapsulation, Composition (has ostream), Recursion

---

## 4. TaskManager Class (Main Coordinator)

```
┌────────────────────────────────────────┐
│          TaskManager                   │
├────────────────────────────────────────┤
│ - all_tasks: vector<unique_ptr<Task>>  │ Owns tasks
│ - task_map: map<int, Task*>            │
│ - current_scheduler: unique_ptr<Scheduler>│ Polymorphic
│ - executor: TaskExecutor               │ Composition
│ - next_task_id: int                    │
│ - completed_tasks: int                 │
│ - total_simulated_time: int            │
├────────────────────────────────────────┤
│ + TaskManager()                        │
│ + run()                                │
│ + createTask(...): Task*               │
│ + addSubtask(int, int)                 │
│ + addDependency(int, int)              │
│ + setScheduler(unique_ptr<Scheduler>)  │
│ + executeAll()                         │
│                                        │
│ - displayMenu()                        │
│ - detectCycle(...): bool               │ Recursive
│ - hasCircularDependencies(): bool      │
└────────────────────────────────────────┘
```

**OOP Concepts**: Encapsulation, Composition, Polymorphism

---

## 5. Complete System Diagram

```
                    ┌──────────────┐
                    │     main     │
                    └──────┬───────┘
                           │ creates
                           ▼
                 ┌─────────────────────┐
                 │   TaskManager       │
                 └─────────┬───────────┘
                           │
            ┌──────────────┼──────────────┐
            │              │              │
            │ owns         │ has          │ has
            ▼              ▼              ▼
       ┌────────┐    ┌──────────┐   ┌──────────────┐
       │  Task  │    │Scheduler │   │TaskExecutor  │
       └────┬───┘    └────┬─────┘   └──────────────┘
            │             │
            │ contains    │ polymorphic to
            │             │
            ▼             ├─▶ PriorityScheduler
       ┌────────┐        │
       │  Task  │        ├─▶ DeadlineScheduler
       │(child) │        │
       └────────┘        └─▶ HierarchicalScheduler
```

---

## 6. OOP Concepts Map

| Concept           | Classes/Location                           |
| ----------------- | ------------------------------------------ |
| **Encapsulation** | Task, TaskManager, TaskExecutor            |
| **Inheritance**   | Scheduler → Priority/Deadline/Hierarchical |
| **Polymorphism**  | Scheduler virtual methods, runtime binding |
| **Abstraction**   | Scheduler (abstract base class)            |
| **Composition**   | Task has subtasks, Manager owns tasks      |
| **Recursion**     | displayHierarchy(), detectCycle()          |

---

## 7. Relationships Summary

**Inheritance** (is-a):

- PriorityScheduler IS-A Scheduler
- DeadlineScheduler IS-A Scheduler
- HierarchicalScheduler IS-A Scheduler

**Composition** (has-a, owns):

- TaskManager HAS-A vector of Tasks (owns)
- TaskManager HAS-A Scheduler (owns)
- TaskManager HAS-A TaskExecutor
- Task HAS-A vector of subtasks
- TaskExecutor HAS-A output stream

**Association** (uses):

- TaskExecutor USES Task
- Scheduler USES Task
- TaskManager USES Scheduler polymorphically

---

_This diagram represents the core structure of the Hierarchical Task Scheduling Engine demonstrating all major OOP principles._
