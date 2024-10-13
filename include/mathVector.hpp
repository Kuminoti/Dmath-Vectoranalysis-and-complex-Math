#pragma once
#pragma region FILE
#ifndef VECTORMATH_H
#define VECTORMATH_H //include guard

/*
 * File: include/mathVector.hpp
 * This File contains the classes for 2D and 3D Vectors and all importent mathmatical
 * and geometric operations
 * 
 */


#include "systems.hpp" //Vec2D and Vec3D inherit form Coordinatesystem2D and ...3D

#ifdef SYSTEM_READY //Checks if all the right coordinatesystem is selected
#include<iostream>


#include"systemGeometry.hpp"
NAMESPACESTART

#pragma region Vec2D
class Vec2D : public CoordinateSystem2D {                          //CoordinateSystem2D contains the actual coordinates for cartesian and polar systems
  private: //Private members
    double abs;                                                    // The absolute value or lenght of a vector
    double distanceToZero;   
    double vectorRotation; 

    void calcAbs();                                                // Calculates the absolute value
    void ValidManipulation();

  public: // Basic operrator overloading:
    
    //Mathmatical operators
    Vec2D  operator*(const double scalarValue);                    //Multiplys x and y by scalarValue   
    Vec2D  operator/(const double scalarValue);                    //divides all components of the Vector with the scalar value and returns it
    Vec2D  operator+(const Vec2D& Mathvector);                     //Basic Vector addition
    Vec2D  operator-(const Vec2D& Mathvector);                     //Basic Vector subtractions
    double operator*(const Vec2D& Mathvector);                     //Calculates the dotproduct of two vectors


    void operator+=(Dmath::Duo<double, double> data);              // this x-value + Duo.one ; this y-value + Duo.two
    void operator-=(Dmath::Duo<double, double> data);              // this x-value - Duo.one ; this y-value - Duo.two
    void operator*=(Dmath::Duo<double, double> data);              // this x-value * Duo.one ; this y-value * Duo.two
    void operator/=(Dmath::Duo<double, double> data);              // this x-value / Duo.one ; this y-value / Duo.two
    

    void operator+=(Dmath::sVec2f vec);                            // this x-value + sVec.x; this y-value + sVec.y 
    void operator-=(Dmath::sVec2f vec);                            // this x-value - sVec.x; this y-value - sVec.y
    void operator*=(Dmath::sVec2f vec);                            // this x-value * sVec.x; this y-value * sVec.y
    void operator/=(Dmath::sVec2f vec);                            // this x-value / sVec.x; this y-value / sVec.y

    void operator+=(double scalar);                                // this y-value + scalar; this y-value + scalar
    void operator-=(double scalar);                                // this y-value - scalar; this y-value - scalar
    void operator*=(double scalar);                                // this y-value * scalar; this y-value * scalar
    void operator/=(double scalar);                                // this y-value / scalar; this y-value / scalar


    void operator+=(Vec2D vec);                                    // this x-value + vec.X  ; this y-value + vec.x
    void operator-=(Vec2D vec);                                    // this x-value - vec.X  ; this y-value - vec.x
    void operator*=(Vec2D vec);                                    // this x-value * vec.X  ; this y-value * vec.x
    void operator/=(Vec2D vec);                                    // this x-value / vec.X  ; this y-value / vec.x


    void operator++();                            //Adds 1 to the x and y coordinate
    void operator--();                            //Adds 1 to the x and y coordinate

    //Logic operators
    inline bool operator==(Vec2D& Mathvector);   // == checks if the x and y coordinates are the same
    inline bool operator!=(Vec2D& Mathvector);   // != checks if the x and y coordinates are diffrent
    inline bool operator>=(Vec2D& Mathvector);   // >= checks if the lenght of the vector is greater or equal
    inline bool operator<=(Vec2D& Mathvector);   // <= checks lenght ...
    inline bool operator<(Vec2D& Mathvector);    // lenght1 < lenght2 ... 
    inline bool operator>(Vec2D& Mathvector);    // ""


