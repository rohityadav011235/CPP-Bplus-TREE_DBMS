# 🎓 University Data Management System (Custom DBMS)

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg) ![Language: C++](https://img.shields.io/badge/Language-C++-blue.svg) ![Architecture: B+Tree](https://img.shields.io/badge/Architecture-B%2B%20Tree-green.svg)

A high-performance, file-based Database Management System (DBMS) built from scratch in C++. 
This project implements a **B+ Tree** for indexing and uses a **File System** for persistent storage, mimicking real-world database architectures like MySQL or PostgreSQL.

---

## 🚀 Features
* **B+ Tree Indexing:** Utilizes a custom B+ Tree algorithm for optimized **$O(\log n)$** search complexity.
* **Persistent Storage:** Student data (Name, Age, Course) is serialized and saved to disk (`.txt` files), ensuring data persists after the program closes.
* **Crash Handling:** Implements robust input sanitization (`cin.fail()`) to prevent infinite loops on invalid user inputs.
* **CRUD Operations:** Supports Adding students with duplicate checks and Searching records efficiently.
* **Balanced Architecture:** Automatically handles node splitting and merging to keep the tree balanced.

---

## 🛠️ Tech Stack
* **Language:** C++ (Standard Template Library)
* **Data Structure:** B+ Tree (Degree `t=3`)
* **Algorithm:** B-Tree Splitting & Merging ("Traffic Sign" Logic)
* **Storage:** File I/O (`fstream`) for persistent data
* **Environment:** Compatible with GCC/G++ compilers (Windows/Linux/Mac)

---

## 📸 Project Demo & Walkthrough

### 1. Data Entry & Input Validation
*The clean CLI interface allows users to add student records. The system handles input validation to prevent crashes (e.g., ensuring IDs are numbers).*
![Input Demo](demo_input.png.png)

### 2. B+ Tree Visualization & Search
*The "Show Tree" feature visualizes the balanced structure in memory. The Search function then uses this index to instantly locate and retrieve the persistent student file.*
![Tree and Search Demo](demo_tree_search.png.png)

---

## 🧠 System Architecture (How It Works)

This system separates **Indexing** from **Data Storage** to maximize efficiency. Below are diagrams visualizing the actual state of the system with sample data (IDs 111–1000).

### 1. Visualizing the Current B+ Tree State
* **Internal Nodes (Orange):** Act as "traffic signs" to guide traversal. They do not store data pointers.
* **Leaf Nodes (Blue):** Store the actual keys and link to the persistent text files. They are linked horizontally to allow efficient range queries.

```mermaid
graph TD
    %% Styling
    classDef internalNode fill:#f96,stroke:#333,stroke-width:2px,color:white;
    classDef leafNode fill:#aaddff,stroke:#333,color:black;
    classDef fileSystem fill:#eee,stroke:#999,stroke-dasharray: 5 5;

    %% Root Node (Quoted to fix PIPE error)
    Root(("Root: 333 | 666")):::internalNode

    %% Leaf Nodes
    L1[Leaf: 111, 222]:::leafNode
    L2[Leaf: 444, 555]:::leafNode
    L3[Leaf: 777, 888, 999, 1000]:::leafNode

    %% Connections
    Root -->|Keys < 333| L1
    Root -->|Keys 333-666| L2
    Root -->|Keys > 666| L3

    %% Leaf Links
    L1 -.-> L2
    L2 -.-> L3

    %% Files
    File1(File: 111.txt):::fileSystem
    L1 --- File1
