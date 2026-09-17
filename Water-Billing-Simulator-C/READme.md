# Group 7: County Water Consumption and Billing Simulator (C Implementation)

## Course & Group Details
* **Unit Code:** CCS 2105 - Programming Languages
* **Unit Name:** Programming Languages Laboratory
* **Assignment:** Names, Bindings, and Scopes (Group 7)
* **Code Repository:** [OneCompiler C Code](https://onecompiler.com/c/453ersm5d)
* **Documentation:** [C Documentation Google Doc](https://docs.google.com/document/d/1ibbBRpm8eljvzOZ1VkilgoXWBQwmw11u/edit)

## Group Members
1.	Godfrey Macharia - C026-01-0950/2025
2.	Roy Waititu -  C026-01-0931/2025
3.	Vivian Ndirangu  - C026-01-0954/2025 


---

## System Documentation

### Project Overview
This project implements a C application designed to calculate water utility bills for county customers using progressive tiered tariffs, validate meter inputs, track metrics, and generate summary reports.

### Key Concepts & Technical Implementation
1. **Named Constants & Binding Times (Tasks A & B)**
   - Tariff parameters (`RATE_BAND1 = 25.0`, `RATE_BAND2 = 35.0`, `RATE_BAND3 = 50.0`, `FIXED_CHARGE = 100.0`) are declared as `const` values bound at **compile time**.
   - Customer input fields (e.g., `customers[i].currentReading`) are bound to memory locations at **load time** and populated with values at **run time**.

2. **L-Value vs. R-Value Evaluation (Task C)**
   - In `b.totalBill = b.bandCharge + b.fixedCharge;`, `b.totalBill` acts as an **L-Value** (a modifiable memory location), whereas `b.bandCharge + b.fixedCharge` evaluates to an **R-Value** (a temporary computed value).

3. **Scope and Lifetime Optimization (Task D)**
   - **Minimizing Block Scope:** The `bandCharge` variable is declared strictly inside individual conditional branches (`if`/`else`) in `generateBill()` to enforce block-level scoping and minimize variable lifetime.
   - **Static Lifetime:** The `countGeneratedBills()` function uses a `static int billsGenerated` counter whose scope is internal to the function, but whose lifetime persists in static memory across execution calls.

### System Rules & Input Validation
* **Minimum Customers:** Rejects processing if fewer than 6 customers are entered.
* **Meter Verification:** Enforces `currentReading >= previousReading` and non-negative values.
* **Tariff Bands:**
  * Band 1 (1–10 units): KES 25.0 / unit
  * Band 2 (11–30 units): KES 35.0 / unit
  * Band 3 (>30 units): KES 50.0 / unit
  * Mandatory Fixed Charge: KES 100.0

  ## Quick Links & Execution
* **Live Online Execution:** [Run C Code on OneCompiler](https://onecompiler.com/c/453ersm5d)
* **Google Docs System Documentation:** [C Documentation](https://docs.google.com/document/d/1ibbBRpm8eljvzOZ1VkilgoXWBQwmw11u/edit)