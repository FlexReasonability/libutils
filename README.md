# Utils Library

A C library that provides implementations for a generic linked list and stack, designed for dynamic data management and memory-safe operations.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
  - [Linked List](#linked-list)
  - [Stack](#stack)
- [Examples](#examples)
  - [Linked List Example](#linked-list-example)
  - [Stack Example](#stack-example)
- [License](#license)

## Installation

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/FlexReasonability/libutils.git
   cd libutils
   ```

2. Build the library:

   ```bash
   make
   ```

3. Run tests to verify the installation:

   ```bash
   make check
   ```

4. The library archive libutils.a will be created, ready to be linked to your C programs.

## Usage

### Linked List

The `LinkedList` structure provides a flexible, dynamically allocated list for generic data. Functions include adding, removing, retrieving elements, iterating, and performing transformations.

### Stack

The Stack structure provides a Last-In-First-Out (LIFO) stack with functions for adding, removing, and inspecting elements. It supports generic data.
