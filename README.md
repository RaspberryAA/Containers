# s21_containers

**s21_containers** is a custom C++17 implementation of STL-like containers, written from scratch without using the Standard Template Library. The project replicates STL logic, structure, and behavior, with full test coverage and bonus features.

---

## Features

- Containers: `list`, `vector`, `map`, `set`, `stack`, `queue`
- Bonus containers: `array`, `multiset`
- Template-based classes
- Iterator support
- Namespace: `s21`
- STL-like behavior: memory handling, exceptions, boundary checks
- Bonus: `insert_many`, `insert_many_back`, `insert_many_front`

---

## Project Structure

```
src/
├── array/          # array implementation
├── list/           # list implementation
├── map/            # map implementation
├── multiset/       # multiset implementation
├── queue/          # queue implementation
├── rbTree/         # red-black tree base
├── set/            # set implementation
├── stack/          # stack implementation
├── vector/         # vector implementation
├── tests/          # unit tests per container
s21_containers.h     # main container header
s21_containersplus.h # bonus containers header
Makefile             # build and test script
```

---

## Build and Run

```bash
make         # Build the project and run unit tests with coverage report
```

---

## Technologies Used

- **Language**: C++17
- **Testing**: Google Test (GTest)
- **Build**: Makefile
- **Code Style**: Google C++ Style Guide

---

## Bonus - insert_many Methods

Extended modifiers for inserting multiple elements using parameter packs:

| Method                     | Applies to                    |
|---------------------------|-------------------------------|
| `insert_many(pos, args)`  | `list`, `vector`              |
| `insert_many_back(args)`  | `list`, `vector`, `queue`     |
| `insert_many_front(args)` | `list`, `stack`               |
| `insert_many(args)`       | `map`, `set`, `multiset`      |

---

## Tests

Each container and its methods are covered by unit tests using the GTest framework. Tests are located in the `src/tests/` folder and named accordingly:

- `vector_test.cc`
- `list_test.cc`
- `map_test.cc`
- etc.


```bash
make test # to execute all test cases.
```


---

## Notes

- `map`, `set`, and `multiset` are implemented using a custom red-black tree (`rbTree`)
- `list` is implemented as a doubly-linked list, not using arrays
- Shared logic is modularized where appropriate (e.g., stack and queue, list and vector)
- No STL headers or functionality were used or copied

---
