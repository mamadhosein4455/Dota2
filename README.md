# Dota2

A console-based **C++ student and course management system** developed using object-oriented programming and file-based data storage.

## Features

* **User account management**

  * Create accounts
  * Edit accounts
  * Delete accounts
  * Display accounts
  * Student and professor roles

* **Class management**

  * Create classes
  * Add students to classes
  * Remove students from classes
  * Edit student grades
  * Display class details

* **Homework management**

  * Create homework assignments
  * Assign grades to students
  * Display homework details

* **File-based data storage**

  * Account information stored in `accounts.txt`
  * Class information stored in `Classes.txt`
  * Homework information stored in `homework.txt`

## Technical Details

* **Language:** C++
* **Concepts:** Object-Oriented Programming, Inheritance, File I/O
* **Standard Library:** `fstream`, `sstream`, `vector`, `string`

## Main Classes

* `UUser` — User information and account properties
* `Admin` — Account management
* `Darss` — Class and student management
* `HomeWork` — Homework and grade management

## Project Structure

```text
Dota2/
│
├── main.cpp
└── README.md
```
