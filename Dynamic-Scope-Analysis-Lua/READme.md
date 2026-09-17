# Group 7: Dynamic vs. Lexical Scope Analysis (Lua Implementation)

## Course & Group Details

- **Unit Code:** CCS 2105 - Programming Languages
- **Unit Name:** Programming Languages Laboratory
- **Assignment:** Scope Resolution & Variable Binding Analysis
- **Live Online Execution:** [Run Lua Code on OneCompiler](https://onecompiler.com/lua/453eqp9b9)
- **Google Docs System Documentation:** [Lua Documentation](https://docs.google.com/document/d/1vZyt4a7wEF8muFleJ4EjWnf6Cw6Dzh7L/edit?usp=sharing)

---

## Group Members

1. **Godfrey Macharia** - C026-01-0950/2025
2. **Roy Waititu** - C026-01-0931/2025
3. **Vivian Ndirangu** - C026-01-0954/2025

---

## System Documentation

### Project Overview

This project explores and demonstrates the core differences between **Lexical (Static) Scoping** and **Dynamic Scoping** using Lua scripts. It analyzes how variable lookup rules behave during program execution, highlighting referencing environments, variable shadowing, and binding times.

### Comparative Analysis

| Feature / Property       | Lexical (Static) Scope                                               | Dynamic Scope                                                        |
| :----------------------- | :------------------------------------------------------------------- | :------------------------------------------------------------------- |
| **Resolution Strategy**  | Determined at **compile time** based on source code block structure. | Determined at **run time** based on the active execution call stack. |
| **Free Variable Origin** | Bound to the environment where the function was **defined**.         | Bound to the environment where the function was **called**.          |
| **Predictability**       | High; variable references can be analyzed by reading code structure. | Low; variable values depend on dynamic call sequences.               |
| **Primary Languages**    | C, C++, Lua, Python, Java                                            | Bash, Perl (`local`), Early LISP                                     |

---

### Key Concepts Demonstrated

1. **Static / Lexical Scope Rules:**
   - In standard Lua execution, functions resolve free variables using the environment in which they were _declared_.
   - Nested blocks establish parent-child lexical hierarchies that remain fixed regardless of call sequence.

2. **Dynamic Scoping Simulation:**
   - Demonstrates how free variables are evaluated when name resolution traverses the active call stack rather than the lexical declaration block.
   - Highlights how execution outcomes change depending on which caller function invokes a target subroutine.

3. **Referencing Environments & Shadowing:**
   - Illustrates local vs. enclosing/global scope shadowing when identifiers share the same name across multiple nesting levels.
