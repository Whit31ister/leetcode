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
- **notes/** - Algorithm documentation and complexity analysis
  - Big O complexity explanations and examples
  - Reference material for algorithm analysis and performance considerations

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

The notes folder provides supporting material for understanding algorithm complexity and performance across all languages.

## Problem List

| Problem | Python | C++ |
|---------|--------|-----|
| 2 Two Sum | ✓ | ✓ |
| 15 3Sum | ✓ | ✓ |
| 18 4Sum | ✓ | ✓ |
| 26 Remove Duplicates from Sorted Array | ✓ | ✓ |
| 268 Missing Number | ✓ | ✓ |
| 271 Contains Duplicate | ✓ | ✓ |
| 448 Find All Missing Numbers | ✓ | ✓ |
| 1365 How Many Numbers Are Smaller Than Current | ✓ | ✓ |

## Purpose

This repository serves as a personal learning resource and reference for Leetcode problems solved in multiple programming languages. It helps track progress, maintain a searchable collection of solutions by problem category and number, and enables comparison between different language implementations of the same algorithms.
