# Data Structures Library
(A sample structure of readme file - will be updated later)

A C++ library implementing common data structures from scratch without using STL containers.

## Features

- Dynamic Array
- Linked List
- Hash Map
- Template-based implementation
- Rule of Three support

## Project Structure

```
.
├── include/
│   ├── DynamicArray.h
│   ├── LinkedList.h
│   └── HashMap.h
├── src/
├── tests/
├── README.md
└── LICENSE
```

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/username/data-structures-library.git
cd data-structures-library
```

### Compile

```bash
g++ main.cpp -o main
```

### Run

```bash
./main
```

## Example

```cpp
DynamicArray<int> arr;

arr.push_back(10);
arr.push_back(20);

cout << arr.get(0); // 10
```

## Time Complexities

| Operation | Complexity |
|------------|------------|
| push_back | O(1) amortized |
| insert | O(n) |
| remove | O(n) |
| get | O(1) |

## Author

Nilesh Sahu

## License
