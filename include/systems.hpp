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
    VectorAnalysis2D(Dmath::singleVarFunction xFunc, Dmath::singleVarFunction yFunc);
    VectorAnalysis2D(std::function<double(double,double)> mainFunc, double systemStart, double systemStopp, double resolution);

    VectorAnalysis2D(Dmath::singleVarFunction xFunc, Dmath::singleVarFunction yFunc, double systemStart, double systemStopp, double resolution);
    VectorAnalysis2D(Dmath::singleVarFunction xFunc, Dmath::singleVarFunction yFunc, double systemStart, double systemStopp, double resolution, double rotation);

  public:

    inline double getNumberOfElements()                { return this->numberOfElements;}
    inline double getResolution()                      { return this->resolution;      }
    inline double getStart()                           { return this->systemStart;     }
    inline double getEnd()                             { return this->systemStopp;     }
    inline double getDataAtX(double data)              { return this->xFunc(data);     }
    inline double getDataAtY(double data)              { return this->yFunc(data);     }
    inline Dmath::singleVarFunction getXFunction(){ return this->xFunc;           }
    inline Dmath::singleVarFunction getYFunction(){ return this->yFunc;           }

    virtual ~VectorAnalysis2D() = default;

    

};

#endif //CARTESIAN_IS_2D_STANDARD

#ifdef CARTESIAN_IS_3D_STANDARD
class VectorAnalysis3D: public VectorAnalysis2D{
  protected:

    std::function<Dmath::Trio<double, double, double>(double, double, double)> functionX;
    std::function<Dmath::Trio<double, double, double>(double, double, double)> functionY;
    std::function<Dmath::Trio<double, double, double>(double, double, double)> functionZ;
    
    Dmath::singleVarFunction zFunc;
    
    VectorAnalysis3D(double systemStart, double systemStopp, double resolution);
    VectorAnalysis3D(Dmath::singleVarFunction xFunc, Dmath::singleVarFunction yFunc,Dmath::singleVarFunction zFunc);
    VectorAnalysis3D(Dmath::singleVarFunction xFunc, Dmath::singleVarFunction yFunc,Dmath::singleVarFunction zFunc,
                                    double systemStart, double systemStopp, double resolution);

  public:

    inline Dmath::singleVarFunction getZfunction(){ return this->zFunc;           }
    inline double getDataAtZ(double data)              { return this->zFunc(data);     }

   virtual ~VectorAnalysis3D(){}
};
#pragma endregion
#endif 
#endif // SYSTEM_IS_SET
#endif // SYSTEMS_H includeguard
