# Leetcode Solutions

Repository for tracking and recording Leetcode problem solutions implemented in Python and C++.

## Overview

This repository contains solutions to Leetcode problems organized by topic and programming language. Each solution includes the problem implementation and is named with the problem number and title for easy reference.

## Directory Structure

### Python Solutions
- **Python/Array/** - Array and list manipulation problems
  - Problems like 3Sum, 4Sum, duplicate removal, missing numbers, and duplicate detection
  - Covers array searching, sorting, and element manipulation techniques

### C++ Solutions
- **Cpp/Array/** - Array and list manipulation problems (C++ implementations)
  - Parallel implementations of all Python array problems
  - Includes both brute force and optimal solutions
  - Uses standard C++ data structures (vector, unordered_set, unordered_map)

### Documentation
- **[notes/](notes/README.md)** - DSA, C++, and LeetCode study notes
  - [DSA Fundamentals](notes/dsa-fundamentals.md) - Complexity, data structures, invariants, and graph traversal
  - [C++ STL Dictionary](notes/cpp-stl.md) - Containers, iterators, heaps, maps, sets, and standard algorithms
  - [Sorting Algorithms](notes/sorting-algorithms.md) - Sorting complexity, custom comparators, and sorting patterns
  - [Problem-Solving Patterns](notes/problem-solving-patterns.md) - Hashing, two pointers, sliding windows, DP, and backtracking
  - [LeetCode C++ Reference](notes/leetcode-cpp-reference.md) - Templates, safe arithmetic, debugging, and test cases
  - Big-O examples and complexity analysis resources

- **README.md** - Documentation and repository overview

## File Naming Convention

Solution files follow the format:
- **Python:** `[problem_number] [problem_title].py`
- **C++:** `[problem_number]_[problem_title].cpp`

Examples:
- `15 3sums.py` / `15_3Sum.cpp` - Leetcode problem 15 (3Sum)
- `268 Missing number.py` / `268_Missing_Number.cpp` - Leetcode problem 268 (Missing Number)
- `271 Contains duplicate.py` / `271_Contains_Duplicate.cpp` - Leetcode problem 271 (Contains Duplicate)

## Usage

**Python Solutions:**
- Each Python file contains a self-contained solution and can be run directly or imported for reference

**C++ Solutions:**
- Each C++ file contains multiple solution approaches (brute force + optimal)
- Includes standard `#include` headers and can be compiled with any modern C++ compiler
- Example: `g++ -std=c++17 -o solution 15_3Sum.cpp`

The [notes collection](notes/README.md) provides supporting material for understanding algorithm complexity, C++ STL, sorting, reusable problem-solving patterns, and performance across both languages.

## Suggested Workflow

1. Start with the relevant problem in the [problem list](#problem-list).
2. Read the constraints and identify the likely pattern.
3. Review the matching [DSA notes](notes/dsa-fundamentals.md) or [problem-solving pattern](notes/problem-solving-patterns.md).
4. Use the [C++ STL dictionary](notes/cpp-stl.md) and [C++ reference](notes/leetcode-cpp-reference.md) while implementing.
5. Test edge cases and record the final time and space complexity.


## Purpose

This repository serves as a personal learning resource and reference for Leetcode problems solved in multiple programming languages. It combines working solutions with structured notes so algorithms can be studied, implemented, compared, and revisited by topic.
