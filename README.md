# Data Structures Performance Benchmarking

A cleaned portfolio version of my University of Tasmania data structures project in C.

The project models a many-to-many food-delivery relationship between customers and restaurants, then compares different storage/search approaches.

## Implementations

- Array + ordered linked lists
- AVL tree + ordered linked lists
- Hash table with separate chaining + ordered linked lists

## What the project demonstrates

- Linear search with arrays
- Balanced-tree insertion and lookup
- Hashing and collision handling
- Many-to-many relationship modelling
- Ordered singly linked lists
- Dynamic memory management
- Performance benchmarking across increasing dataset sizes

In my evaluation, the AVL-tree implementation performed best overall for the tested workload.

## Repository structure

```text
src/
  assoc_list.c / assoc_list.h
  array_m2m_db.c / array_m2m_db.h
  avl_m2m_db.c / avl_m2m_db.h
  hash_m2m_db.c / hash_m2m_db.h

examples/
  demo.c

Makefile
```

## Build and run

```bash
make
./data_structures_demo
```

Or:

```bash
make run
```

The demo initialises each implementation, inserts a sample customer and restaurant, creates a many-to-many order relationship, and confirms the operation succeeds.

## Skills demonstrated

`C` · `Arrays` · `Linked Lists` · `AVL Trees` · `Hash Tables` · `Algorithm Complexity` · `Performance Benchmarking` · `Memory Management`

## Note

This repository is a portfolio version of completed coursework. Assessment instructions, generated IDE files and submission-only material are intentionally excluded.
