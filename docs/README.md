# HTSE Documentation Index

This directory contains supplementary documentation for the Hierarchical Task Scheduling Engine project.

## Available Documents

### 1. CLASS_DIAGRAM.md

**Purpose**: Visual representation of class structure and relationships

**Contents**:

- Text-based UML class diagram
- Detailed class specifications
- Interaction flow diagrams
- OOP concepts mapping
- PlantUML code for automatic diagram generation

**Use Case**: Understanding the overall architecture and class relationships

---

### 2. FLOWCHART.md

**Purpose**: Execution flow and algorithm visualization

**Contents**:

- Main program flow
- Task creation flow
- Task execution flow
- Scheduler algorithm flows
- Dependency resolution flow
- Cycle detection flow
- Complete user session example

**Use Case**: Understanding how the program operates step-by-step

---

## How to Use This Documentation

### For Learning

1. Start with **CLASS_DIAGRAM.md** to understand the structure
2. Read **FLOWCHART.md** to understand the execution flow
3. Review the source code with this context in mind

### For Implementation

1. Use CLASS_DIAGRAM.md as a reference for class design
2. Use FLOWCHART.md to understand control flow
3. Refer to specific sections when implementing features

### For Presentation

1. Generate graphical diagrams from the PlantUML code
2. Use flowcharts to explain program behavior
3. Reference OOP concept mappings in discussions

---

## Generating Graphical Diagrams

### UML Class Diagram (from CLASS_DIAGRAM.md)

**Option 1: Using PlantUML**

1. Copy the PlantUML code from CLASS_DIAGRAM.md
2. Save to `htse_classes.puml`
3. Render using:
   - Online: http://www.plantuml.com/plantuml/
   - VS Code: Install PlantUML extension
   - Command line: `plantuml htse_classes.puml`

**Option 2: Using draw.io**

1. Open https://app.diagrams.net/
2. Create new diagram
3. Use the text descriptions from CLASS_DIAGRAM.md as reference
4. Draw classes with proper UML notation

**Option 3: Using Lucidchart**

1. Sign up at https://www.lucidchart.com/
2. Use UML class diagram template
3. Follow the structure from CLASS_DIAGRAM.md

### Flowcharts (from FLOWCHART.md)

**Option 1: draw.io**

1. Use flowchart shapes
2. Follow the ASCII flowcharts from FLOWCHART.md
3. Export as PNG or PDF

**Option 2: Microsoft Visio**

1. Use flowchart template
2. Convert ASCII diagrams to graphical format

**Option 3: Google Drawings**

1. Free alternative
2. Create flowcharts based on text descriptions

---

## Additional Resources

### In Main Directory

- **README.md**: Complete project documentation
- **QUICKSTART.md**: Quick start guide
- **SUMMARY.md**: Project summary and completion status
- **progress.md**: Detailed implementation log
- **BUILD_WINDOWS.md**: Windows build instructions

### In Source Directory

- **src/**: All C++ source files with inline comments

---

## Documentation Standards

All documentation in this project follows these principles:

1. **Clarity**: Clear, concise language
2. **Completeness**: All aspects covered
3. **Accuracy**: Verified against implementation
4. **Educational**: Focus on learning OOP concepts
5. **Accessibility**: Text-based for easy access

---

## Contribution Guidelines

If extending this project, please:

1. Update CLASS_DIAGRAM.md when adding new classes
2. Update FLOWCHART.md when changing control flow
3. Maintain ASCII representations for accessibility
4. Keep PlantUML code synchronized with text diagrams
5. Document OOP concepts used

---

## Quick Reference

| Want to understand... | See document...  | Section...               |
| --------------------- | ---------------- | ------------------------ |
| Class hierarchy       | CLASS_DIAGRAM.md | Class Hierarchy Overview |
| Task structure        | CLASS_DIAGRAM.md | Task class details       |
| Scheduler design      | CLASS_DIAGRAM.md | Scheduler hierarchy      |
| Program startup       | FLOWCHART.md     | Main Program Flow        |
| Task execution        | FLOWCHART.md     | Task Execution Flow      |
| Dependency resolution | FLOWCHART.md     | Dependency Resolution    |
| Cycle detection       | FLOWCHART.md     | Cycle Detection Flow     |
| Complete workflow     | FLOWCHART.md     | Complete User Session    |

---

## For Grading/Presentation

When preparing for grading or presentation:

1. **Print or render**:

   - UML class diagram (from CLASS_DIAGRAM.md PlantUML)
   - Main execution flowchart (from FLOWCHART.md)

2. **Prepare to explain**:

   - How each class demonstrates OOP concepts
   - How polymorphism enables scheduler selection
   - How recursion is used in hierarchy traversal
   - How composition manages object relationships

3. **Demo scenarios**:

   - Simple linear dependency
   - Hierarchical task structure
   - All three scheduling algorithms
   - Circular dependency detection

4. **Show code sections**:
   - Pure virtual functions (Scheduler)
   - Virtual function overrides (schedulers)
   - Recursive methods (displayHierarchy)
   - Smart pointers (TaskManager)

---

## Updates

This documentation is current as of: **October 27, 2025**

For the latest version, check the project repository.

---

**End of Documentation Index**
