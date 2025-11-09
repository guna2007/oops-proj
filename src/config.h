#ifndef CONFIG_H
#define CONFIG_H

// ============================================================
// HTSE Project Configuration File
// ============================================================
// This file controls build-time features for academic deadlines
// Modify these settings based on submission requirements
// ============================================================

// ===== DEADLINE MODE CONTROL =====
// Uncomment the line below for Deadline 2 (November 6, 2025)
// This disables Polymorphism, Templates, and Exception Handling
// and locks the scheduler to PriorityScheduler only

// #define D2_MODE

// When D2_MODE is defined:
// - Only Encapsulation, Abstraction, Inheritance, Operator Overloading
// - No runtime scheduler selection (PriorityScheduler only)
// - Template demonstrations hidden from menu
// - Exception handling disabled
//
// When D2_MODE is NOT defined (Final Submission):
// - All OOP concepts enabled
// - Polymorphism via Scheduler base class
// - Templates and generic programming
// - Exception handling with try-catch blocks

// ===== UI CONFIGURATION =====
// Enable ANSI color codes for terminal output
// Set to 0 to disable colors for compatibility
#ifndef ENABLE_COLOR
#define ENABLE_COLOR 1
#endif

// ===== EXECUTION CONFIGURATION =====
// Delay in milliseconds for task execution animation
// Set to 0 for instant execution (useful for testing)
#ifndef EXEC_DELAY_MS
#define EXEC_DELAY_MS 500
#endif

// ===== COLOR DEFINITIONS =====
// ANSI escape codes for colored terminal output
#if ENABLE_COLOR
#define COLOR_RESET "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_RED "\033[1;31m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#else
#define COLOR_RESET ""
#define COLOR_BOLD ""
#define COLOR_CYAN ""
#define COLOR_GREEN ""
#define COLOR_YELLOW ""
#define COLOR_RED ""
#define COLOR_BLUE ""
#define COLOR_MAGENTA ""
#endif

// ===== UI CONSTANTS =====
#define UI_WIDTH 62
#define UI_BORDER "+============================================================+"
#define UI_LINE "+--------------------------------------------------------------+"

#endif // CONFIG_H
