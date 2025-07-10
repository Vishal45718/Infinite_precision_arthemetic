# Infinite Precision Arithmetic Library

This project implements an **Infinite Precision Arithmetic** library in C++ that supports operations on arbitrarily large integers and floating-point numbers with up to **100 digits of precision**.

## Features

- Arithmetic operations on large numbers:
  - **Integers**: Addition, Subtraction, Multiplication
  - **Floats**: Addition, Subtraction, Multiplication
- Handles numbers beyond built-in C++ data types
- Modular design using custom headers and .cpp files
- Built using object-oriented principles

##  File Structure

| File              | Description                                      |
|-------------------|--------------------------------------------------|
| `integer.cpp/hh`  | Base class for integer arithmetic                |
| `float.cpp/hh`    | Base class for float arithmetic                  |
| `intadd/intsub/intmul.cpp` | Integer operation implementations     |
| `floatadd/floatsub/floatmul.cpp` | Float operation implementations |
| `calculator.cpp`  | Entry point to test the arithmetic library       |
| `makefile`        | Compile and link the project                     |
| `libmy_inf_arith.a` | Static library archive                         |
| `my_inf_arith`    | Final compiled binary                            |
| `report.pdf`      | Detailed explanation and test cases              |

## 🚀 Usage

```bash
make          # Builds the library and executable
./my_inf_arith
