#pragma once

#ifndef VECTORMATH_H
#define VECTORMATH_H
#include "systems.hpp"

#ifdef SYSTEM_READY

#ifdef MATRIX_HPP
  #define DMATRIX
#endif

#include"systemGeometry.hpp"
NAMESPACESTART


class Vec2D : public CoordinateSystem2D {
  private: //Private members
    double abs;                                              // The absolute value or lenght of a vector
    double distanceToZero;   
    double vectorRotation;                                
    void calcAbs();                                         // Calculates the absolute value
    

  public: // Basic operrator overloading:
    
    Vec2D operator/(double scalarValue);                    //divides all components of the Vector with the scalar value and returns it
    Vec2D operator+(Vec2D& Mathvector);                     //Basic Vector addition
    Vec2D operator-(Vec2D& Mathvector);                     //Basic Vector subtractions
    double operator*(Vec2D& Mathvector);                    //Calculates the dotproduct of two vectors

#ifdef DMATRIX //Mathmatical operations between vectors and matrices

    Dmath::Matrix addToMatrix(Dmath::Matrix matrix){

    }

    Dmath::Matrix subtractMatrix(){

    }

    Dmath::Matrix operator+(Dmath::Matrix matrix){
      
    }

    Dmath::Matrix operator-(Dmath::Matrix matrix){
      
    }

    

#endif //DMATRIX

  public: //Public Constructors
#ifdef CARTESIAN_IS_2D_STANDARD
    Vec2D(double XY);                                        // creates a Vector with the same x and y value
    Vec2D(double X, double Y);                                // basic x and y vector
    Vec2D(double X, double Y, double originX, double originY);  // crates a vector with a specific non zero startpoint
#endif // CARTESIAN_IS_2D_STANDARD

#ifdef POLAR_IS_STANDARD
    Vec2D(double radius, double phi);                          // Creates a Vector in a polar coordinatesystem
#endif // POLAR_IS_STANDARD

   

  public: //getters and setters

    /* Setters:
     * If data is set/changed it will automaticly change the values for other
     * coordinate types as well.
     */

    double getRotationAngle();                            // Gets the rotation angle for rotated vectors
    double getAbs();                                      // Calculates the absolutvalue
    double getLenght();                                   // Calculates the length of a vector

    void setX(double value);                              // Basic x setter
    void setY(double value);                              // Basic y setter
    void setPhi(double value);                            // Setter for the angle in a polar system
    void setRadius(double radius);                        // Setter for the radius in a polar system



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
    
    



    public: //vector transformations

   
    void moveVectorX(double move);                        // Moves the vector in a specific x-direction
    void moveVectorY(double move);                        // Moves the vector in a specific y-direction
    void moveVector(double moveX, double moveY);          // Moves the vector in a specific x and y direction 
    void rotateThisVector(double value);

 

    // spezial Vectors
    static Vec2D polarVector(double radius, double angle); // Creates a Vector in a polar system
    static Vec2D zeroVector();                             // Creates a vector with lenght 0
};

#ifdef SYSTEMGEOMETRY_HPP //aus systemGeometry.hpp

//Most of the methods in the Vec3D class ar simular to the methods in the Vec2D class

class SystemGeometry;
class Vec3D : public CoordinateSystem3D {
  private:

    double abs;
    void calcAbs();
    
    

  public: // Operator overloading

    Dmath::SystemGeometry *systemGeometry;

    Vec3D operator+(Vec3D& Mathvector);
    Vec3D operator-(Vec3D& Mathvector);
    Vec3D operator/(double scalarValue);
    double operator*(Vec3D& Mathvector);


  public: // Public Constructors

    //NULL vector
    Vec3D();

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
    void setX(double X);
    void setY(double Y);
    void setZ(double Z);

    void setPhi(double phi);       // For spheresystems (radius, angle Phi, angle Theta)
    void setHeight(double phi);    // For cylinder systems (radius, angle, height);
    void setTheta(double phi);     // For spheresystems (radius, angle Phi, angle Theta);

    void normalize();

    

    double getSphereRadius();
    double getCylinderRadius();

    inline double getAbs(){return this->abs; }

    //The moveVector() method will move the vectors in the x,y and Z directions
    void moveVector(double moveX, double moveY, double moveZ);

    void moveVectorX(double moveX); // Moves the vector in a specific x-direction
    void moveVectorY(double moveY); // Moves the vector in a specific y-direction
    void moveVectorZ(double moveZ); // Moves the vector in a specific y-direction


    void rotateThisVector(double phi, double Theta);

    // The rotateVector method will return a new Vector based on the original and the given rotation
    Vec3D rotateVector(double radiansPhi, double radiansTheta);

    // Calculations that return a scalar value
    double dotProduct(Vec3D Mathvector);
    double calcAngle(Vec3D Mathvector);

    // Calculations that return a vector
    Vec3D vecProduct(Vec3D Mathvector);
    Vec3D add(Vec3D Mathvector);
    Vec3D subtract(Vec3D Mathvector);

    

    // Return a spezial vector
    static Vec3D zeroVector(); // Returns a Vector with lenght 0

    static Vec3D sphereVector(double radius, double angleOne, double angleTwo);
    static Vec3D cylinderVector(double radius, double angle, double height);

};
#endif


#endif // SYSTEM_IS_SET
NAMESPACEEND
#endif // VECTORMATH_H