#pragma once
#ifndef BASICFUNCTIONS_H
#define BASICFUNCTIONS_H

#include "systems.hpp"



NAMESPACESTART
class BasicFunction {
  protected: // protected members:
    double systemStart = ZERO;
    double systemStopp = TWOPI;
    double resolution = STDRES;

    size_t numberOfElements = 0;

    MathHelper mathHelper;

  private: // private methods:

    virtual void createCurve();
    Dmath::singleVarFunction mainFunc;
    std::vector<double> fX;

public:

    BasicFunction(Dmath::singleVarFunction mainFunc);
    //BasicFunction(Dmath::singleVarFunction mainFunc, double resolution); // Constructor for polarfunctions
    BasicFunction(Dmath::singleVarFunction mainFunc, double systemStart, double systemStopp, double resolution);

  public:
    double operator[](size_t index);

    static BasicFunction createBasicFunctionGraph(Dmath::singleVarFunction mainFunc) { return BasicFunction(mainFunc); }
    static BasicFunction createCustomFunctionGraph(Dmath::singleVarFunction mainFunc, double systemStart, double systemStopp, double resolution) {
     
        return BasicFunction(mainFunc, systemStart, systemStopp, resolution);
    }

    // r(phi) =
    //static BasicFunction PolarFunction(Dmath::singleVarFunction mainFunc, double resolution) { return BasicFunction(mainFunc, resolution); }

    // Returns the number of zero points
    size_t numberOfZeroPoints();

    // Returns the area between the X-achsis and the graph
    double areaXachsis(double start, double stopp);
    double getSlopeAt(double Value);

    // Getters:
    inline double getResolution() { return this->resolution; }
    inline double getSystemStart() { return this->systemStart; }
    inline double getSystemStopp() { return this->systemStopp; }
    inline double getNumberOfElements() { return this->numberOfElements; }

    // Maximum and minimum
    double getMaximum();
    double getMinimum();

    double getLength(); // NEEDS DEFINITION


    bool exsitsIn(double Value);
};

// f(x,y) = ...
class TwoVariableFunction {
  private: // private members
    Dmath::Duo<double, double> variables;
    std::vector<Dmath::Duo<double, double>> functionVector;
    std::function<Dmath::Duo<double, double>(double, double)> mainFunc;

    double systemStart = ZERO;
    double systemStopp = TWOPI;
    double resolution = STDRES;

    size_t numberOfElements = 0;

  protected: //Protected mathods

    virtual void createFunction(){
      for(float i = this->systemStart; i < this->systemStopp; i +=this->resolution){
        for(float j = this->systemStart; j < this->systemStopp; i += this->resolution){
          this->variables = mainFunc(i,j);
          functionVector.push_back(this->variables);
        }
      }
    }

  private: // Private Constructors
    TwoVariableFunction(std::function<Dmath::Duo<double, double>(double, double)> mainFunc) {
        this->systemStart = 0;
        this->systemStopp = TWOPI;
        this->resolution = STDRES;
        this->mainFunc = mainFunc;
        this->numberOfElements = static_cast<size_t>((this->systemStopp - this->systemStart) / this->resolution);
    }

    Dmath::Duo<double, double> getDataAtPoint(double valueX, double valueY){
      Dmath::Duo<double,double> newDuo(0.0,0.0);

      if(valueX >= this->systemStart && valueX <= this->systemStopp &&
         valueY >= this->systemStart && valueY <= this->systemStopp ){
          newDuo = this->mainFunc(valueX, valueY);
          
      }
      return newDuo;
    }
};

NAMESPACEEND

#endif // Include guard