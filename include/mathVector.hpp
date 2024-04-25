#pragma once

#ifndef VECTORMATH_H
#define VECTORMATH_H
#include "systems.hpp"
#ifdef SYSTEM_IS_SET

NAMESPACESTART
class Vec2D : public CoordinateSystem2D {
  private:
    float aX;                                               // Absolute X the coordinate of a vector that does not start at zero
    float aY;                                               // Absolute Y the coordinate of a vector that does not start at zero
    float abs;                                              // The absolute value or lenght of a vector
    float distanceToZero;                                   // Calculates the distance to zero for a vector that dont start at zero
    void calcDZ();                                          // Calculates the distance to zero
    void calcAbs();                                         // Calculates the absolute value
    void calcAbsXY();                                       // Calculates and sets the absolute x and y coordinates
    

  public:
    // Basic operrator overloading:
    Vec2D operator/(float scalarValue);                     //divides all components of the Vector with the scalar value and returns it
    Vec2D operator+(Vec2D& Mathvector);                     //Basic Vector addition
    Vec2D operator-(Vec2D& Mathvector);                     //Basic Vector subtractions
    float operator*(Vec2D& Mathvector);                     //Calculates the dotproduct of two vectors
    
#ifdef CARTESIAN_IS_2D_STANDARD
    Vec2D(float XY);                                        // creates a Vector with the same x and y value
    Vec2D(float X, float Y);                                // basic x and y vector
    Vec2D(float X, float Y, float originX, float originY);  // crates a vector with a specific non zero startpoint
#endif // CARTESIAN_IS_2D_STANDARD

#ifdef POLAR_IS_STANDARD
    Vec2D(float radius, float phi);                          // Creates a Vector in a polar coordinatesystem
#endif // POLAR_IS_STANDARD

    // Math with scalar results

    float getAX();                                       // Gets the absolute X coordinate from a vector with a non zero start
    float getAY();                                       // Gets the absolute X coordinate from a vector with a non zero start
    float getDistanceToZero();                           // Gets the distance to [ 0 ; 0 ] from a vector with a non zero start
    float getAbs();                                      // Calculates the absolutvalue
    float lenght();                                      // Calculates the length of a vector

    float dotProduct(Vec2D Mathvector);                  // Calculates Scalar product
    float calcAngle(Vec2D Mathvector);                   // Calculates the angle between 2 vectors
    float distance(Vec2D Mathvector);                    // Calculates the distance between vectors
                    
    float polarSystemArea();                             // Calculates the circle of a polar system
    float polarSystemCircumfrance();                     // Calculates the circumfrance of a polar system
    float rectangleArea(Vec2D MathVector);               // Calculates the area of a rectangle
    float rectangleCircumfrance(Vec2D MathVector);       // Calculates the circumfrance of the rectangle
    
    /* Setters:
     * If data is set/changed it will automaticly change the values for other
     * coordinate types as well.
     */

    void setX(float value);                              // Basic x setter
    void setY(float value);                              // Basic y setter
    void setPhi(float value);                            // Setter for the angle in a polar system
    void setRadius(float radius);                        // Setter for the radius in a polar system

    void normalize();

    void setOriginX(float newOriginX);
    void setOriginY(float newOriginY);
   
    void moveVectorX(float move);                        // Moves the vector in a specific x-direction
    void moveVectorY(float move);                        // Moves the vector in a specific y-direction
    void moveVector(float moveX, float moveY);           // Moves the vector in a specific x and y direction 

    // You can use methods instead of operators
    Vec2D add(Vec2D Mathvector);                         // Adding 2 vectors
    Vec2D subtract(Vec2D Mathvector);                    // Subtract 2 vectors
    Vec2D rotateVector(float angle);                     // Rotates a vector dependent op the angle

    // spezial Vectors
    static Vec2D polarVector(float radius, float angle); // Creates a Vector in a polar system
    static Vec2D zeroVector();                           // Creates a vector with lenght 0
};


//Most of the methods in the Vec3D class ar simular to the methods in the Vec2D class
class Vec3D : public CoordinateSystem3D {
  private:
    float aX;
    float aY;
    float aZ;
    float distanceToZero;
    float abs;
    void calcAbs();
    void calcDTZ();
    void calcAXYZ();

  public: // Operator overloading
    Vec3D operator+(Vec3D& Mathvector);
    Vec3D operator-(Vec3D& Mathvector);
    float operator*(Vec3D& Mathvector);

#ifdef CARTESIAN_IS_3D_STANDARD
    Vec3D(float XYZ);
    Vec3D(float X, float Y, float Z);
    Vec3D(float X, float Y, float Z, float originX, float originY, float originZ );
#endif

#ifdef SPHERE_IS_STANDARD
    Vec3D(float radius, float phi, float theta);
#endif

#ifdef CYLINDER_IS_STANDARD
    Vec3D(float radius, float phi, float height);
#endif

    // Setters
    void setX(float X);
    void setY(float Y);
    void setZ(float Z);
    void normalize();

    void setPhi(float phi);       // For spheresystems (radius, angle Phi, angle Theta)
    void setHeight(float phi);    // For cylinder systems (radius, angle, height);
    void setTheta(float phi);     // For spheresystems (radius, angle Phi, angle Theta);

    void moveVectorX(float move);                        // Moves the vector in a specific x-direction
    void moveVectorY(float move);  
    void moveVectorZ(float Z);        
    void moveVector(float moveX, float moveY, float moveZ);           


    // Calculations that return a scalar value
    float dotProduct(Vec3D Mathvector);
    float calcAngle(Vec3D Mathvector);

    // Calculations that return a vector
    Vec3D vecProduct(Vec3D Mathvector);
    Vec3D add(Vec3D Mathvector);
    Vec3D subtract(Vec3D Mathvector);
  

    // Return a spezial vector
    static Vec3D zeroVector(); // Returns a Vector with lenght 0
    static Vec3D sphereVector(float radius, float angleOne, float angleTwo);
    static Vec3D cylinderVector(float radius, float angle, float height);

    // Volumes and surfaces of sphere and cylinder systems
    float cylinderSystemVolume();
    float cylinderSystemSurface();
    float cylinderSystemLateralSurface();

    float sphereSystemVolume();
    float sphereSystemSurface();

    // Volumes and surface from a cuboid build with vectors
    float cuboidVolume(Vec3D MathVector, Vec3D MathVectorTwo);
    float cuboidSurface(Vec3D MathVector, Vec3D MathVectorTwo);

    float getAbs();
    float getSphereRadius();
    float getCylinderRadius();
};

#endif // SYSTEM_IS_SET
NAMESPACEEND
#endif // VECTORMATH_H