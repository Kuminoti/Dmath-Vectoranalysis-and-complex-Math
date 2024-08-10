# Math Library for vectors and more dimensional analysis

This is a simple C++ library for vector mathematics, vector analysis, and differential geometry, providing classes for 2D and 3D vectors, and the creation of more complex mathematical vector objects like vectorial parametric curves.

## Introduction to Vectors and Vector Analysis

### Description of a Vector
A mathematical vector is an ordered set of numerical values that represents a directed quantity, typically in 2D or 3D space, characterized by its magnitude (length) and direction. It can be visualized as an arrow extending from an origin to a point in space, with its length indicating the magnitude and its direction indicating the orientation in space. Vectors are fundamental in various mathematical fields, including linear algebra, geometry, and physics.

### Vector Analysis Overview

Vector analysis deals with mathematical operations and concepts involving vectors, such as addition, subtraction, scalar multiplication, dot products, cross products, and calculus operations like differentiation and integration in vector spaces.

The Vector Math Library (Vectormath) consists of two main classes: Vec2D for 2D vectors and Vec3D for 3D vectors. These classes offer functionality for basic vector operations and support different coordinate systems, including Cartesian, polar, spherical, and cylindrical coordinates. A class called CoordinateSystem is used to build a simple abstraction and provide basic functionality.

## Coordinate Systems

The library allows you to work with different coordinate systems by defining the desired standard coordinate system using preprocessor directives. Available coordinate systems are:

- Cartesian 2D (CARTESIAN_IS_2D_STANDARD) (X: ; Y: )
- Polar (POLAR_IS_STANDARD) (r: ; φ: )

- Cartesian 3D (CARTESIAN_IS_3D_STANDARD) (X: ; Y: ; Z: )
- Spherical (SPHERE_IS_STANDARD) (r: ; φ: ; θ: )
- Cylindrical (CYLINDER_IS_STANDARD) (r: ; φ: ; h: )  
### r(Radius)  
### φ(Phi): angle one  
### θ(Theta): angle two  
### h(height)  

You can define which coordinate system to use by uncommenting the corresponding preprocessor directive in the header file.

## Classes

### Vec2D

The Vec2D class represents a 2D vector. It provides methods for basic vector operations and supports both Cartesian and polar coordinate systems. 
Most methods are inherited of the Coordinatesystem2D class in the systems.hpp file

#### Constructors
- Vec2D(double XY): Constructs a 2D vector in Cartesian coordinates with the same X and Y value.
- Vec2D(double X, double Y): Constructs a 2D vector in Cartesian coordinates with the given X and Y components.
- Vec2D(double X, double Y, double originX, double originY): Constructs a 2D vector in Cartesian Coordinates with a defined non-zero start point.
- Vec2D(double radius, double angle): Constructs a 2D vector in polar coordinates with the given radius and angle.

#### Methods

- Length(): Calculates the length of the vector.
- DotProduct(Vec2D MathVector): Calculates the dot product of this vector with another vector.
- CalcAngle(Vec2D MathVector): Calculates the angle between this vector and another vector.
- Getters and setters for vector components.
- ZeroVector(): Returns a vector with a length of zero.

### Vec3D

The Vec3D class extends Vec2D to represent 3D vectors. It provides additional methods for vector operations in 3D space and supports Cartesian, spherical, and cylindrical coordinate systems.

#### Constructors
- Vec3D(double XYZ): Constructs a 3D vector in Cartesian coordinates with the same X and Y value.
- Vec3D(double X, double Y, double Z): Constructs a 3D vector in Cartesian coordinates with the given X, Y, and Z components.
- Vec3D(double radius, double phi, double theta): Constructs a 3D vector in spherical coordinates with the given radius, phi, and theta.
- Vec3D(double radius, double phi, double height): Constructs a 3D vector in cylindrical coordinates with the given radius, phi, and height.

#### Methods
- Methods inherited from CoordinateSystem3D.
- Additional methods for vector operations in 3D space.
- Methods to convert between different coordinate systems.

## Absolute and Relative Coordinates

