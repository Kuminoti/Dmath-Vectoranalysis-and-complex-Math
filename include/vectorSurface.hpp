#pragma once

#ifndef VECTOR_SURFACE_HPP
#define VECTOR_SURFACE_HPP

#include"VectorCurve.hpp"

NAMESPACESTART
class VectorSurface : public VectorAnalysis3D{
  private:

    /* Doublevarfunction is a typedef for std::function<double(double,double)>
       it's defined in datatypes.hpp and is used to define mathmatical functions
      example: f(x,y) = x + y
      => singleVarFunction test = [](double x, double y) ->double { return x+y; }
    */
    Dmath::doubleVarFunction xFunc;
    Dmath::doubleVarFunction yFunc;
    Dmath::doubleVarFunction zFunc;

    std::vector<Dmath::Vec3D> mainSurface;
    std::vector<Dmath::Vec3D> surfaceNormals;

    double epsilon = 0.001;

    Dmath::Vec3D calculatePartialDerivativeU(double u, double v);
    Dmath::Vec3D calculatePartialDerivativeV(double u, double v);

    void createVectorSurface();

    VectorSurface(doubleVarFunction xFunc, doubleVarFunction yFunc, doubleVarFunction zFunc, double systemStart, double systemStopp, double resolution);


    double integrateSurfaceArea();

  public:
    static VectorSurface createStandardSurface(doubleVarFunction xFunc, doubleVarFunction yFunc, doubleVarFunction zFunc);

    static VectorSurface createCustomSurface(doubleVarFunction xFunc, doubleVarFunction yFunc,  doubleVarFunction zFunc, double systemStart, double systemStopp, double resolution);

    void calculateSurfaceNormals();

    inline void setEpsilon(double epsilon) { this->epsilon = epsilon;       }
    inline double getEpsilon()             { return this->epsilon;          }
    inline double getSurfaceArea()         { return integrateSurfaceArea(); }

    inline std::function<double(double,double)> getXFunction() {return this->xFunc;}
    inline std::function<double(double,double)> getYFunction() {return this->yFunc;}
    inline std::function<double(double,double)> getZFunction() {return this->zFunc;}

    inline Dmath::Vec3D getSurfaceNormales(size_t index){return this->surfaceNormals[index];}

    Dmath::Vec3D getVectorAtPointT(double t);
    
    double maxX();
    double minX();
    double maxY();
    double minY();
    double maxZ();
    double minZ();

    double calculatePerimeter();

};

NAMESPACEEND

#endif //VECTOR_SURFACE_HPP