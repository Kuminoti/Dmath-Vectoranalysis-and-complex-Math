#pragma once

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <cmath>
#include <iostream>
#include <vector>
#include <functional>

#define STDRES 0.1f               //The standard resolution for more dimensional vector systems
#define ZERO 0                    //Standard zero used as a constant for the startpoint in more dimensional vector systems
#define PI 3.14159265358979323846
#define EULER 2.718281828459045
#define TWOPI 2 * PI
#define FOUR_PI 2 * PI
#define RAD_TO_DEG 180.f/PI
#define DEG_TO_RAD PI/180.f
#define NAMESPACESTART namespace Dmath {
#define NAMESPACEEND }

/* This file is used to create a base and an abstraction for the other classes and systems.
 * The CoordinateSystem2D and CoordinateSystem3D classes will be inherited to the Vec2D and Vec3D
 * classes the classes for the basic vectors.
 * The VectorAnalysis2D and VectorAnalysis3D will be inherited to the VectorCurve and Vectorsurface classes
 * 
 * In this file you can choose the standard Coordinate system for you calculations and it contains important
 * mathmatical constants and data.
*/


//Choose your prefered angle unit with (un)commenting the fitting macro
#define STANDARD_ANGLE_UNIT_DEG
//#define STANDARD_ANGLE_UNIT_RAD
#if(defined(STANDARD_ANGLE_UNIT_DEG) || defined(STANDARD_ANGLE_UNIT_RAD))
#define ANGLE_UNIT_SET
#else
#if(defined(STANDARD_ANGLE_UNIT_DEG) && defined(STANDARD_ANGLE_UNIT_RAD))
#warning "Both angle units are set standard will be radiants!"
#undef STANDARD_ANGLE_UNIT_DEG
#define ANGLE_UNIT_SET
#endif
#endif

//Uncomment to choose your standard coordinate system

#define CARTESIAN_IS_2D_STANDARD   // Cartesian system: X,Y
//#define POLAR_IS_STANDARD        //Polar system: Radius, phi

#define CARTESIAN_IS_3D_STANDARD   //Cartesian system: X,Y,Z
//#define SPHERE_IS_STANDARD       // Sphere system: Radius, phi, phi
//#define CYLINDER_IS_STANDARD     //Cylinder system: Radius, phi, height

#if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD)) &&                              \
    defined(CARTESIAN_IS_3D_STANDARD)
#warning "Warning: More than one system is defined!"
#undef CARTESIAN_IS_STANDARD
#ifdef SPHERE_IS_STANDARD
#undef CYLINDER_IS_STANDARD
#warning "Sphere system will be standart!"
#endif
#warning "Cylinder system will be standart!"

#endif

#ifdef POLAR_IS_STANDARD
#ifdef CARTESIAN_IS_2D_STANDARD
#undef CARTESIAN_IS_2D_STANDARD
#warning                                                                                           \
    "Warning: You defined polar coordinates as standard and cartesian as 2D standard. Polar will be standard."
#endif
#endif

#if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD) ||                               \
     defined(CARTESIAN_IS_3D_STANDARD) || defined(POLAR_IS_STANDARD) ||                            \
     defined(CARTESIAN_IS_2D_STANDARD))
#define SYSTEM_IS_SET
#else
#error "FATAL ERROR NO SYSTEM SET"
#endif

#if (defined(SYSTEM_IS_SET) && defined(ANGLE_UNIT_SET))
#define SYSTEM_READY




// A helper class with some pre defined functions
class MathHelper{
  private:
    double h  = 0.0001;           //Resolution for Derivative
    double dx = 0.000000001;      //Stepps for Antiderivative
    int numSteps = 1000;         //Stepps for the integral
    

  public:

    inline double hyperbolicCotangent(double X){ return this->hyperbolicCosine(X)/this->hyperbolicSine(X); }
    inline double hyperbolicTangent(double X)  { return this->hyperbolicSine(X)/this->hyperbolicCosine(X); }
    inline double hyperbolicCosine(double X)   { return (0.5*(std::pow(EULER,X) + std::pow(EULER,-X)));    }
    inline double hyperbolicSine(double X)     { return (0.5*(std::pow(EULER,X) - std::pow(EULER,-X)));    }

    inline double pyth(double x, double y){return std::sqrt((x*x) + (y*y) );}
    inline double pyth3D(double x, double y, double z){return std::sqrt((x*x) + (y*y) +(z*z) );}

    inline double radiansToDegrees(double radians) {return radians * RAD_TO_DEG;}
    inline double degreesToRadians(double degrees) {return degrees * DEG_TO_RAD;}

    inline double sinFunc (double x) { return std::sin(x); }
    inline double cosFunc (double x) { return std::cos(x); }
    inline double tanFunc (double x) { return std::cos(x); }
    inline double numOfElements(double start, double stopp, double res){ return static_cast<int> ((stopp-start)/res);}

    double calculateDerivativeAt(std::function<double(double)> f, double x);
    double calculateDefiniteIntegral(std::function<double(double)> f, double a, double b);

    std::function<double(double)> calculateAntiderivative(std::function<double(double)> f, double x0);
    std::function<double(double)> calculateDerivative(std::function<double(double)> f);


    double sigmaAdd(std::function<double(double)> mainFunc,size_t start, size_t end);
    double piMultiply(std::function<double(double)> mainFunc,size_t start, size_t end);

};


// Coordinatesystem2D is used as an abstraction for other classes like the 2 main Vector classes
class CoordinateSystem2D { 
  protected:
    double X;
    double Y;

