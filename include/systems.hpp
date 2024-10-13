#pragma once

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include"macros.hpp"   //Contains macros and constants for this project
#include"dataTypes.hpp" //Contains library specific datatypes

/* 
 * This file is used to create a base and an abstraction for the other classes and systems.
 * The CoordinateSystem2D and CoordinateSystem3D classes will be inherited to the Vec2D and Vec3D
 * classes the classes for the basic vectors.
 * The VectorAnalysis2D and VectorAnalysis3D will be inherited to the VectorCurve and Vectorsurface classes
 * 
 * In this file you can choose the standard Coordinate system for you calculations and it contains important
 * mathmatical constants and data.
*/




#ifdef SYSTEM_READY

#pragma region MathHelper
// A helper class with some pre defined functions
class MathHelper{
  private:
  
    double h  = 0.0001;               //Resolution for Derivative
    double dx = 0.000000001;          //Stepps for Antiderivative
    uint16_t numSteps = 1000;         //Stepps for the integral
    

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

#pragma endregion


#pragma region 2D-Coordinates
// Coordinatesystem2D is used as an abstraction for other classes like the 2 main Vector classes
class CoordinateSystem2D { 

  protected: // Protected members

    void* NULLVECX = 0; //NULL vector x
    void* NULLVECY = 0; //NULL vector y

    double X = 0;
    double Y = 0;
    double t = 0;     //A parameter t can be used to represent time or can be used for parametriccurves



    //For vectors wich doesnt start at zero
    double originX = 0;       //the "x-Start" of the vector, if the vector it self doesent start at zero  
    double originY = 0;       //the "x-Start" of the vector, if the vector it self doesent start at zero

    double aX;                //The absoulute xvalue, or the distence between 0 and the X value
    double aY;                //The absoulute yvalue, or the distence between 0 and the Y value

    double distanceToZero; 

    double radius = 0;        //Randius and angle for polar-coordinates 
    double phi = 0;           //Angle phi



  

    void polarToCartesian();
    void cartesianToPolar();

    void calcAbsXY();
    void calcDZ();                                          // Calculates the distance to zero

  public:
#ifdef CARTESIAN_IS_2D_STANDARD

    //sVec is a struct with only an x, and y (and z) member defined in include/datatypes.hpp
    CoordinateSystem2D(Dmath::sVec2f vec);
    CoordinateSystem2D(Dmath::sVec2i vec);

    CoordinateSystem2D() = default;
    CoordinateSystem2D(double XY);
    CoordinateSystem2D(double x, double y);
    CoordinateSystem2D(double x, double y, double t); //Need Implementation
    CoordinateSystem2D(double x, double y, double originX, double originY);
#endif

#ifdef POLAR_IS_STANDARD
    CoordinateSystem2D(double radius, double phi);
    CoordinateSystem2D(double radius, double phi, double originX, double originY);
#endif

  virtual ~CoordinateSystem2D() = default;



  public:

  void operator++();
    MathHelper mathHelper;
    inline double getT()       { return this->t;       }
    inline double getX()       { return this->X;       }
    inline double getY()       { return this->Y;       }
    inline double getAX()      { return this->aX;      }
    inline double getAY()      { return this->aY;      }   
    inline double getPhi()     { return this->phi;     }
    inline double getRadius()  { return this->radius;  }    
    inline double getOriginX() { return this->originX; }
    inline double getOriginY() { return this->originY; }

    inline void setT(double t) { this->t = t; }

    void setOriginX(double newOriginX);
    void setOriginY(double newOriginY);

    inline double getDistanceZero(){ return this->distanceToZero; } 

    


}; // CoordinateSystem2D

#pragma endregion


#pragma region 3D-Coordinates
class CoordinateSystem3D : public CoordinateSystem2D {
  protected: // protected data
    //For zero or nullvectors
    void* NULLVECX = 0;
    void* NULLVECY = 0;
    void* NULLVECZ = 0;

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
    
  public: //Public constructors

#ifdef CARTESIAN_IS_3D_STANDARD

    CoordinateSystem3D(Dmath::sVec3f vec);
    CoordinateSystem3D(Dmath::sVec3i vec);

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


    virtual ~CoordinateSystem3D() = default;



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
    //Zerovector / NULL vector constructor

    CoordinateSystem3D() : CoordinateSystem2D(){
      this->NULLVECX = CNULL;
      this->NULLVECY = CNULL;
      this->NULLVECZ = CNULL;
    }


}; // CoordinateSystem3D

#ifdef CARTESIAN_IS_2D_STANDARD
class VectorAnalysis2D{
  protected:

    // One main function for implicid curves

    std::function<double(double,double)> mainFunc;

    std::function<Dmath::Duo<double,double>(double, double)> funcOne;
    std::function<Dmath::Duo<double,double>(double, double)> funcTwo;

    // X and Y-functions
    std::function<double(double)> xFunc;
    std::function<double(double)> yFunc;

    std::function<void()> noFunc = []() {return CNULL;};

    double resolution  = STDRES;
    double systemStart = ZERO;
    double systemStopp = TWOPI;
    double rotation    = ZERO;
    int numberOfElements;


    VectorAnalysis2D(std::function<Dmath::Duo<double,double>(double,double)> paramOne, std::function<Dmath::Duo<double,double>(double,double)> paramTwo);
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

    virtual ~VectorAnalysis2D() = default;

    MathHelper mathHelper;

};

#endif //CARTESIAN_IS_2D_STANDARD

#ifdef CARTESIAN_IS_3D_STANDARD
class VectorAnalysis3D: public VectorAnalysis2D{
  protected:

    std::function<Dmath::Trio<double, double, double>(double, double, double)> functionX;
    std::function<Dmath::Trio<double, double, double>(double, double, double)> functionY;
    std::function<Dmath::Trio<double, double, double>(double, double, double)> functionZ;
    
    std::function<double(double)> zFunc;
    
    VectorAnalysis3D(double systemStart, double systemStopp, double resolution);
    VectorAnalysis3D(std::function<double(double)> xFunc, std::function<double(double)> yFunc, std::function<double(double)> zFunc);
    VectorAnalysis3D(std::function<double(double)> xFunc, std::function<double(double)> yFunc, std::function<double(double)> zFunc,
                                    double systemStart, double systemStopp, double resolution);

  public:

    inline std::function<double(double)> getZfunction(){ return this->zFunc;           }
    inline double getDataAtZ(double data)              { return this->zFunc(data);     }

   
};
#pragma endregion
#endif 
#endif // SYSTEM_IS_SET
#endif // SYSTEMS_H includeguard
