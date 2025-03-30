#pragma once 

#ifndef DMATH_COMPLEX_FUNCTIONS_HPP
#define DMATH_COMPLEX_FUNCTIONS_HPP

#include"complex.hpp"

NAMESPACESTART
//Complex logs
Dmath::Scalar logarithm(Dmath::Scalar logBase, Dmath::Scalar power);
Dmath::Complex complexLn(Dmath::Scalar power);
Dmath::Complex complexBaseLog(Dmath::Scalar logBase, Dmath::Scalar power);

//Exponents
Dmath::Complex complexExponent(Dmath::Scalar base, Dmath::Complex complexNum);


//Complex Trigonemetry

//basic trigfunctions
Dmath::Complex complexSine   (Dmath::Complex complexNum);
Dmath::Complex complexCosine (Dmath::Complex complexNum);
Dmath::Complex complexTangent(Dmath::Complex complexNum);


//the "other" tric functions

Dmath::Complex complexSecant(Dmath::Complex complexNum);
Dmath::Complex complexCosecant(Dmath::Complex complexNum);
Dmath::Complex complexCotangent(Dmath::Complex complexNum);


NAMESPACEEND

#endif //DMATH_COMPLEX_FUNCTIONS_HPP