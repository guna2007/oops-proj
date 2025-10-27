Perfect 👌 — since your `instructions.md` already defines a **clear project specification**, you can now give GitHub Copilot (or any agentic AI system) a single, structured **prompt** to make it:

1. **Read and interpret** your `instructions.md`.
2. **Generate code incrementally**, file by file.
3. **Track progress** in a `progress.md` log automatically.
4. **Maintain academic clarity**, not production-grade complexity.

Here’s the **exact Copilot prompt** you can paste into your workspace (like the Copilot Chat or CLI agent mode):

---

### 🚀 **Prompt for Copilot Agentic Mode**

```text
You are an AI coding assistant helping to implement a semester-level C++ OOP project called 
"Hierarchical Task Scheduling Engine (HTSE)". 

You must read and follow the complete project specification defined in the file `instructions.md`.

Follow these rules strictly:
1. Treat `instructions.md` as the single source of truth for the entire project.
2. Do NOT overwrite or modify existing files unless the change is required to stay consistent with `instructions.md`.
3. Generate clean, readable, academic-level C++ code — emphasize clarity, comments, and demonstration of OOP concepts 
   (Encapsulation, Inheritance, Abstraction, Polymorphism, Composition, and Recursion). 
   Avoid production-level complexity like threading, persistence, or error handling frameworks.
4. Implement one logical file at a time inside a `src/` folder:
   - task.h / task.cpp
   - hierarchical_task.h / hierarchical_task.cpp
   - scheduler.h / scheduler.cpp
   - priority_scheduler.h / priority_scheduler.cpp
   - deadline_scheduler.h / deadline_scheduler.cpp
   - hierarchical_scheduler.h / hierarchical_scheduler.cpp
   - task_executor.h / task_executor.cpp
   - task_manager.h / task_manager.cpp
   - main.cpp
5. After completing each file, append a short summary in `progress.md` under this format:

```

## [timestamp] File Completed: <filename>

* Purpose: <one line summary>
* Key Concepts: <comma-separated OOP concepts used>
* Next Step: <next file Copilot will work on>

```

6. Use clear console output formatting for all CLI interactions.
7. Avoid any non-ASCII characters in console logs.
8. Ensure all dependencies are correctly included, header guards are used, and namespaces are consistent.
9. At the end of all implementations, generate a final section in `progress.md` called "Testing Checklist" with sample input-output flow matching the examples in `instructions.md`.

Begin now by reading `instructions.md` fully and planning the class hierarchy.
Then start coding the first file (`task.h` and `task.cpp`), documenting the progress in `progress.md` as you go.
```

---

### ✅ Optional Tip:

If your Copilot supports *plan + execute* style prompts, prepend this:

```text
PLAN: Read `instructions.md`, break down class dependencies, and list file generation order.
EXECUTE: Start implementing each file sequentially, updating `progress.md` after each.
```

---

Would you like me to write the **ideal structure for progress.md** (so Copilot knows exactly how to format it cleanly and consistently)?
It’ll make your progress tracking and submission report easier.
