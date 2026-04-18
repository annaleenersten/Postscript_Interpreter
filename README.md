# PostScript Interpreter (C++)

## Overview

This project is a simplified PostScript interpreter implemented in C++. It supports:

* Operand stack and dictionary stack
* Built-in operators (arithmetic, stack, string, boolean, control flow)
* User-defined functions (`def`)
* Code blocks (`{ ... }`)
* **Dynamic and Static scoping**

---

## Requirements

* C++17 compatible compiler
* CMake (version 3.10 or higher)

---

## Build Instructions (CMake)

From the root of the project:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

After building, the `build/` directory will contain:

- `ps_interpreter` → interactive REPL
- `runTests` → GoogleTest test executable

---

## Running the Interpreter

From the `build` directory:

```bash
./ps_interpreter
```

You will see the REPL prompt:

```
REPL>
```

---
## Running Tests

This project uses **GoogleTest** for unit testing, integrated with CMake and CTest

<br>

Run the test executable directly (recommended):

```bash id="gtest3"
./runTests
```

or use CTest:

```bash id="gtest2"
ctest
```

---

## Example Usage

### Arithmetic

```
REPL> 3 4 add
OP_STACK = [ 7 ]
```

### Variables

```
REPL> /x 10 def
REPL> x
OP_STACK = [ 10 ]
```

### Functions

```
REPL> /square { dup mul } def
REPL> 5 square
OP_STACK = [ 25 ]
```

---

## Scoping Modes

The interpreter supports:

* **Dynamic Scoping** (PostScript default)
* **Static Scoping**

### How to switch

In `interpreter.cpp`, modify:

```cpp
bool STATIC_SCOPING = true;
```

* `true` → Static scoping
* `false` → Dynamic scoping

Rebuild the project after changing this value.

---

## Scoping Example

```
/x 10 def
/g { x } def

1 dict begin
    /x 20 def
    g
end
```

Expected output:

* Dynamic → `20`
* Static → `10`

---