# 🔗 Professional URL Shortener Service (C++ Modular Engine)

## 1. Overview
A high-performance, CLI-based URL Shortener designed with an emphasis on **Modular Software Architecture**. This project demonstrates the ability to decompose a system into independent logic, storage, and validation layers using only the C++ Standard Library.

## 2. Planning & Core Mechanics (Detailed Analysis)
The system was engineered following a structured analytical approach to solve the challenge of mapping infinite long URLs to finite, readable short codes.

### A. Problem Decomposition
The engineering problem was broken down into four distinct domains:
- **Input Integrity:** Filtering and sanitizing raw string data before processing.
- **Algorithmic Transformation:** Converting a complex URL string into a predictable, human-friendly identifier without external libraries.
- **State Persistence:** Managing the lifecycle of data across program restarts.
- **Memory Optimization:** Utilizing Hash-based structures to ensure $O(1)$ search performance.

### B. Logical Mapping Strategy
To prevent data duplication and ensure bidirectional lookup, the system maintains a **Dual-Map In-Memory State**:
1. `longToShort Map`: Prevents re-shortening the same URL, saving storage and compute cycles.
2. `shortToLong Map`: Enables instantaneous resolution of short codes back to original destinations.

### C. Human-Friendly Algorithm Design
The algorithm rejects random string generation in favor of **Semantic Tokenization**:
- **Sanitization:** Stripping protocols and `www` prefixes to isolate the core domain.
- **Domain Segmentation:** Breaking the domain into tokens using `.` and `-` as delimiters.
- **Contextual Extraction:** Capturing the first 2 characters of each token + the last path segment (Identifier) to maintain readability while ensuring uniqueness.

---

## 3. System Architecture & Component Breakdown

The system is split into three independent modules to ensure high cohesion and low coupling:

### 3.1. `UrlShortener` Class (The Logic Engine)
**Files:** `UrlShortener.h`, `UrlShortener.cpp`
- **Responsibility:** Orchestrates the shortening process and executes the parsing algorithm.
- **Key Logic:**
    - `generateHumanFriendlyCode()`: A private helper that implements the string-shredding logic using `std::string::find` and `std::string::substr`.
    - `shorten()`: Manages the logic flow—checks cache, generates code, handles collisions, and triggers persistence.


### 3.2. `StorageManager` Class (The Persistence Layer)
**Files:** `StorageManager.h`, `StorageManager.cpp`
- **Responsibility:** Bridges the volatile memory (RAM) and the non-volatile storage (Disk).
- **Key Logic:**
    - `loadMappings()`: Parsed on startup. It utilizes `std::ifstream` to populate the maps, ensuring the system recovers its state perfectly.
    - `appendMapping()`: Uses `std::ios::app` (Append Mode) to write new entries to `urls.txt`. This is a constant time $O(1)$ write operation, avoiding the overhead of re-writing the entire file.

### 3.3. `UrlValidator` (Input Guard)
- **Responsibility:** Implements defensive programming by ensuring input strings conform to standard URL structures (Protocol presence, no whitespace) before they reach the core engine.

---

## 4. Implementation Steps (Phased Execution)

The project was developed in four distinct engineering phases:

### Phase I: Foundation & CLI
- Defined the system interfaces and built the interactive CLI loop.
- Implemented basic input/output flow using `std::cin` and `std::cout`.

### Phase II: The Algorithmic Engine
- Developed the `UrlShortener` class logic.
- Implemented the string manipulation algorithm for human-friendly code generation.
- Integrated `std::unordered_map` to handle in-memory data management.

### Phase III: Persistence Integration
- Created the `StorageManager` to handle file I/O operations.
- Developed the startup loading sequence to ensure the system is "stateful."

### Phase IV: Robustness & Refinement
- Added defensive validation layers to handle edge cases (e.g., empty paths, invalid protocols).
- Final code audit for memory efficiency and naming conventions.

---

## 5. Build & Run Instructions
```bash
# Compile all modules together
g++ main.cpp UrlShortener.cpp StorageManager.cpp -o url_shortener

# Run the system
./url_shortener
```
---
## 6. Sample Usage (I/O)

| Original URL (Input) | Generated Short URL (Output) |
| :--- | :--- |
| `https://github.com/user/project/154` | `gi-pr/154` |
| `https://social-media.net/profile/edit` | `so-me/edit` |
| `https://www.google.com/search?q=cpp` | `go/search?q=cpp` |