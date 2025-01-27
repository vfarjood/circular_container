# CircularContainer Documentation

A header-only, ring-buffer-like C++ container that supports fixed-capacity push/pop
and arbitrary iterator-based insertion. When the container is full, a new push overwrites
the oldest element, maintaining a constant maximum size.

## Table of Contents
1. [Features](#features)
2. [Repository Structure](#repository-structure)
3. [How It Works](#how-it-works)
4. [Public API](#public-api)
5. [Usage Example](#usage-example)
6. [Building](#building)
7. [Running the Tests](#running-the-tests)
8. [Contributing](#contributing)
9. [License](#license)

## 1. Features
- **Fixed Capacity**: Holds up to `_capacity` elements.
- **Overwrite on Full**: If `push_back` is called when full, the oldest element is removed.
- **Insertion**: Insert elements at arbitrary iterator positions.
- **Iteration**: Provides `begin()`, `end()`, `rbegin()`, `rend()`, plus `const` versions.
- **Brace Initialization**: Thanks to a deduction guide, you can write
  `CircularContainer c{1,2,3}` in C++17 or later.
- **Header-Only**: Just include the `.hpp` file—no separate linking needed.

## 2. Repository Structure
```
your-repo/
├── CMakeLists.txt
├── include/
│   └── CircularContainer.hpp
└── test.cpp
```

- **include/CircularContainer.hpp**: This single-header library contains the entire CircularContainer implementation.
- **test.cpp**: Example usage and tests (assert-based) demonstrating ring-buffer functionality.
- **CMakeLists.txt**: A basic CMake configuration, allowing you to build the test or include CircularContainer as a third-party library.

## 3. How It Works
The container is implemented as a ring buffer with these key points:

1. **Internal Buffer**: `std::array<value_type, _capacity + 1>`
2. **Head (m_head) and Tail (m_tail) Indices**:
   - `m_head` marks the front element.
   - `m_tail` marks the slot after the last valid element.
3. **Size Tracking (`m_content_size`)**:
   - If `size() < capacity()`, `push_back()` just appends.
   - If `size() == capacity()`, `push_back()` overwrites the oldest item (increments `m_head`).
4. **Iteration**:
   - `begin()` / `end()` produce forward iterators.
   - `rbegin()` / `rend()` produce reverse iterators.
5. **Insertion**:
   - `insert(pos, value)` shifts elements `[end()..pos)` up by 1 and places the new item at `pos`.
   - If the container is full, the oldest item is removed when you insert or push more elements.

**Important**:
- `front()` / `back()` have undefined behavior if `empty()`.
- Decrementing `--end()` on an empty container is also undefined.

## 4. Public API

### A) Constructors
- `CircularContainer()`: Default constructor.
- Copy / Move constructors.
- Brace initialization with a deduction guide:
  ```cpp
  vfc::CircularContainer<int,5> c{1,2,3,4,5};
  ```

### B) Capacity & State
- `size()`: Returns the number of elements.
- `capacity()`: Returns `_capacity`.
- `empty()`: Returns `true` if `size == 0`.
- `full()`: Returns `true` if `size == capacity()`.

### C) Modifiers
- `push_back(const T&)` / `emplace_back(T&&)`: Appends an element, overwriting if full.
- `pop_front()`: Removes the front; if empty, calls `clear()`.
- `insert(iterator pos, const T&)` / `insert(iterator pos, T&&)`: Inserts an element before `pos`, shifting the ring. Overwrites oldest if full.
- `clear()`: Resets container to empty.

### D) Iterators
- `begin()`, `end()`, `cbegin()`, `cend()`: Standard forward iterators.
- `rbegin()`, `rend()`, `crbegin()`, `crend()`: Reverse iterators.

### E) Element Access
- `front()`, `back()`: Reference to the first / last element (undefined if empty).

## 5. Usage Example

### Example (`main.cpp`):
```cpp
#include "CircularContainer.hpp"
#include <iostream>

int main() {
    // Create a CircularContainer of capacity 5 for ints
    vfc::CircularContainer<int,5> c;

    // Push elements
    c.push_back(10);
    c.push_back(20);
    c.push_back(30);

    std::cout << "Size: " << c.size() << "\n";    // 3
    std::cout << "Front: " << c.front() << "\n"; // 10
    std::cout << "Back: " << c.back() << "\n";   // 30

    // Iterate
    for (auto &val : c) {
        std::cout << val << " ";  // 10 20 30
    }
    std::cout << "\n";

    // Fill up
    c.push_back(40);
    c.push_back(50);
    // Now it's full (size=5). Another push overwrites oldest
    c.push_back(60); // overwrites '10'

    std::cout << "New front: " << c.front() << "\n"; // 20
    std::cout << "New back: " << c.back() << "\n";   // 60

    return 0;
}
```

### Compile & Run:
```bash
g++ -std=c++17 main.cpp -o example && ./example
```

## 6. Building

There is a provided `CMakeLists.txt`. Follow these steps:

1. Clone or download this repository.
2. From the project root:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. This builds an executable (from `test.cpp`) that runs basic asserts to confirm correctness.

## 7. Running the Tests

After building with the above steps:
```bash
./test
```

If everything is correct, it prints:
```
All tests passed!
```

Any failing assertion will abort the program with an error message.

## 8. Contributing

- **Issues**: Please create GitHub issues describing bugs, steps to reproduce, or enhancement requests.
- **Pull Requests**: We welcome additions, such as more robust error handling, improved iteration logic, or specialized ring-buffer operations.

## 9. License

This project is distributed under the MIT License. See `LICENSE` for details.