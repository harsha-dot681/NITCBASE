# NITCbase

NITCbase is a Relational Database Management System (RDBMS) implementation project developed at the National Institute of Technology Calicut. It is designed to help undergraduate students understand the internal architecture, data structures, and algorithms used in building a basic RDBMS by implementing it themselves in C++.

## Project Overview

NITCbase is organized into eight logical layers:

1. Physical Layer  
2. Buffer Layer  
3. B+ Tree Layer  
4. Block Access Layer  
5. Cache Layer  
6. Algebra Layer  
7. Schema Layer  
8. Frontend Interface

Each layer is built on top of the previous ones, gradually increasing in complexity and abstraction. The final system supports basic SQL-like operations including `CREATE`, `DROP`, `INSERT`, `SELECT`, `PROJECT`, `JOIN`, and B+ Tree indexing operations like `CREATE INDEX` and `DROP INDEX`.

### Note

NITCbase does not currently support concurrent transactions.

## Features

- Implementation in C++ on Unix/Linux
- Simulation of disk-based storage with block-level access
- Basic SQL-like query support via command-line interface
- B+ Tree based indexing
- Modular, layered system design for pedagogical clarity

## Components Provided

- A working command-line tool (`XFS Interface`) for interacting with a simulated file system
- `Disk.cpp` containing low-level disk access routines (`readBlock()` and `writeBlock()`)
- Class definitions (headers only) for:
  - Buffer Layer
  - Block Access Layer
  - Cache Layer
  - B+ Tree Layer
  - Schema Layer
  - Algebra Layer
  - Frontend Programming Interface
- Complete implementations of:
  - Frontend User Interface
  - Physical Layer (`Disk.cpp`)
- Roadmap documentation with tutorials and algorithmic descriptions for each layer
- B+ Tree operation tutorials and design documents

## Layer Summary

### Physical Layer
- Complete code provided
- Interfaces directly with the simulated disk

### Buffer Layer
- Implements disk caching with LRU replacement
- Provides abstraction over disk I/O

### B+ Tree Layer
- Indexing support for efficient query operations
- Requires implementation of insert and search algorithms

### Block Access Layer
- Core implementation of `SELECT` and `PROJECT`
- Supports basic relational operations

### Cache Layer
- Manages in-memory metadata for open relations and attributes

### Algebra Layer
- Implements `INSERT`, `SELECT`, `PROJECT`, and `JOIN`
- Delegates operations to the Block Access Layer

### Schema Layer
- Implements Data Definition Language (DDL) commands like `CREATE` and `DROP`
- Interfaces with Cache and Block Access Layers

### Frontend Interface
- Interprets user input and calls appropriate backend methods
- Split into:
  - User Interface: fully implemented
  - Programming Interface: partial implementation (to be completed)

## Getting Started

1. Use a Unix/Linux system with a C++ compiler
2. Begin with the roadmap document and complete each phase step by step
3. Refer to the layer-specific documentation and tutorials as needed
4. Build and test using the provided `XFS Interface`

## Prerequisites

- Strong understanding of C++ and data structures
- Familiarity with basic RDBMS concepts
- Working knowledge of file systems and command-line environments

## Outcome

At the end of this project, you will have implemented a fully functional, modular RDBMS system in C++ consisting of roughly 3000 lines of code. You will have gained deep insight into the internal mechanisms of relational databases, including storage management, query execution, indexing, and buffer management.

## License

Creative Commons License  
Copyright © 2025  
National Institute of Technology Calicut

## Acknowledgements

- Faculty and contributors from the Computer Science Department, NIT Calicut
- Students and developers who tested and documented the system
