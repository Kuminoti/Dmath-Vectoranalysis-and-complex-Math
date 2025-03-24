#pragma once

#ifndef DMATH_COMPLEX_HPP
#define DMATH_COMPLEX_HPP

#include"mathVector.hpp" //To convert the data from the complex plane to a vector in cartesian coordinates
#include"dFunctions.hpp" //Helper function

/* File include/Complex.hpp 
 * This File contains a class for Complex Numbers und fitting mathmaticals operations
 *
 * Z = aX + ib => ∀( a,b ) ∈ R; i ∈ Q ; i² = -1
*/



NAMESPACESTART //Dmath:: - namespace

class Complex{

private:
    //real and imaginary parts
    double real;
    double img;

    
    double absolute; //The "distance" from the coordinate origin
    double phaseAngle = 0;

    //Calculates the angle and abs after a manipulations
    void update();

public:

    Complex();                          //default Constructor
    Complex(double real, double img);   


    //getters
    double getRealPart();
    double getImaginaryPart();
    double getAbsolute();


    //Adders

    //Adds img to the imaginary part : x + (iy + iimg)
    void addImaginary(double img);
    void addReal(double real);

    void setNumber(double real, double img);

    //Setters for the real and imaginary part
    void setImaginaryPart(double img);
    void setRealPart(double real);

    void conjugate();

    //Logic operators
    bool operator==(Complex num);
    bool operator!=(Complex num);

    bool operator==(Dmath::Scalar num);
    bool operator!=(Dmath::Scalar num);
    

    bool operator< (Complex num);
    bool operator> (Complex num);
    bool operator<=(Complex num);
    bool operator>=(Complex num);


    bool operator< (Dmath::Scalar num);
    bool operator> (Dmath::Scalar num);
    bool operator<=(Dmath::Scalar num);
    bool operator>=(Dmath::Scalar num);

    //Mathmatical operators
    Complex operator+(Complex num);
    Complex operator-(Complex num);

    Complex operator*(Complex num);
    Complex operator/(Complex num);

    Complex& operator+=(const Complex& num);
    Complex& operator-=(const Complex& num);

    Complex exp(); //e^this

    //Returns a vector in Cartesian coordinats with the real and imaginary parts on the complex plane as x and y coordinates
    Dmath::Vec2D getVector();

    CoordinateSystem2D polarForm();

};

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

#endif