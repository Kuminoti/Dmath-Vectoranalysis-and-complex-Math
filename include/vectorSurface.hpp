#pragma once

#ifndef VECTOR_SURFACE_HPP
#define VECTOR_SURFACE_HPP

#include"VectorCurve.hpp"
#include"Matrix.hpp"

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

    

    Dmath::Matrix<std::vector<double>> getMetric(){

      std::vector<Dmath::Vec3D> derivativeU;
      std::vector<Dmath::Vec3D> derivativeV;

      for(size_t u = 0; u < numberOfElements; u++){
        for(size_t v = 0; v < numberOfElements; v++){

          double currentU = this->systemStart + u * this->resolution;
          double currentV = this->systemStart + v * this->resolution;

          Dmath::Vec3D currentVecU = this->calculatePartialDerivativeU(currentU, currentV);
          Dmath::Vec3D currentVecV = this->calculatePartialDerivativeV(currentU, currentV);

          derivativeU.push_back(currentVecU);
          derivativeV.push_back(currentVecV);
        }
      }


      Dmath::Matrix<std::vector<double>> mainMetric(2);
      std::vector<double> uU;
      std::vector<double> uV;
      std::vector<double> vU;
      std::vector<double> vV;


      for(size_t i = 0; i < numberOfElements; i++){
        uU.push_back(derivativeU[i].dotProduct(derivativeU[i]));
        uV.push_back(derivativeU[i].dotProduct(derivativeV[i]));
        vU.push_back(derivativeV[i].dotProduct(derivativeU[i]));
        vV.push_back(derivativeV[i].dotProduct(derivativeV[i]));
      }


      mainMetric.setElement(1,1,uU);
      mainMetric.setElement(1,2,uV);
      mainMetric.setElement(2,1,uV);
      mainMetric.setElement(2,2,vV);

      return mainMetric;

    }

  
  

};

NAMESPACEEND

#endif //VECTOR_SURFACE_HPP