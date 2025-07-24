# Search Suggestion Engine using Trie and Min-Heap

This project implements a fast and efficient search suggestion system using Trie and Min-Heap data structures. It simulates how e-commerce platforms suggest search terms based on user input and keyword frequency.

## Features

- Prefix-based search suggestions using Trie
- Frequency-based ranking using a Min-Heap
- CLI interface for adding, searching, and suggesting keywords
- Data persistence through a simple text file (`keywords.txt`)
- Efficient performance with O(n) prefix lookups

## Technologies Used

- C++17
- STL: strings, vectors, queues, priority queues
- Trie and Min-Heap implementations
- File I/O for keyword storage

## Folder Structure

```
SearchSuggestionEngine/
├── include/
│   ├── search_engine.h
│   └── trie.h
├── src/
│   ├── main.cpp
│   ├── search_engine.cpp
│   └── trie.cpp
├── data/
│   └── keywords.txt
├── README.md
```

## How to Compile and Run

From the root directory:

### Compile

```
g++ -std=c++17 -Wall -Iinclude src/main.cpp src/search_engine.cpp src/trie.cpp -o search_engine.exe
```

### Run

```
./search_engine.exe
```

## Sample CLI Usage

```
Commands: add | search | suggest | stats | exit

> suggest
Prefix: mo
How many suggestions (default 5): 3

Suggestions for 'mo':
1. mobile (25)
2. mouse (14)
3. monitor (8)
```

## Use Case

This kind of suggestion system is commonly used in e-commerce platforms to improve search experience. This implementation is meant to simulate that logic and serve as a learning tool for working with Trie structures, priority queues, and file handling in C++.

## Notes

This was built as a personal project to explore how search autocomplete systems work internally. Suggestions are stored in memory and updated on disk after each operation.
