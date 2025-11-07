# Dmath — Scientific Mathematics Library

Dmath is a  C++ mathematics library for scientific use that provides different types und functions for calculations in the fields of:  
 - Linear and Multilinear algebra 
 - Numeric functional calculus
 - Numeric vector calculus
 - Complex numbers and functions
 - Diffrential geometry
 - Set theory
 - And more 

The goal is to offer clear, self-contained implementations without external dependencies.

---

## Structure

The complete structure of this Project is based of basic mathmatical objects:

| Module  | Description | File|
|---------------|-------------|-----|
| `Vec2D`, `Vec3D` | Basic vector types with standard operations (dot/cross product, norms, etc.) |mathVector.hpp |
| `Matrix` | General matrix class |matrix.hpp|
| `Complex`  | Complex number utilities and polar form/derivative helpers | complex.hpp|
| `Vectorfunctions` | For Parametric curves and surfaces | vectorFunction.hpp |
| `MathFunction` | Function objects for different types of n-dimensional mathmatical functions | mathFunction.hpp|
| `Functional`| Mathmatical Functional (Function of funtions) and Calculus of Variations | mathFunctional.hpp|
| `Units`| A System for physical units| units.hpp |

*The library contains many more functionalities and data types. For further information, please read the documentation.*

Modules are independent and can be included as needed.

---

## Requirements:

- C++17

- Any standard compiler (clang++, gcc, or MSVC with minor adjustments)

- Windows operatingsystem

--- 

## Notes

- This library focuses on clarity and explicit implementation rather than performance tuning.

- The API is still evolving; function signatures may change.

- No external math libraries are required.
