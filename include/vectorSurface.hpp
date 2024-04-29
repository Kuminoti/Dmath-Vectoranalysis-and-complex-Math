#pragma once

#ifndef VECTOR_SURFACE_HPP
#define VECTOR_SURFACE_HPP

#include"VectorCurve.hpp"

NAMESPACESTART
class VectorSurface : public VectorAnalysis3D{
  private:
    std::function<double(double, double)> xFunc;
    std::function<double(double, double)> yFunc;
    std::function<double(double, double)> zFunc;

    std::vector<Dmath::Vec3D> mainSurface;
    std::vector<Dmath::Vec3D> surfaceNormals;

    double epsilon = 0.001;

    Dmath::Vec3D calculatePartialDerivativeU(double u, double v);
    Dmath::Vec3D calculatePartialDerivativeV(double u, double v);

    void createVectorSurface();

    VectorSurface(std::function<double(double, double)> xFunc, std::function<double(double, double)> yFunc, std::function<double(double, double)> zFunc, double systemStart, double systemStopp, double resolution);


    double integrateSurfaceArea();

  public:
    static VectorSurface createStandardSurface(std::function<double(double, double)> xFunc, std::function<double(double, double)> yFunc, std::function<double(double, double)> zFunc);

    static VectorSurface createCustomSurface(std::function<double(double, double)> xFunc, std::function<double(double, double)> yFunc,  std::function<double(double, double)> zFunc, double systemStart, double systemStopp, double resolution);

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