  public: //Public Constructors
#ifdef CARTESIAN_IS_2D_STANDARD
    Vec2D() = default;                                          //Default constructor (duh...)
    Vec2D(double XY);                                           // creates a Vector with the same x and y value
    Vec2D(double X, double Y);                                  // basic x and y vector
    Vec2D(double X, double Y, double originX, double originY);  // crates a vector with a specific non zero startpoint
#endif // CARTESIAN_IS_2D_STANDARD

#ifdef POLAR_IS_STANDARD
    Vec2D(double radius, double phi);                           // Creates a Vector in a polar coordinatesystem
#endif // POLAR_IS_STANDARD

   virtual ~Vec2D() = default;

  public: //getters and setters

    /* Setters:
     * If data is set/changed it will automaticly change the values for other
     * coordinate types as well.
     */

    double getRotationAngle();                            // Gets the rotation angle for rotated vectors
    double getAbs();                                      // Calculates the absolutvalue
    double getLenght();                                   // Calculates the length of a vector

    
    void setX(const double value);                        // Basic x setter
    void setY(const double value);                        // Basic y setter
    void setPhi(const double value);                      // Setter for the angle in a polar system
    void setAll(const double value);                      // Sets ALL values to...
    void setRadius(const double radius);                  // Setter for the radius in a polar system
    


  public: //Mathmatical operations

    double dotProduct(Vec2D Mathvector);                  // Calculates Scalar product
    double calcAngle(Vec2D Mathvector);                   // Calculates the angle between 2 vectors
    double distance(Vec2D Mathvector);                    // Calculates the distance between vectors
    void normalize();                                     // Divides the vectors components though its length

    // You can use methods instead of overloaded operators
    Vec2D add(Vec2D Mathvector);                          // Adding 2 vectors
    Vec2D subtract(Vec2D Mathvector);                     // Subtract 2 vectors
    Vec2D rotateVector(double radians);                   // Rotates a vector dependent op the angle

  public: //Geometric operations                 
    double polarSystemArea();                             // Calculates the circle of a polar system
    double polarSystemCircumfrance();                     // Calculates the circumfrance of a polar system
    double rectangleArea(Vec2D MathVector);               // Calculates the area of a rectangle
    double rectangleCircumfrance(Vec2D MathVector);       // Calculates the circumfrance of the rectangle

  public: //vector manipulation
   
 
    void addToX(double add); // X + add
    void addToY(double add); // Y + add


    void addXYEach(double xPlus, double yPlus);           //* X + xPlus     || Y + yPlus
    void divideXYBy(double xDivBy, double yDivBy);        //* X / xDivBy    || Y / yDivBy
    void multilpyXY(double xTimes, double yTimes);        //* X * xTimes    || Y * yTimes
    void subtractXY(double xMinus, double yMinus);        //* X - xMinus    || Y - yMinus

    void addToThis(double add);                           //* X + add       ||  Y + add
    void substractThis(double subtract);                  //* X - subtract  ||  Y - subtract
    void multipyThisBy(double factor);                    //* X * factor    ||  Y * factor

    void subtractFromX(double subtract);                  //* X - subtract  ||  
    void subtractFromY(double subtract);                  //* Y - subtract  ||
    
    void multiplyXBy(double factor);                      //* X * factor    ||
    void multiplyYBy(double factor);                      //* Y * factor    ||
     
    void divideXBy(double divBy);                         //* X / divBy     ||
    void divideYBy(double divBy);                         //* Y / divBy     ||





    void moveVectorX(double move);                        // Moves the vector in a specific x-direction
    void moveVectorY(double move);                        // Moves the vector in a specific y-direction
    void moveVector(double moveX, double moveY);          // Moves the vector in a specific x and y direction 
    void rotateThisVector(double value);

 

    // spezial Vectors
    static Vec2D polarVector(double radius, double angle); // Creates a Vector in a polar system
    static Vec2D zeroVector();                             // Creates a vector with lenght 0
};

#pragma endregion

#ifdef SYSTEMGEOMETRY_HPP //aus systemGeometry.hpp

