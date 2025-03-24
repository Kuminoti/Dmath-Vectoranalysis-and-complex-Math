#pragma once

#ifndef VEC_S

#define VEC_S

#include"vectorfunction.hpp"
#include"dFunctions.hpp"

NAMESPACESTART

class VectorSurfaceTest{
  private:
    Dmath::DoubleVectorFunction mainFunc;
    std::vector<Dmath::Vec3D> numerics;

    size_t numOfElements = 0;
    Dmath::Parameters params;

    

  public:

    VectorSurfaceTest(Dmath::DoubleVectorFunction mainFunc, double start, double end, double stepp){
      this->mainFunc = mainFunc;
      this->params = Dmath::Parameters(start,end,stepp);
      if(!Dmath::checkParams(this->params)){
        this->params = Dmath::Parameters(0,TWOPI,0.1);
      }
      this->numOfElements = Dmath::numberOfElements(params);
    }
  
};

NAMESPACEEND

#endif
