#pragma once

#ifndef VECTOR_SURFACE_HPP
#define VECTOR_SURFACE_HPP

#include"VectorCurve.hpp"

NAMESPACESTART
class VectorSurface : public VectorAnalysis3D{
  private:
    std::function<float(float, float)> xFunc;
    std::function<float(float, float)> yFunc;
    std::function<float(float, float)> zFunc;

    std::vector<Dmath::Vec3D> mainSurface;
    std::vector<Dmath::Vec3D> surfaceNormals;

    float epsilon = 0.001;

    Dmath::Vec3D calculatePartialDerivativeU(float u, float v);
    Dmath::Vec3D calculatePartialDerivativeV(float u, float v);

    void createVectorSurface();

    VectorSurface(std::function<float(float, float)> xFunc, std::function<float(float, float)> yFunc, std::function<float(float, float)> zFunc, float systemStart, float systemStopp, float resolution);


    float integrateSurfaceArea();

  public:
    static VectorSurface createStandardSurface(std::function<float(float, float)> xFunc, std::function<float(float, float)> yFunc, std::function<float(float, float)> zFunc);

    static VectorSurface createCustomSurface(std::function<float(float, float)> xFunc, std::function<float(float, float)> yFunc,  std::function<float(float, float)> zFunc, float systemStart, float systemStopp, float resolution);

    void calculateSurfaceNormals();

    inline void setEpsilon(float epsilon) { this->epsilon = epsilon;       }
    inline float getEpsilon()             { return this->epsilon;          }
    inline float getSurfaceArea()         { return integrateSurfaceArea(); }

    inline std::function<float(float,float)> getXFunction() {return this->xFunc;}
    inline std::function<float(float,float)> getYFunction() {return this->yFunc;}
    inline std::function<float(float,float)> getZFunction() {return this->zFunc;}

    inline Dmath::Vec3D getSurfaceNormales(size_t index){return this->surfaceNormals[index];}

    Dmath::Vec3D getVectorAtPointT(float t);
    
    float maxX();
    float minX();
    float maxY();
    float minY();
    float maxZ();
    float minZ();

    float calculatePerimeter();

};

NAMESPACEEND

#endif //VECTOR_SURFACE_HPP