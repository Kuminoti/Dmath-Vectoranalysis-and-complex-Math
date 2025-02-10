#pragma once

#ifndef VEC_S

#define VEC_S

#include"mathVector.hpp"
#include"mathFunction.hpp"

NAMESPACESTART

class VectorSurfaceTest{
  private:
    Dmath::DoubleVarFunction xOfUV;
    Dmath::DoubleVarFunction yOfUV;
    Dmath::DoubleVarFunction zOfUV;

  public:
    VectorSurfaceTest(Dmath::DoubleVarFunction xOfUV,Dmath::DoubleVarFunction yOfUV,Dmath::DoubleVarFunction zOfUV){
        this->xOfUV = xOfUV;
        this->yOfUV = yOfUV;
        this->zOfUV = zOfUV;
        
    }
};

NAMESPACEEND

#endif
