# CS 300 Portfolio Submission

## Repository Contents

This repository contains selected portfolio artifacts from CS 300: Data Structures and Algorithms.

### Project One Artifact
**Pseudocode and Runtime Analysis**

This document compares the use of vectors, hash tables, and binary search trees for the ABCU advising program. It includes pseudocode, runtime analysis, memory analysis, advantages and disadvantages of each data structure, and a final recommendation.

### Project Two Artifact
**Advising Assistance Program**

This C++ program loads course information from a file, stores the course data in a binary search tree, prints all courses in alphanumeric order, and allows a user to search for an individual course and view its prerequisites.

---

## Reflection

### What was the problem you were solving in the projects for this course?

The main problem I was solving was how to store, organize, search, and display course information for ABCU’s Computer Science advising program. The advisors needed a program that could load course data from a file, print all courses in alphanumeric order, and allow a user to search for one course and view its prerequisites.

### How did you approach the problem?

I approached the problem by comparing different data structures and thinking about how each one would affect performance. I worked with vectors, hash tables, and binary search trees. Understanding data structures is important because the structure chosen affects how efficiently a program can insert, search, sort, and print data. For this project, I recommended and used a binary search tree because it supports sorted output through in-order traversal and allows efficient searching when the tree is reasonably balanced.

### How did you overcome any roadblocks you encountered while going through the activities or project?

One roadblock I encountered was handling the course input file correctly, especially when reading lines with optional prerequisites. I had to make sure the program ignored blank prerequisite fields and validated that each listed prerequisite existed as another course in the file. I also tested the menu options, file loading, course search, and printed course list to make sure the program behaved correctly.

### How has your work on this project expanded your approach to designing software and developing programs?

This project helped me think more carefully about planning before coding. Instead of just starting with code, I first used pseudocode and runtime analysis to compare possible solutions. That helped me understand why one data structure might be better than another depending on the problem. I also learned to break a program into smaller parts, such as file loading, searching, printing, and menu handling.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

This project improved the way I organize code. I used clear function names, comments, and separate responsibilities so each part of the program had a specific purpose. For example, the program has separate functions for trimming strings, converting input to uppercase, splitting file lines, loading courses, inserting into the tree, printing the course list, and searching for a course. This makes the code easier to read, test, update, and reuse in the future.

---

## Skills Demonstrated

- Data structure comparison
- Runtime and memory analysis
- Binary search tree implementation
- File input handling
- Input validation
- Menu-driven C++ programming
- Modular code design
- Readable and maintainable code
