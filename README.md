# CircularContainer

A header-only, ring-buffer-like C++ container that supports fixed-capacity push/pop operations and 
arbitrary iterator-based insertion. When the container is full, it efficiently overwrites the oldest element, 
maintaining a constant maximum size while offering flexibility and iterator support.

## Table of Contents
1. [Features](#features)
2. [Repository Structure](#repository-structure)
3. [How It Works](#how-it-works)
4. [Public API](#public-api)
5. [Usage Example](#usage-example)
6. [Running the Tests](#running-the-tests)
7. [Contributing](#contributing)
8. [License](#license)

## Features
- **Fixed Capacity**: Holds up to `_capacity` elements while maintaining O(1) push/pop efficiency.
- **Automatic Overwrite**: If `push_back` is called on a full container, the oldest element is seamlessly removed to make space.
- **Custom Insertions**: Supports inserting elements at arbitrary positions using iterators.
- **Rich Iteration Support**:
    - Forward (`begin()`, `end()`) and reverse (`rbegin()`, `rend()`) iterators.
    - Constant versions (`cbegin()`, `crend()`).
- **Brace Initialization**: Allows direct initialization with C++17 deduction guides:
- **Header-Only Implementation**: Easily include the `.hpp` file with no additional linking required.
- **STL Compatibility**: Works seamlessly with STL algorithms like `std::sort`, `std::find`, and `std::copy`.

---

## Repository Structure
```
circular_container/
├── include/
│   └── CircularContainer.hpp    # Main header-only library
├── test.cpp                     # Test suite for validation
└── CMakeLists.txt               # CMake file for building
```

- **`include/CircularContainer.hpp`**: Core implementation of the container.
- **`test.cpp`**: Demonstrates various use cases and validates functionality.
- **`CMakeLists.txt`**: Build configuration for integrating and testing the project.

---

## How It Works

`CircularContainer` is implemented as a **ring buffer**, a data structure that uses a fixed-size array as a circular queue. Key design elements:

1. **Internal Buffer**:
    - An `std::array` of size `_capacity + 1` is used.
2. **Head and Tail Pointers**:
    - `m_head`: Points to the front element.
    - `m_tail`: Points to the next free slot for insertion.
3. **Behavior on Full Capacity**:
    - If the container is full, the `push_back` operation advances `m_head`, discarding the oldest element.
4. **Iteration**:
    - Iterators loop over the valid elements between `m_head` and `m_tail`, wrapping around the circular array.

---

## Public API
### Constructors
- **Default Constructor**:
  ```cpp
  CircularContainer<T, capacity>();
  ```
- **Brace Initialization** (C++17):
  ```cpp
  CircularContainer<int, 5> c{1, 2, 3, 4, 5};
  ```

---

### Capacity & State
| **Function** | **Description** |
|--------------|-----------------|
| `size()`     | Returns the number of elements in the container. |
| `capacity()` | Returns the maximum capacity of the container. |
| `empty()`    | Returns `true` if the container is empty. |
| `full()`     | Returns `true` if the container is full. |

---

### Modifiers
| **Function**          | **Description**                                             |
|-----------------------|-------------------------------------------------------------|
| `push_back(const T&)` | Appends an element, overwriting the oldest if full.         |
| `emplace_back(T&&)`   | Appends an element using move semantics.                    |
| `pop_front()`         | Removes the oldest element.                                 |
| `insert(iterator, const T&)` | Inserts an element at a specific position and shift others. |
| `clear()`             | Resets all elements.                                        |

---

### Iterators
| **Iterator Type** | **Description** |
|-------------------|-----------------|
| `begin()`, `end()` | Forward iterators for looping through elements. |
| `rbegin()`, `rend()` | Reverse iterators. |
| `cbegin()`, `cend()` | Constant forward iterators. |
| `crbegin()`, `crend()` | Constant reverse iterators. |

---

### Element Access
- **`front()`**: Returns the first element. Throws `std::out_of_range` if empty.
- **`back()`**: Returns the last element. Throws `std::out_of_range` if empty.

---
## Usage Example

### Example Code (`test.cpp`)
```cpp
#include "CircularContainer.hpp"
#include <iostream>

int main() {
    vfc::CircularContainer<int, 5> container;

    // Add elements
    container.push_back(10);
    container.push_back(20);
    container.push_back(30);

    std::cout << "Size: " << container.size() << "\n"; // 3
    std::cout << "Front: " << container.front() << "\n"; // 10
    std::cout << "Back: " << container.back() << "\n"; // 30

    // Add more elements
    container.push_back(40);
    container.push_back(50);
    container.push_back(60); // Overwrites 10

    std::cout << "Front after overwrite: " << container.front() << "\n"; // 20

    // Iterate through elements
    for (const auto& elem : container) {
        std::cout << elem << " "; // Outputs: 20 30 40 50 60
    }

    return 0;
}
```
---
## Running the Tests

```bash
g++ -std=c++17 test.cpp -o test && ./test
```

If everything is correct, it prints:
```
All tests passed!
```

Any failing assertion will abort the program with an error message.

---

## Contributing

We welcome contributions! Here's how to get involved:
1. Fork the repository and create a new branch.
2. Add new features or bug fixes.
3. Submit a pull request with a clear description of the changes.

---

## License

This project is licensed under the **MIT License**. See the [LICENSE](./LICENSE) file for details.

---

## Acknowledgments
Thank you for using CircularContainer! If you have any feedback or feature requests, feel free to open an issue.