//Most of the methods in the Vec3D class ar simular to the methods in the Vec2D class
#pragma region Vec3D 
class SystemGeometry;
class Vec3D : public CoordinateSystem3D {
  private: //Private members

    double abs;

  private: //Private Methods
    void calcAbs();
    

  public: // Operator overloading

    Dmath::SystemGeometry *systemGeometry;

    Vec3D operator+(Vec3D& Mathvector);          //Vector addition
    Vec3D operator-(Vec3D& Mathvector);          //Vectors subraction
    Vec3D operator/(double scalarValue);         //Divides the coordinates by a given value
    double operator*(Vec3D& Mathvector);         //Scalarproduct


    inline bool operator==(Vec3D& Mathvector);   // == checks if the x and y coordinates are the same
    inline bool operator!=(Vec3D& Mathvector);   // != checks if the x and y coordinates are diffrent
    inline bool operator>=(Vec3D& Mathvector);   // >= checks if the lenght of the vector is greater or equal
    inline bool operator<=(Vec3D& Mathvector);   // <= checks lenght ...
    inline bool operator<(Vec3D& Mathvector);    // lenght1 < lenght2 ... 
    inline bool operator>(Vec3D& Mathvector);    // lenght1 > lenght2 ...

    void operator++();
    void operator--();

  public: // Public Constructors

   Vec3D() = default; //default constructor

#ifdef CARTESIAN_IS_3D_STANDARD
    Vec3D(double XYZ);
    Vec3D(double X, double Y, double Z);
    Vec3D(double X, double Y, double Z, double originX, double originY, double originZ );
#endif

#ifdef SPHERE_IS_STANDARD
    Vec3D(double radius, double phi, double theta);
#endif

#ifdef CYLINDER_IS_STANDARD
    Vec3D(double radius, double phi, double height);
#endif


  public: //Getters and Setters
    void setX(double X);            //Basic public setters
    void setY(double Y);
    void setZ(double Z);

    void setPhi(double phi);       // For spheresystems (radius, angle Phi, angle Theta)
    void setHeight(double phi);    // For cylinder systems (radius, angle, height);
    void setTheta(double phi);     // For spheresystems (radius, angle Phi, angle Theta);

    void normalize();              // Divides the vectors components though its length 

    double getSphereRadius();      //Getters for other systems
    double getCylinderRadius();

    inline double getAZ() { return this->aZ;  } //Getter for aX and aY
    inline double getAbs(){ return this->abs; }

    //The moveVector() method will move the vectors in the x,y and Z directions
    void moveVector(double moveX, double moveY, double moveZ);

    void moveVectorX(double moveX); // Moves the vector in a specific x-direction
    void moveVectorY(double moveY); // Moves the vector in a specific y-direction
    void moveVectorZ(double moveZ); // Moves the vector in a specific y-direction


    void rotateThisVector(double phi, double Theta);

    // The rotateVector method will return a new Vector based on the original and the given rotation
    Vec3D rotateVector(double radiansPhi, double radiansTheta);  //Gives back a rotated vector based of this vectors coordinats

    // Calculations that return a scalar value
    double dotProduct(Vec3D Mathvector);                         //Simpel dot or scalarproduct between two vectors
    double calcAngle(Vec3D Mathvector);                          //calculates the angle between vectors

    // Calculations that return a vector
    Vec3D vecProduct(Vec3D Mathvector);                          //The vector product of two vectors
    Vec3D add(Vec3D Mathvector);                                 //Vector addition
    Vec3D subtract(Vec3D Mathvector);                            //Vector subtraction

    // Return a spezial vector
    static Vec3D zeroVector();                                   // Returns a Vector with lenght 0

    static Vec3D sphereVector(double radius, double angleOne, double angleTwo); //gives a vector in a sphere  system
    static Vec3D cylinderVector(double radius, double angle, double height);    //gives a vector in a cylinder system

};
#endif

#pragma endregion
#endif // SYSTEM_IS_SET
NAMESPACEEND
#endif // VECTORMATH_H

#pragma endregion