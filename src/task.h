#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

// OOP Concept: Encapsulation - Task encapsulates all task-related data and behavior
// OOP Concept: Composition - Task contains vectors of other Task pointers (subtasks and dependencies)

enum TaskStatus
{
    PENDING,
    RUNNING,
    COMPLETED
};

class Task
{
private:
    // OOP Concept: Encapsulation - Private data members
    int id;
    std::string name;
    int priority; // 1-10, 10 is highest
    int deadline; // Integer days from now
    TaskStatus status;
    int estimated_time;               // Simulated execution time units
    std::vector<Task *> subtasks;     // OOP Concept: Composition - Contains other tasks
    std::vector<Task *> dependencies; // OOP Concept: Aggregation - References to other tasks

public:
    // Constructor
    Task(int id, const std::string &name, int priority, int deadline, int time);

    // Destructor
    ~Task();

    // Getters - OOP Concept: Encapsulation (controlled access)
    int getId() const;
    std::string getName() const;
    int getPriority() const;
    int getDeadline() const;
    TaskStatus getStatus() const;
    int getEstimatedTime() const;
    const std::vector<Task *> &getSubtasks() const;
    const std::vector<Task *> &getDependencies() const;

    // Task hierarchy management
    void addSubtask(Task *t);
    void addDependency(Task *t);

    // Execution control
    bool isReady() const; // Returns true if all dependencies are COMPLETED
    void execute();       // Simulate task execution
    void markComplete();

    // Display methods - OOP Concept: Abstraction (hiding implementation details)
    void displayInfo(int indent = 0) const;
    void displayHierarchy(int indent = 0) const; // OOP Concept: Recursion

    // Utility methods
    int getTotalSubtasks() const; // Counts all subtasks recursively
};

#endif // TASK_H
