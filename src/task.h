#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

using namespace std;

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
    string name;
    int priority; // 1-10, 10 is highest
    int deadline; // Integer days from now
    TaskStatus status;
    int estimated_time;          // Simulated execution time units
    vector<Task *> subtasks;     // OOP Concept: Composition - Contains other tasks
    vector<Task *> dependencies; // OOP Concept: Aggregation - References to other tasks

public:
    // Constructor
    Task(int id, const string &name, int priority, int deadline, int time);

    // Destructor
    ~Task();

    // Getters - OOP Concept: Encapsulation (controlled access)
    int getId() const;
    string getName() const;
    int getPriority() const;
    int getDeadline() const;
    TaskStatus getStatus() const;
    int getEstimatedTime() const;
    const vector<Task *> &getSubtasks() const;
    const vector<Task *> &getDependencies() const;

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

    // ===== OOP Concept: OPERATOR OVERLOADING =====

    // Comparison operators - Compare tasks by priority
    bool operator<(const Task &other) const;  // Lower priority
    bool operator>(const Task &other) const;  // Higher priority
    bool operator<=(const Task &other) const; // Lower or equal priority
    bool operator>=(const Task &other) const; // Higher or equal priority
    bool operator==(const Task &other) const; // Same task (by ID)
    bool operator!=(const Task &other) const; // Different task

    // Arithmetic operators - Modify priority
    Task operator+(int value) const; // Increase priority
    Task operator-(int value) const; // Decrease priority
    Task &operator+=(int value);     // Increase priority in-place
    Task &operator-=(int value);     // Decrease priority in-place

    // Increment/Decrement operators - Adjust priority by 1
    Task &operator++();   // Pre-increment priority
    Task operator++(int); // Post-increment priority
    Task &operator--();   // Pre-decrement priority
    Task operator--(int); // Post-decrement priority

    // Stream insertion operator - For easy printing
    friend ostream &operator<<(ostream &os, const Task &task);

    // Assignment operator
    Task &operator=(const Task &other);
};

#endif // TASK_H
