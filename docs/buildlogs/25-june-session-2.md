# Build Log - 2026-06-25 (Session 2)
## <div style="display:flex; justify-content:space-between;"> <span style="color:forestgreen;">Duration - 2:00pm to 6:00 pm</span><span>git commit -m <span style="color:forestgreen;font-size:17px;"> "better hasing implementation" </span> </span> </div>



# Objective

Today's objective was to redesign the custom `HashMap` implementation to make it more generic, extensible, and closer to the internal design of `std::unordered_map`.

The primary focus areas were:

* Designing a generic hashing system
* Supporting container hashing
* Exploring user-defined object hashing
* Understanding STL hash customization
* Improving the overall architecture of `HashMap`

---

# Work Completed

## 1. Redesigned the MyHash Infrastructure

Refactored the hashing system so that different data types can have their own specialized hashing logic.

Implemented specializations for:

* `int`
* `long long`
* `char`
* `std::string`
* `const char*`
* `LinkedList<T>`
* `DynamicArray<T>`

Each specialization now generates an appropriate hash value based on the stored data.

---

## 3. Learned Recursive Template Dispatch

Studied how template specialization works recursively.

Observed that:

```cpp
MyHash<T>{}(value);
```

does **not** call the same function every time.

Instead, the compiler automatically selects the appropriate specialization.

Examples:

```
T = int
→ MyHash<int>

T = std::string
→ MyHash<std::string>

T = LinkedList<int>
→ MyHash<LinkedList<int>>
```

This removed the need for manual type checking.

---

## 4. Experimented with Generic Object Hashing

Attempted multiple approaches for hashing arbitrary objects.

### Approach 1

Convert object address to pointer

↓

Convert pointer into string

↓

Hash the generated string

Later simplified this approach using

```cpp
reinterpret_cast<size_t>(&object);
```

to directly convert the object's address into an integer hash.

---

## 5. Studied reinterpret_cast

Learned how `reinterpret_cast` works internally.

Key learnings:

* Does not modify memory.
* Only changes how the compiler interprets existing bits.
* Safely converts pointer values into integer representations.
* Useful for pointer hashing.

Also learned why `static_cast` cannot perform pointer-to-integer conversions.

---

## 6. Tested Address-Based Hashing

Performed experiments using

```cpp
reinterpret_cast<size_t>(&object);
```

Observed that objects containing identical data but stored at different memory locations produce different hash values.

Example:

```
Student A
{id = 1}

Address:
0x1000
```

```
Student B
{id = 1}

Address:
0x2000
```

Even though both objects contain identical data, their hashes differ because their addresses differ.

---

## 7. Investigated Equality Problems

While testing custom object keys inside `HashMap`, encountered lookup failures even after successful insertion.

Root cause:

HashMap stores **copies** of keys.

Example:

```
Original Object

↓

Copied into Pair
```

Since the stored key becomes a different object, comparing addresses using

```cpp
this == &other
```

always returns false.

This explained why `get()` threw:

```
Key not found
```

even though insertion succeeded.

---

## 8. Studied STL HashMap Design

Researched how `std::unordered_map` is implemented.

Learned that STL separates two responsibilities:

* Hash Function
* Equality Function

Instead of directly depending on `operator==`.

Decided to redesign the custom implementation in the same way.

Target design:

```cpp
HashMap<
    Key,
    Value,
    Hash = MyHash<Key>,
    Equal = MyEqual<Key>
>
```

---


## 10. Updated Friend Declarations

Since the number of template parameters changed in `HashMap`, all related friend declarations had to be updated.

Modified friend declarations inside `LinkedList` to match the new template signature.

Resolved template parameter mismatch compilation errors.

---

# Problems Encountered

---

## Problem 1

### Error

```
no match for operator==
```

### Cause

Custom container keys did not implement `operator==`.

### Resolution

Implemented comparison operators for custom containers.

---

## Problem 2

### Error

```
specialization after instantiation
```

### Cause

Attempted to use `MyHash<std::string>` before its specialization was visible to the compiler.

### Resolution

Rejected the approach and redesigned the implementation.

---

## Problem 3

### Address-Based Hashing

The implementation technically worked but produced incorrect logical behavior.

Objects containing identical data generated different hashes because their memory addresses differed.

### Resolution

Rejected this approach for generic object hashing.

---

## Problem 4

### Address-Based Equality

Initially attempted

```cpp
this == &other;
```

for generic object comparison.

Observed that copied keys inside `HashMap` never match the original object.

### Resolution

Rejected this comparison strategy.

---

## Problem 5

### Unsupported Object Types

Introduced

```cpp
static_assert
```

inside the generic `MyHash` template.

Now unsupported object types immediately generate a compile-time error:

```
No hash defined for this type.
```

This behavior closely matches the design of `std::hash`.

---

## Problem 6

### Friend Template Errors

After increasing the number of template parameters in `HashMap`, old friend declarations became invalid.

Compiler error:

```
redeclared with 2 template parameters
```

### Resolution

Updated all friend declarations to match the new template signature.

---

# New Concepts Learned

* Recursive template specialization
* Partial template specialization
* Generic hash functors
* Container hashing
* Rolling hash technique
* Pointer hashing
* reinterpret_cast
* Default template arguments
* STL HashMap architecture
* Hash functors vs Equality functors
* Why HashMap requires both hashing and equality
* Compile-time validation using `static_assert`
* Template instantiation order
* Copy semantics and object identity
* Generic library architecture

---

# Design Decisions

## Accepted

* Recursive hashing for containers
* Separate hash specializations
* Default template parameters
* STL-style HashMap interface
* User-provided custom hash functors
* Future support for custom equality functors
* Compile-time diagnostics for unsupported key types

---

## Rejected

* Address-based hashing as a generic solution
* Pointer-to-string hashing
* Address-based equality (`this == &other`)
* Automatic hashing of arbitrary objects without user-defined logic

---

# Current Progress

### Completed

* Primitive hashing
* String hashing
* LinkedList hashing
* DynamicArray hashing
* Recursive hashing
* HashMap template redesign
* STL-style hash customization
* Investigation of object hashing limitations

---

### Next Goals

* Implement `MyEqual`
* Replace direct `operator==` usage with equality functors
* Fully support custom hash and equality policies
* Make `HashMap` behavior closely match `std::unordered_map`
* Continue improving generic container support

---

# Key Takeaways

Today's work focused primarily on architectural improvements rather than adding new data structures.

Several experimental approaches—including pointer hashing, address-based equality, and generic object hashing—were implemented, analyzed, and intentionally rejected after understanding their limitations.

The major outcome of today's work was redesigning the hashing system and `HashMap` architecture to closely follow the design philosophy of the C++ Standard Library, making the library more extensible, maintainable, and suitable for future custom data types.