    double radius;
    double phi;

    double originX;
    double originY;

    double aX;
    double aY;

    double distanceToZero;

    void polarToCartesian();
    void cartesianToPolar();

    void calcAbsXY();
    void calcDZ();                                          // Calculates the distance to zero


  public:
    MathHelper mathHelper;

    inline double getX()       { return this->X;       }
    inline double getY()       { return this->Y;       }
    inline double getAX()      { return this->aX;      }
    inline double getAY()      { return this->aY;      }   
    inline double getPhi()     { return this->phi;     }
    inline double getRadius()  { return this->radius;  }    
    inline double getOriginX() { return this->originX; }
    inline double getOriginY() { return this->originY; }
   
    void setOriginX(double newOriginX);
    void setOriginY(double newOriginY);

    inline double getDistanceZero(){ return this->distanceToZero; } 

#ifdef CARTESIAN_IS_2D_STANDARD
    CoordinateSystem2D(double XY);
    CoordinateSystem2D(double x, double y);
    CoordinateSystem2D(double x, double y, double originX, double originY);
#endif

#ifdef POLAR_IS_STANDARD
    CoordinateSystem2D(double radius, double phi);
    CoordinateSystem2D(double radius, double phi, double originX, double originY);
#endif
}; // CoordinateSystem2D

class CoordinateSystem3D : public CoordinateSystem2D {
  protected: // protected data
    double Z;
    double aZ;
    double theta;
    double height;
    double originZ;

  protected: // Protected methods;
    void cartesianToSphere();
    void cartesianToCylinder();

    void sphereToCatesian();
    void sphereToCylinder();

    void cylinderToCartesian();
    void cylinderToSphere();
    void calcDTZ();
    void calcAXYZ();
    

  public: // Public Methods

    //Basic inline getters
    inline double getTheta()   { return this->theta;   }
    inline double getHeight()  { return this->height;  }
    inline double getZ()       { return this->Z;       } 
    inline double getOriginZ() { return this->originZ; }

    void setOriginX(double Value);

    void setOriginY(double Value);

    void setOriginZ(double Value);

    double getRadiusSphere();
    double getRadiusCylinder();
    
#ifdef CARTESIAN_IS_3D_STANDARD
    CoordinateSystem3D(double XYZ);
    CoordinateSystem3D(double X, double Y, double Z);
    CoordinateSystem3D(double X, double Y, double Z, double originX, double originY, double originZ);
#endif

#ifdef SPHERE_IS_STANDARD
    CoordinateSystem3D(double radius, double phi, double theta);
    CoordinateSystem3D(double radius, double phi, double theta, double originX, double originY, double originZ);
#endif

#ifdef CYLINDER_IS_STANDARD
    CoordinateSystem3D(double radius, double phi, double height);
    CoordinateSystem3D(double radius, double phi, double hieght, double originX, double originY, double originZ);
#endif

}; // CoordinateSystem3D

#ifdef CARTESIAN_IS_2D_STANDARD
class VectorAnalysis2D{
  protected:

    // One main function for implicid curves

    std::function<double(double,double)> mainFunc;


    // X and Y-functions
    std::function<double(double)> xFunc;
    std::function<double(double)> yFunc;

    double resolution  = STDRES;
    double systemStart = ZERO;
    double systemStopp = TWOPI;
    double rotation    = ZERO;
    int numberOfElements;

    VectorAnalysis2D(double systemStart, double systemStopp, double resolution);
    VectorAnalysis2D(std::function<double(double)> xFunc, std::function<double(double)> yFunc);
    VectorAnalysis2D(std::function<double(double,double)> mainFunc, double systemStart, double systemStopp, double resolution);
    VectorAnalysis2D(std::function<double(double)> xFunc, std::function<double(double)> yFunc, double systemStart, double systemStopp, double resolution);
    VectorAnalysis2D(std::function<double(double)> xFunc, std::function<double(double)> yFunc, double systemStart, double systemStopp, double resolution, double rotation);

  public:

    inline double getNumberOfElements()                { return this->numberOfElements;}
    inline double getResolution()                      { return this->resolution;      }
    inline double getStart()                           { return this->systemStart;     }
    inline double getEnd()                             { return this->systemStopp;     }
    inline double getDataAtX(double data)              { return this->xFunc(data);     }
    inline double getDataAtY(double data)              { return this->yFunc(data);     }
    inline std::function<double(double)> getXFunction(){ return this->xFunc;           }
    inline std::function<double(double)> getYFunction(){ return this->yFunc;           }

    MathHelper mathHelper;

};

#endif //CARTESIAN_IS_2D_STANDARD

#ifdef CARTESIAN_IS_3D_STANDARD
class VectorAnalysis3D: public VectorAnalysis2D{
  protected:
    
    std::function<double(double)> zFunc;
    VectorAnalysis3D(double systemStart, double systemStopp, double resolution);
    VectorAnalysis3D(std::function<double(double)> xFunc, std::function<double(double)> yFunc, std::function<double(double)> zFunc);
    VectorAnalysis3D(std::function<double(double)> xFunc, std::function<double(double)> yFunc, std::function<double(double)> zFunc,
                                    double systemStart, double systemStopp, double resolution);

  public:

    inline std::function<double(double)> getZfunction(){ return this->zFunc;           }
    inline double getDataAtZ(double data)              { return this->zFunc(data);     }

   
};
#endif 
#endif // SYSTEM_IS_SET
#endif // SYSTEMS_H includeguard
