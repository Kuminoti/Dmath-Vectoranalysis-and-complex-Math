#pragma once

#ifndef DMATH_FUNCTIONAL_CALCULUS_HPP
#define DMATH_FUNCTIONAL_CALCULUS_HPP

#include"mathFunction.hpp"
#include"Matrix.hpp"
#include"mathVector.hpp"
NAMESPACESTART


//Calculates the partialderivative of each variable and 
//Returns a vector made of it

// Nambla operator[ d/dx, d/dy, d/dz]
Dmath::Vec3D gradientVector(Dmath::TripleVarFunction func, Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar z);
Dmath::Vec2D gradientVector(Dmath::DoubleVarFunction func, Dmath::Scalar x, Dmath::Scalar y);

Dmath::Matrix<Dmath::Scalar> getHesseMatrixAt(Dmath::DoubleVarFunction func, Dmath::Scalar x, Dmath::Scalar y);

//Links functionOne inside functionOne
Dmath::SingleVarFunction functionalComposition(Dmath::SingleVarFunction funcOne, Dmath::SingleVarFunction funcTwo);
Dmath::SingleVarFunction functionAddition     (Dmath::SingleVarFunction funcOne, Dmath::SingleVarFunction funcTwo);

NAMESPACEEND


#endif