#pragma once

#ifndef VEC_S

#define VEC_S

#include"vectorfunction.hpp"
#include"dFunctions.hpp"

NAMESPACESTART

class VectorSurfaceTest{
  private:
    Dmath::DoubleVectorFunction mainFunc;
    Dmath::Parameters params;

  private:
    

  public:

    VectorSurfaceTest(Dmath::DoubleVectorFunction mainFunc){
      this->mainFunc = mainFunc; 
    }

    // std::vector<Dmath::Vec3D> getNumerics(Dmath::Parameters param){
    //   if(!Dmath::checkParams(param)){
    //     std::cerr << "Error Wrong parameters" << std::endl;
    //   }
    //   //Calculates numeric and push into the vector (to do)
    // }


    Dmath::Matrix<DoubleVarFunction> getMetric() {

      //Create a sqared 2x2 tensor in form of a matix
      Dmath::Matrix<Dmath::DoubleVarFunction> metricTensor(2); 

      Dmath::DoubleVarFunction dxdu = this->mainFunc.getXFunc().getPartialX();
      Dmath::DoubleVarFunction dxdv = this->mainFunc.getXFunc().getPartialY();

      Dmath::DoubleVarFunction dydu = this->mainFunc.getYFunc().getPartialX();
      Dmath::DoubleVarFunction dydv = this->mainFunc.getYFunc().getPartialY();
      
      Dmath::DoubleVarFunction dzdu = this->mainFunc.getZFunc().getPartialX();
      Dmath::DoubleVarFunction dzdv = this->mainFunc.getZFunc().getPartialY();

      DoubleVectorFunction dFdu(dxdu,dydu,dzdu);
      DoubleVectorFunction dFdv(dxdv,dydv,dzdv);

      /* The matric g_µv tensor in simple non-relativistic differntial geometry consits of the dot-producs
       * of partial derivativs (basis vectors):
       *
       * g_11 = d/du * d/du
       * g_12 = d/du * d/dv = d/dv * d/du = g_21 
       * g_21 = d/dv * d/du = d/du * d/dv = g_12
       * g_22 = d/dv * d/dv
       */

       Dmath::DoubleVarFunction g_11    = dFdu * dFdu;
       Dmath::DoubleVarFunction g_12_21 = dFdu * dFdv;
       Dmath::DoubleVarFunction g_22    = dFdv * dFdv;

       metricTensor.setElement(1,1,g_11);
       metricTensor.setElement(1,2,g_12_21);
       metricTensor.setElement(2,1,g_12_21);
       metricTensor.setElement(2,2,g_22);

       return metricTensor;
    }
  
};

NAMESPACEEND

#endif
