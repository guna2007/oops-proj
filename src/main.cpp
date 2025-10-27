#include "task_manager.h"
#include <iostream>

// OOP Concept: Abstraction - Main function uses high-level TaskManager interface
// All complexity is hidden behind the TaskManager class

int main()
{
    // OOP Concept: Encapsulation - TaskManager encapsulates all system logic
    TaskManager manager;

    // OOP Concept: Abstraction - Simple interface hides complex CLI implementation
    manager.run();

    return 0;
}
