#pragma once

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <cmath>
#include <iostream>
#include <vector>
#include <functional>

#define PI 3.14159265358979323846
#define TWOPI 2 * PI
#define FOUR_PI 2 * PI
#define NAMESPACESTART namespace Dmath {
#define NAMESPACEEND }

// uncomment to choose your standard coordinate system

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

#ifdef SYSTEM_IS_SET

// Coordinatesystem2D is used as an abstraction for other classes like the 2 main Vector classes
class CoordinateSystem2D { 
  protected:
    float X;
    float Y;

    float radius;
    float phi;

    float originX;
    float originY;

    void polarToCartesian();
    void cartesianToPolar();

  public:

    inline float getX()       { return this->X;       }
    inline float getY()       { return this->Y;       }   
    inline float getPhi()     { return this->phi;     }
    inline float getOriginX() { return this->originX; }
    inline float getOriginY() { return this->originY; }
    inline float getRadius()  { return this->radius;  }


#ifdef CARTESIAN_IS_2D_STANDARD
    CoordinateSystem2D(float XY);
    CoordinateSystem2D(float x, float y);
    CoordinateSystem2D(float x, float y, float originX, float originY);
#endif

#ifdef POLAR_IS_STANDARD
    CoordinateSystem2D(float radius, float phi);
    CoordinateSystem2D(float radius, float phi, float originX, float originY);
#endif
}; // CoordinateSystem2D

class CoordinateSystem3D : public CoordinateSystem2D {
  protected: // protected data
    float Z;
    float theta;
    float height;
    float originZ;

  protected: // Protected methods;
    void cartesianToSphere();
    void cartesianToCylinder();

    void sphereToCatesian();
    void sphereToCylinder();

    void cylinderToCartesian();
    void cylinderToSphere();

  public: // Public Methods

    //Basic inline getters
    inline float getTheta()   { return this->theta;   }
    inline float getHeight()  { return this->height;  }
    inline float getZ()       { return this->Z;       } 
    inline float getOriginZ() { return this->originZ; }

    float getRadiusSphere();
    float getRadiusCylinder();
    
#ifdef CARTESIAN_IS_3D_STANDARD
    CoordinateSystem3D(float XYZ);
    CoordinateSystem3D(float X, float Y, float Z);
    CoordinateSystem3D(float X, float Y, float Z, float originX, float originY, float originZ);
#endif

#ifdef SPHERE_IS_STANDARD
    CoordinateSystem3D(float radius, float phi, float theta);
    CoordinateSystem3D(float radius, float phi, float theta, float originX, float originY, float originZ);
#endif

#ifdef CYLINDER_IS_STANDARD
    CoordinateSystem3D(float radius, float phi, float height);
    CoordinateSystem3D(float radius, float phi, float hieght, float originX, float originY, float originZ);
#endif

}; // CoordinateSystem3D

#ifdef CARTESIAN_IS_2D_STANDARD
class VectorAnalysis2D{
  protected:
    std::function<float(float)> xFunc;
    std::function<float(float)> yFunc;

    float resolution;
    float systemStart;
    float systemStopp;
    int numberOfElements;

    VectorAnalysis2D(std::function<float(float)> xFunc, std::function<float(float)> yFunc);
    VectorAnalysis2D(std::function<float(float)> xFunc, std::function<float(float)> yFunc, 
                                    float systemStart, float systemStopp, float resolution);

  public:
    

    inline float getNumberOfElements()               { return this->numberOfElements;}
    inline float getResolution()                     { return this->resolution;      }
    inline float getStart()                          { return this->systemStart;     }
    inline float getEnd()                            { return this->systemStopp;     }
    inline float getDataAtX(float data)              { return this->xFunc(data);     }
    inline float getDataAtY(float data)              { return this->yFunc(data);     }
    inline std::function<float(float)> getXFunction(){ return this->xFunc;           }
    inline std::function<float(float)> getYFunction(){ return this->yFunc;           }
    

};

#endif //CARTESIAN_IS_2D_STANDARD

#ifdef CARTESIAN_IS_3D_STANDARD
class VectorAnalysis3D: public VectorAnalysis2D{
  protected:
    std::function<float(float)> zFunc;

    VectorAnalysis3D(std::function<float(float)> xFunc, std::function<float(float)> yFunc, std::function<float(float)> zFunc);
    VectorAnalysis3D(std::function<float(float)> xFunc, std::function<float(float)> yFunc, std::function<float(float)> zFunc,
                                    float systemStart, float systemStopp, float resolution);

  public:

    inline std::function<float(float)> getZfunction(){ return this->zFunc;           }
    inline float getDataAtZ(float data)              { return this->zFunc(data);     }
   
};
#endif //CARTESIAN_IS_2D_STANDARD
#endif // SYSTEM_IS_SET
#endif // SYSTEMS_H includeguard
