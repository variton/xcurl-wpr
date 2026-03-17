# Design {#design}

This section describes the architectural choices and constraints guiding the implementation.

The two applications are implemented using a small framework designed to:

- keep the codebase uncluttered,
- scale as the project evolves,
- allow the entire code path to be easily understood,
- enable reuse of software components.

## Architectural Concepts

The architecture is driven by three main constraints:

- separation of concerns,
- zero-cost abstractions,
- timing and latency requirements.

---

## 1. Separation of Concerns

Functionality is divided into well-defined modules with clear interfaces.  
Components shared across executables are packaged as libraries in order to maximize reuse and maintain explicit boundaries.

**Trade-off**

This approach introduces additional build and deployment complexity, including interface management, versioning, and debugging across modules.

---

## 2. Zero-Cost Abstractions

Performance-critical code avoids runtime overhead (such as virtual dispatch) by using compile-time polymorphism (templates and CRTP) together with inlining-friendly interfaces.

**Trade-off**

This increases compile-time complexity and can make debugging and compiler error messages harder to understand for developers unfamiliar with template-based design.

---

## 3. Timing and Latency Constraints

Performance-critical loops are kept minimal and close to operating system APIs (socket I/O, polling, and file I/O) in order to minimize overhead and reduce timing jitter.

**Trade-off**

This results in less abstract interfaces in the critical path and introduces platform-specific code, requiring familiarity with system-level programming.

---

## Summary

The chosen architecture prioritizes:

- clarity of code structure,
- predictable runtime behavior,
- low execution overhead,
- and component reuse.

This approach provides a balance between performance and maintainability while keeping the system extensible.