Vectors with origins other than zero possess both absolute and relative coordinates. For instance, consider the vector [0;2], which begins at Y = 2. Its absolute Y-coordinate is 4, as it starts at 2 and extends 2 units upward to reach Y = 4. In the code, these absolute coordinates are called aX and aY.  
There are methods for interacting and working with these Vectors:   
- CalcDistance(): calculates the distance between Vectors
- MoveVectorX(double move): Moves the vector in a specific x-direction
- MoveVectorY(double move): Moves the vector in a specific y-direction
- MoveVector(double moveX, double moveY): Moves the vector in a specific x and y direction
- GetAX(): Gets the absolute X coordinate from a vector with a non-zero start
- GetAY(): Gets the absolute X coordinate from a vector with a non-zero start
- GetDistanceToZero(): Gets the distance to [ 0 ; 0 ] from a vector with a non-zero start
- SetOriginX(double newOriginX): Sets the y-Origin to a specific value
- SetOriginY(double newOriginY): Sets the y-Origin to a specific value

#### Basic Operators: + - *

- Vec2D and Vec3D support addition, subtraction, and multiplication.
- Addition + : Returns a vector from the addition of two vectors Vx = (X1 + X2); Vy = (Y1 + Y2)
- Subtraction - : Returns a Vector from the subtraction of two Vectors Vx = (X1 - X2); Vy = (Y1 - Y2)
- Multiplication * : Returns the scalar (or dot) product of two vectors.

## Basic geometric operations in a Coordinate System

### The SystemGeometry class

The `SystemGeometry` class provides functionality for calculating specific properties of coordinate systems, such as:

- Area and circumference of a polar coordinate system, based on the system's properties like radius.
- Volumes and surfaces of sphere and cylinder systems.
- Cuboid volume based on three vectors.

### Methods

- `cylinderSystemVolume(Dmath::Vec3D vector)`:  
  Calculates the volume of a cylinder coordinate system based on the given vector.

- `cylinderSystemSurface(Dmath::Vec3D vector)`:  
  Calculates the surface of a cylinder coordinate system based on the given vector.

- `cylinderSystemLateralSurface(Dmath::Vec3D vector)`:  
  Calculates the lateral surface of a cylinder coordinate system based on the given vector.

- `sphereSystemVolume(Dmath::Vec3D vector)`:  
  Calculates the volume of a sphere coordinate system based on the given vector.

- `sphereSystemSurface(Dmath::Vec3D vector)`:  
  Calculates the surface of a sphere coordinate system based on the given vector.

- `cuboidVolume(Dmath::Vec3D mainVector, Dmath::Vec3D MathVector, Dmath::Vec3D MathVectorTwo)`:  
  Creates a cuboid based on the three given vectors and returns its volume.

- `cuboidSurface(Dmath::Vec3D mainVector, Dmath::Vec3D MathVector, Dmath::Vec3D MathVectorTwo)`:  
  Creates a cuboid based on the three given vectors and returns its surface.  

# Differential Geometry

## Simple Description of Differential Geometry

Differential geometry extends the principles of calculus to the study of curves, surfaces, and higher-dimensional spaces. It focuses on properties that remain invariant under transformations, such as curvature, torsion, and tangent vectors. In the context of the provided code, differential geometry is used to analyze the behavior of vectorial described parametric curves, including determining their tangent vectors, calculating slopes, and measuring lengths and much more. It provides tools for understanding the geometric properties of curves and surfaces and enables the study of their intrinsic and extrinsic characteristics. Differential geometry plays a fundamental role in fields such as physics, engineering, and computer graphics, where precise geometric descriptions are essential.  
**This part of the library is not finished and primarily experimental and might not be optimised and can have buggs; new features, bug fixes and optimizations will come soon.**
  
## Representations of Curves

### Code Representation of Curves

Different types of classes exist for various curves, but essentially, every curve is represented by a `std::vector` filled with mathematical vectors. These vectors encompass length, direction, and the previous origin, collectively defining a curve. The `std::vector` is populated by a specific algorithm, which generates all necessary data based on input parameters.

A curve in this library necessitates three elements:

- **Functions for Every Component:** Within the class, represented by `std::function` objects, the `xFunc` and `yFunc` (and optionally `zFunc`) are required.
- **A Range:** The curve requires a specific range, delineating from where to where it is calculated. This is symbolized within the class by `systemStart` and `systemStop`.
- **A Resolution:** Since computers cannot compute infinitely small data, the curve is calculated in steps with a specific value.

The range and resolution of curves are standardized across all classes:
- `systemStart` is set to 0.
- `systemStop` is set to (2PI).
- `resolution` is set to 0.1.

### Different Ways to Represent a Curve

#### Function Graphs

A function graph assigns each element from the set of definitions \(D\) a corresponding value in the set of real numbers \(\mathbb{R}\):
f: D → ℝ , x → f(x)

A popular example is the parabola, represented by the quadratic function:
f(x) = x²

#### Parametric Curves

A parametric curve is a mathematical representation of a line or path in space, where the position of a point on the curve is described as a function of one or more parameters:  
 [A, B] → ℝ, t ↦ (x(t), y(t))  

These parameters can represent time or any other independent variable. The function defines the coordinates of each point along the curve as a function of these parameters. In a two-dimensional space, for instance, a parametric curve can be defined by describing the \(x\) and \(y\) coordinates of a point as functions of a parameter (t), such as:  
[x = f(t), y = g(t)]

This dynamic description allows for a varying path of the curve as the parameter (t) changes. Within this library, the curve's data along the (x) and (y) (and (z), if applicable) axes is encapsulated within a vector structure, representing the curve as an aggregation of vectors aligned with the tangent direction at specific points.

### Code Representation of Parametric Curves

A parametric curve can be described as a series of mathematical vectors. To create such a curve, utilize the `VectorCurve2D` class for 2D systems or the `VectorCurve3D` class for 3D systems.

Two static methods facilitate the creation of `VectorCurve2D` or `VectorCurve3D` objects:

- `VectorCurve2D createStandardCurve(std::function<double(double)> funcX, std::function<double(double)> funcY)`:
   - Creates a curve with predefined standards, requiring only the functions for the (x) and (y) (and (z)) components.
   - Returns a `VectorCurve` object.

```cpp
// Your main.cpp

#include<iostream>
#include"VectorCurve.hpp"

// Sine function (x(t) = sin(t))
auto sinFunc = [](double x) -> double { return std::sin(x); };

// Cosine function (y(t) = cos(t))
auto cosFunc = [](double x) -> double { return std::cos(x); };

// Creation of a simple vector curve in parametric representation
Dmath::VectorCurve2D myCurve = Dmath::VectorCurve2D::createStandardCurve(sinFunc, cosFunc);

int main(int argc, char** argv){

  // Get the x value at t = 2
  std::cout << myCurve.getDataAtX(2) << std::endl;

  // Get the y value at t = 2
  std::cout << myCurve.getDataAtY(2) << std::endl;

  return EXIT_SUCCESS;
}
```

  
With this example a curve will be created like this: 
*An oversimplefied demonstration:*  
**[curveStart, curveEnd] → ℝ, t ↦ (sinFunc, cosFunc)**  

### **VectorCurve2D Class Methods**

The vectorCurve classes contain a lot of mathmatical operations and functionalities:

- Dmath::Vec2D getVectorFromFunction(double vecX, double vecY);
    - Description: Returns a vector calculated from the x and y functions of the class
    - Input: the x value and the y value (input args for the xFunc and yFunc)
    - Return: A new 2D vector with X = this->xFunc(vecX) and Y = this->yFunc(vecY)  
         
- Dmath::Vec2D getVectorFromPoint(double point);                  
    - Description: Returns a vector on the point t
    - Input: the point t.
    - Return: A new 2D vector with X = this->xFunc(point) and Y = this->yFunc(point)
- Dmath::Vec2D getVectorFromStdVec(size_t index);
    - Returns a specific element of the std::vector
    - Input: The number or index of the wanted element
    - Return: The Vector at index ...  this->maincurve[ index ];




### Inpricid curves

A curve can also be described by one or more equations in the coordinates. An Example for this can be the equation:  
  
X² + Y² = 1  

this eqation describes the unit circle on the plane.

#### Code representation
An impliced curve can be 









